// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"
#include "BaseWeapon.h"
AVillager::AVillager()
{

}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVillager::Attack()
{
	Super::Attack();
	if (Weapon)
	{
		Weapon->Attack();
	}
}

void AVillager::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<ABaseWeapon> WeaponClass = WeaponClasses[FMath::RandRange(0, WeaponClasses.Num() - 1)];
	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
		if (Weapon)
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			Weapon->SetOwner(this);
			Weapon->SetInstigator(this);
		}
	}
}