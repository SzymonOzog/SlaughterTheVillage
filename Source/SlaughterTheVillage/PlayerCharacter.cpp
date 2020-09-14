// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BaseMissile.h"
#include "Engine/World.h"

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
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("NextMissile"), IE_Pressed, this, &APlayerCharacter::NextMissile);
	PlayerInputComponent->BindAction(TEXT("PreviousMissile"), IE_Pressed, this, &APlayerCharacter::PreviousMissile);
}

void APlayerCharacter::Attack()
{
	Super::Attack();
	if (GetWorld()->GetTimeSeconds() - MissileLastCast < MissileCooldown)
	{
		return;
	}
	MissileLastCast = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Atttacked in player class"))
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

FTransform APlayerCharacter::CalculateMissileSpawnTransform()
{
	FTransform MissileSpawnTransform;
	FRotator ControllerRotation = GetControlRotation();
	MissileSpawnTransform.SetLocation(ControllerRotation.Vector() * 150.0f + GetActorLocation());
	MissileSpawnTransform.SetRotation(ControllerRotation.Quaternion());
	return MissileSpawnTransform;
}

