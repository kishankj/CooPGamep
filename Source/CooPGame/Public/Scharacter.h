// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rifle.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "Scharacter.generated.h"
class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class ARifle;
UCLASS()
class COOPGAME_API AScharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AScharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthCompo;
    UFUNCTION()
	void HealthChanged(UHealthComponent* HealthComp, float Health,
                                                 float HealthDelta, const class UDamageType* DamageType,
                                                 class AController* InstigatedBy, AActor* DamageCauser);
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	UFUNCTION()
	void SetCrouch();

	UFUNCTION()
	void SetUnCrouch();
	UFUNCTION()
	void Zoom();
	UFUNCTION()
	void UnZoom();
	ARifle* CurrentGun;
	UPROPERTY(EditDefaultsOnly,Category="FOV")
	TSubclassOf<ARifle> StarterWeaponClass;
	bool bWantsToZoom;
	UPROPERTY(EditDefaultsOnly,Category="FOV")
	float DefaultFeildView;
	UPROPERTY(EditDefaultsOnly,Category="FOV")
	float CurrenFeildView;
	UPROPERTY(EditDefaultsOnly,Category="FOV")
	float InterpSpeed;

	UPROPERTY(VisibleDefaultsOnly,Category="FOV")
	FName AttachWeaponSocketName;
	void fire();
	
	void Unfire();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual FVector GetPawnViewLocation() const override;

	UPROPERTY(BlueprintReadOnly,Category="DieStatus")
	bool bDied;
	
	
};
