// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpell.h"
#include "SpellMeteor.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API ASpellMeteor : public ABaseSpell
{
	GENERATED_BODY()
public:
	ASpellMeteor();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
};
