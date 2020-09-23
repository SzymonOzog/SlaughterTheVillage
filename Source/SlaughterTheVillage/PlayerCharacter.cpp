// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BaseMissile.h"
#include "Engine/World.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

APlayerCharacter::APlayerCharacter()
{

}
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupMissileSpawnParams();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAimingSpell && SpellIndicator)
	{
		FVector PlayerViewLocation;
		FRotator PlayerViewRotation;
		Controller->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
		FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * 5000.0f;
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility))
		{
			SpellIndicator->SetActorLocation(Hit.Location);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("NextMissile"), IE_Pressed, this, &APlayerCharacter::NextMissile);
	PlayerInputComponent->BindAction(TEXT("PreviousMissile"), IE_Pressed, this, &APlayerCharacter::PreviousMissile);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction(TEXT("CastSpell"), IE_Pressed, this, &APlayerCharacter::AimSpell);
	PlayerInputComponent->BindAction(TEXT("CastSpell"), IE_Released, this, &APlayerCharacter::CastSpell);
}

void APlayerCharacter::Attack()
{
	Super::Attack(); 
	if (GetWorld()->GetTimeSeconds() - MissileLastCast < MissileCooldown)
	{
		return;
	}
	MissileLastCast = GetWorld()->GetTimeSeconds();
	MissileClass = MissileClasses[MissileIndex];
	if (MissileClass)
	{
		GetWorld()->SpawnActor<ABaseMissile>(MissileClass, CalculateMissileSpawnTransform(), MissileSpawnParams);
	}
}

void APlayerCharacter::SetupMissileSpawnParams()
{
	MissileSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MissileSpawnParams.bNoFail = true;
	MissileSpawnParams.Owner = this;
	MissileSpawnParams.Instigator = this;
}

void APlayerCharacter::PreviousMissile()
{
	MissileIndex--;
	if (MissileIndex < 0)
	{
		MissileIndex = MissileClasses.Num() - 1;
	}
}

void APlayerCharacter::NextMissile()
{
	MissileIndex++;
	if (MissileIndex >= MissileClasses.Num())
	{
		MissileIndex = 0;
	}
}

void APlayerCharacter::Dash()
{
	PushBack(GetControlRotation().Vector() * DashStrength);
}

void APlayerCharacter::AimSpell()
{
	if (SpellIndicatorClass)
	{
		bIsAimingSpell = true;
		SpellIndicator = GetWorld()->SpawnActor<ADecalActor>(SpellIndicatorClass, GetActorLocation(), FRotator());
	}
}

void APlayerCharacter::CastSpell()
{
	bIsAimingSpell = false;
	if (SpellIndicator)
	{
		SpellIndicator->Destroy();
	}
}

FTransform APlayerCharacter::CalculateMissileSpawnTransform()
{
	FTransform MissileSpawnTransform;
	FRotator ControllerRotation = GetControlRotation();
	MissileSpawnTransform.SetLocation(ControllerRotation.Vector() * 150.0f + GetActorLocation());
	MissileSpawnTransform.SetRotation(ControllerRotation.Quaternion());
	return MissileSpawnTransform;
}

