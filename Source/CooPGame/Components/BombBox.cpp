// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBox.h"


#include "UnitConversion.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"



// Sets default values
ABombBox::ABombBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	HealthComponents = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponents"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComp->SetSimulatePhysics(true);
	RedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	DarkMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DarkMaterial"));
	ExplosionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffect"));
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetAutoActivate(false);
	RadialForce->SetupAttachment(MeshComp);
	RadialForce->Radius = 300;
	RadialForce->bImpulseVelChange = true;
	RadialForce ->bIgnoreOwningActor = true;
	
	Socketer = "Socketer";
	ImpulseStrength = 400;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ABombBox::BeginPlay()
{
	Super::BeginPlay();

	HealthComponents->OnHealthChanged.AddDynamic(this,&ABombBox::OnBlast);
MeshComp->SetMaterial(0,RedMaterial);
	
	
	
}

void ABombBox::OnBlast(UHealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{

	
	if(bBlasted)
	{

		return;
	}

if(Health<=0.0f)
{
	bBlasted = true;
	MeshComp->SetMaterial(0,DarkMaterial);
	
	FVector BoostIntensity = FVector::UpVector * ImpulseStrength;
	
	MeshComp->AddImpulse(BoostIntensity,NAME_None,true);
		
		UGameplayStatics::SpawnEmitterAttached(ExplosionEffect,MeshComp,Socketer);
		
	RadialForce->FireImpulse();
	
}

	
	
}

// Called every frame
void ABombBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

