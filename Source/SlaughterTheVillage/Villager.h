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
	virtual void Tick(float DeltaTime) override;
	virtual void Attack() override;
	inline float GetVisionRange() const { return VisionRange; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class ABaseWeapon>> WeaponClasses;
	UPROPERTY()
	class ABaseWeapon* Weapon = nullptr;
	UPROPERTY(EditAnywhere)
	float VisionRange = 1000.0f;
};
