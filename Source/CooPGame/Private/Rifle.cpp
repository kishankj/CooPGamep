// Fill out your copyright notice in the Description page of Project Settings.

#include "Rifle.h"

#include <algorithm>
#include <glslang/glslang/src/glslang_lib/glslang/Include/Common.h>


#include "Components/SkeletalMeshComponent.h"
#include"DrawDebugHelpers.h"
#include "Scharacter.h"
#include "Kismet/GameplayStatics.h"
#include"Particles/ParticleSystem.h"
#include"Components/SkeletalMeshComponent.h"
#include "LandscapeEditor/Public/LandscapeToolInterface.h"
#include"Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MuzzelSocket = "MuzzelSocket";
	Target = "Target";
	BaseDamage = 20;
  
	RatePerMinute = 600;
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60/RatePerMinute;
	SetWeaponRotation();
}


void ARifle::SetWeaponRotation()
{
	FRotator rotation;

float MouseAxisValue = GetInputAxisValue(AxisValue);
	FRotator RifleNewRotation;
	RifleNewRotation.Pitch = MouseAxisValue;
	RifleNewRotation.Yaw = 0;
	RifleNewRotation.Roll = 0;
	this->SetActorRotation(RifleNewRotation);
}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARifle::Startfire()
{
	float FirstDelay = FMath::Max(FireRunTime + TimeBetweenShots - GetWorld()->TimeSeconds,0.0f);
{
		GetWorldTimerManager().SetTimer(TimerFire,this,&ARifle::fireweapon,TimeBetweenShots,true,FirstDelay);
}

	
}

void ARifle::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerFire);
}

void ARifle::fireweapon()
{

	


	
	AActor* Owner = GetOwner();
	if (Owner) {



		APawn* MyOwner = Cast<APawn>(GetOwner());
		if(MyOwner)
		{
			APlayerController* PC = Cast<APlayerController>(MyOwner->GetController());
			if(PC)
			{
				PC->ClientPlayCameraShake(CameraShake);
            
                }
        
		}
		FVector Start;
		FRotator Rotation;
		Owner->GetActorEyesViewPoint(Start, Rotation);
		FVector EndLocation;
		FVector EyeLocation = Rotation.Vector();
		EndLocation = Start + (EyeLocation * 10000);

		FVector HitEnd = EndLocation;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Owner);
		Params.AddIgnoredActor(this);
		Params.bTraceComplex = true;
		Params.bReturnPhysicalMaterial = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, EndLocation, ECC_Visibility, Params))
		{
			AActor* DamagedActor = Hit.GetActor();

			EPhysicalSurface Surface = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
			float ActualDamage;
			if (Surface == SurfaceType2)
			{

				ActualDamage = BaseDamage * 3.0f;
				
			}
			else
			{
				ActualDamage = BaseDamage;
				
			}

			UGameplayStatics::ApplyPointDamage(DamagedActor, ActualDamage,EndLocation,Hit,Owner->GetInstigatorController(), this, DamageType);


			UParticleSystem* SelectedEffects;
			switch (Surface)
			{
				case SurfaceType1:
				case SurfaceType2:
				SelectedEffects = BloodEffects;
				break;
				default:
				SelectedEffects = DefaultEffects;
				break;
			
				
			}


			if (SelectedEffects) {
		
			

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffects, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			
			

			}
			HitEnd = Hit.ImpactPoint;
		}
		//DrawDebugLine(GetWorld(), Start, EndLocation, FColor::Red,false,1.0f,0,1.0f);
		if (MuzzelEffects) {

			UGameplayStatics::SpawnEmitterAttached(MuzzelEffects, MeshComp, MuzzelSocket);


		}
		
		if (SmokeEffects) {

			FVector SocketLocation = MeshComp->GetSocketLocation(MuzzelSocket);
			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeEffects, SocketLocation);
			if (TracerComp) {

				TracerComp->SetVectorParameter(Target, HitEnd);

			}


	
			
			
		}
	}

	FireRunTime = GetWorld()->GetTimeSeconds();
}
