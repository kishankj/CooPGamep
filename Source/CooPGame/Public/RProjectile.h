// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rifle.h"
#include "RProjectile.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ARProjectile : public ARifle
{
	GENERATED_BODY()

protected:
	virtual void fireweapon() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	TSubclassOf<AActor>  Projectile;
};
