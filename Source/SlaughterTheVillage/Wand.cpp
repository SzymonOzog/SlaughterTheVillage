// Fill out your copyright notice in the Description page of Project Settings.


#include "Wand.h"
#include "BaseMissile.h"
#include "Engine/World.h"
AWand::AWand()
{
}

void AWand::Attack()
{
	Super::Attack();
	if (!AreMissileSpawnParamsSet())
	{
		SetupMissileSpawnParams();
	}
	if (MissileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("MissileSpawned"))
		GetWorld()->SpawnActor<ABaseMissile>(MissileClass, CalculateMissileSpawnTransform(), MissileSpawnParams);
	}
}

void AWand::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Wands begin play"))
}

bool AWand::AreMissileSpawnParamsSet()
{
	return MissileSpawnParams.Owner && MissileSpawnParams.Instigator;
}

void AWand::SetupMissileSpawnParams()
{
	MissileSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MissileSpawnParams.bNoFail = true;
	MissileSpawnParams.Owner = GetOwner();
	UE_LOG(LogTemp, Error, TEXT("%s is the owner"), *GetOwner()->GetName())

	MissileSpawnParams.Instigator = Cast<APawn>(GetOwner());
}

FTransform AWand::CalculateMissileSpawnTransform()
{
	if (!AreMissileSpawnParamsSet())
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Missile Spawn Params set"), *GetName())
		return FTransform();
	}
	FTransform MissileSpawnTransform;
	FRotator ControllerRotation = MissileSpawnParams.Instigator->GetControlRotation();
	MissileSpawnTransform.SetLocation(ControllerRotation.Vector() * 150.0f + MissileSpawnParams.Instigator->GetActorLocation());
	MissileSpawnTransform.SetRotation(ControllerRotation.Quaternion());
	UE_LOG(LogTemp, Warning, TEXT("transform is %s "), *MissileSpawnTransform.ToString())

	return MissileSpawnTransform;
}
