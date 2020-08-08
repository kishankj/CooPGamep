// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "PhysicsEngine/RadialForceComponent.h"


#include "BombBox.generated.h"
class UMaterial;
class UStaticMeshComponent;
class UHealthComponent;
class UParticleSystem;
class URadialForceComponent;
UCLASS()
class COOPGAME_API ABombBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Mesh")
	FName Socketer;

	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly,Category="Health")
	UHealthComponent* HealthComponents;
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterial* RedMaterial;
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterial* DarkMaterial;
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	URadialForceComponent* RadialForce;
	UFUNCTION()
	void OnBlast(UHealthComponent* HealthComp, float Health,
                                             float HealthDelta, const class UDamageType* DamageType,
                                             class AController* InstigatedBy, AActor* DamageCauser);
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	float ImpulseStrength;
	bool bBlasted;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
