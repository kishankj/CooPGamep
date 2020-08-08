// Fill out your copyright notice in the Description page of Project Settings.

#include "Robot.h"


#include "DrawDebugHelpers.h"
#include "AI/NavigationSystemBase.h"
#include"Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include"NavigationSystem.h"
#include "NavigationPath.h"
#include "Components/HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ARobot::ARobot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCanEverAffectNavigation(false);
	
	HealthCompo = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	
	ForceStrength = 1000;
RequiredDistanceToTarget = 100;
	MeshComp->SetMaterial(0,MatInterface);
}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();
HealthCompo->OnHealthChanged.AddDynamic(this,&ARobot::HealthChangedAction);
	NextPoints = MovingPoint();
	
}
void ARobot::HealthChangedAction(UHealthComponent* HealthComp, float Health,
                                             float HealthDelta, const class UDamageType* DamageType,
                                             class AController* InstigatedBy, AActor* DamageCauser)
{

	if (Matinst == nullptr)
	{
		Matinst = 	MeshComp->CreateDynamicMaterialInstance(0,MatInterface);
		
	}
	if (Matinst)
	{
		Matinst->SetScalarParameterValue("DamageTime",GetWorld()->TimeSeconds);
	}
	if(Health <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),RobotDieEffect,GetActorLocation());
		Destroy();
		
	}
}





FVector ARobot::MovingPoint()
{
ACharacter* CurrentPlayer = UGameplayStatics::GetPlayerCharacter(this,0);
UNavigationPath* PathNav = UNavigationSystemV1::FindPathToActorSynchronously(this,GetActorLocation(),CurrentPlayer);
	if(PathNav->PathPoints.Num()>1)
{
	return PathNav->PathPoints[1];
	
}
	
	
return GetActorLocation();
	
	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
float DistanceToTarget = (GetActorLocation() - NextPoints).Size();
	
	
	NextPoints = MovingPoint();
		
	
	

		FVector ForceDirectoin = (NextPoints - GetActorLocation());
		ForceDirectoin.Normalize();
		ForceDirectoin *= ForceStrength; 
	
		MeshComp->AddForce(ForceDirectoin,NAME_None,true);
	
		DrawDebugSphere(GetWorld(),NextPoints,20,12,FColor::Green,false,1,1);
}


