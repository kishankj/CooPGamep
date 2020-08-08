// Fill out your copyright notice in the Description page of Project Settings.

#include "RProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include"DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include"Particles/ParticleSystem.h"
#include"Components/SkeletalMeshComponent.h"
#include"Particles/ParticleSystemComponent.h"

void ARProjectile::fireweapon()
{
	AActor* Owner = GetOwner();
	if (Owner && Projectile)
	{
		FVector Start;
		FRotator Rotation;
		Owner->GetActorEyesViewPoint(Start, Rotation);
		FVector EyeLocation = Rotation.Vector();
		FVector StartLocation = MeshComp->GetSocketLocation(MuzzelSocket);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(Projectile,StartLocation,Rotation, Params);

	}
}
