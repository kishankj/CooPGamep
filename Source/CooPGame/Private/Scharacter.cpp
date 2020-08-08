// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Scharacter.h"

#include <openexr/Deploy/include/ImathMath.h>


#include "Rifle.h"
#include "../../../../../../../Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/xkeycheck.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameFramework/PawnMovementComponent.h"
#include"CoopGame/Components/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AScharacter::AScharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
    SpringComp->bUsePawnControlRotation = true;
    SpringComp->SetupAttachment(RootComponent);


    GetMovementComponent()->NavAgentProps.bCanCrouch = true;
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringComp);
    DefaultFeildView = CameraComp->FieldOfView;
    CurrenFeildView = 20;
    InterpSpeed = 20;
    AttachWeaponSocketName = "MuzzelSocket";

    HealthCompo = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthCompo"));

    
  
    // int32 TweekValue = 0;
    // FAutoConsoleVariableRef(TEXT("TweekDebugSphere"),TweekValue,TEXT("DrawDebudLIneForSphere"),ECVF_Cheat);
}

// Called when the game starts or when spawned
void AScharacter::BeginPlay()
{
    Super::BeginPlay();
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    CurrentGun = GetWorld()->SpawnActor<ARifle>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator,
                                                SpawnParams);
    if (CurrentGun)
    {
        CurrentGun->SetOwner(this);
        CurrentGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                                      AttachWeaponSocketName);
    }

    HealthCompo->OnHealthChanged.AddDynamic(this, &AScharacter::HealthChanged);
}

void AScharacter::HealthChanged(UHealthComponent* HealthComp, float Health,
                                float HealthDelta, const class UDamageType* DamageType,
                                class AController* InstigatedBy, AActor* DamageCauser)
{
    if (Health <= 0.0f && !bDied)
    {
        bDied = true;
        GetMovementComponent()->StopMovementImmediately();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        
    }
}

void AScharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector() * Value);
}


void AScharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector() * Value);
}

void AScharacter::SetCrouch()
{
    Crouch();
}

void AScharacter::SetUnCrouch()
{
    UnCrouch();
}

void AScharacter::Zoom()
{
    bWantsToZoom = true;
}

void AScharacter::UnZoom()
{
    bWantsToZoom = false;
}


void AScharacter::fire()
{
    CurrentGun->Startfire();
}

void AScharacter::Unfire()
{
    CurrentGun->EndFire();
}

// Called every frame
void AScharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float SetFeildofView = bWantsToZoom ? CurrenFeildView : DefaultFeildView;
    float FinalViewPoint = FMath::FInterpTo(CameraComp->FieldOfView, SetFeildofView, DeltaTime, InterpSpeed);
    CameraComp->SetFieldOfView(FinalViewPoint);
}

// Called to bind functionality to input
void AScharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AScharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AScharacter::MoveRight);
    PlayerInputComponent->BindAxis("AddPitch", this, &AScharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("AddYaw", this, &AScharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AScharacter::SetCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AScharacter::SetUnCrouch);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AScharacter::Zoom);
    PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AScharacter::UnZoom);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AScharacter::fire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &AScharacter::Unfire);
}

FVector AScharacter::GetPawnViewLocation() const
{
    if (CameraComp)
    {
        return CameraComp->GetComponentLocation();
    }


    return Super::GetPawnViewLocation();
}
