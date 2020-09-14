// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Villager.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API AVillager : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AVillager();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;
	inline float GetVisionRange() { return VisionRange; }
private:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class ABaseWeapon>> WeaponClasses;
	UPROPERTY()
		class ABaseWeapon* Weapon = nullptr;
	UPROPERTY(EditAnywhere)
		float VisionRange = 1000.0f;
};
