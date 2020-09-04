// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Wand.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API AWand : public ABaseWeapon
{
	GENERATED_BODY()
public:
	AWand();
	virtual void Attack() override;
protected:
	virtual void BeginPlay() override;
private:
	struct FActorSpawnParameters MissileSpawnParams;
	bool AreMissileSpawnParamsSet();
	void SetupMissileSpawnParams();
	FTransform CalculateMissileSpawnTransform();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseMissile> MissileClass;
};
