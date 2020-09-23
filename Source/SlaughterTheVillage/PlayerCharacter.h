// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack() override;
private:
	struct FActorSpawnParameters MissileSpawnParams;
	void SetupMissileSpawnParams();
	void PreviousMissile();
	void NextMissile();
	void Dash();
	void AimSpell();
	void CastSpell();

	FTransform CalculateMissileSpawnTransform();
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ABaseMissile>> MissileClasses;
	TSubclassOf<class ABaseMissile> MissileClass;
	int32 MissileIndex;

	UPROPERTY(EditDefaultsOnly)
	float DashStrength = 300.0f;
	UPROPERTY(EditAnywhere)
	float MissileCooldown = 0.4f;
	float MissileLastCast = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADecalActor> SpellIndicatorClass;
	UPROPERTY()
	ADecalActor* SpellIndicator;
	bool bIsAimingSpell = false;
};
