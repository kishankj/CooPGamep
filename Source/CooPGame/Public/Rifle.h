// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;


UCLASS()
class COOPGAME_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapons")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapons")
	UParticleSystem* BloodEffects;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapons")
    UParticleSystem* DefaultEffects;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapons")
	float BaseDamage;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Weapons")
	FName MuzzelSocket;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	FName Target;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapons")
	UParticleSystem* MuzzelEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	UParticleSystem* SmokeEffects;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category= "Weapons")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category= "Weapons")
	TSubclassOf<UCameraShake> CameraShake;

	UFUNCTION(BLueprintCallable, Category = "Weapons")
    virtual void fireweapon();

	FTimerHandle TimerFire;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category= "Weapons")
	float RatePerMinute;

	float FireRunTime;

	float TimeBetweenShots;
	
	UFUNCTION()
	void SetWeaponRotation();
	UPROPERTY()
	FName AxisValue;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
     void Startfire();

	 void EndFire();
};
