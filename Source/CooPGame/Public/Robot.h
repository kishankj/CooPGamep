// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Robot.generated.h"

class UStaticMeshComponent;
UCLASS()
class COOPGAME_API ARobot : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ARobot();
    /**
     * \brief 
     */
    UPROPERTY(VisibleDefaultsOnly,Category="Components")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly,Category="Materials")
    UHealthComponent* HealthCompo;

    FVector MovingPoint();

    UPROPERTY(EditDefaultsOnly,Category="Materials")
    UMaterialInterface* MatInterface;
    UPROPERTY(EditDefaultsOnly,Category="Materials")
    UMaterialInstanceDynamic* Matinst;
    bool IsRobotDied;
    UPROPERTY(EditDefaultsOnly,Category="Materials")
    UParticleSystem* RobotDieEffect;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly,Category="Components")
    float ForceStrength;
    UPROPERTY(EditDefaultsOnly,Category="Components")
    float RequiredDistanceToTarget;
    FVector NextPoints;

    UFUNCTION()
    void HealthChangedAction(UHealthComponent* HealthComp, float Health,
                                             float HealthDelta, const class UDamageType* DamageType,
                                             class AController* InstigatedBy, AActor* DamageCauser);
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};



