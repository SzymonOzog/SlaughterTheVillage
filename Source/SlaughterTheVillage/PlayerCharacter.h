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
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupUndergroundInput(UInputComponent* PlayerInputComponent);
	virtual void Attack() override;

protected:
	virtual void BeginPlay() override;

private:
	void RotateSpellIndicator(float DeltaTime);
	void SetSpellIndicatorLocation() const;
	void SetupMissileSpawnParams();
	FTransform CalculateMissileSpawnTransform() const;
	void PreviousMissile();
	void NextMissile();
	void Dash();
	void RocketJump();
	void HideUnderground();
	void AimSpell();
	void CastSpell();

	struct FActorSpawnParameters MissileSpawnParams;
	FRotator SpellIndicatorRotator = FRotator(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ABaseMissile>> MissileClasses;
	TSubclassOf<class ABaseMissile> MissileClass;
	float MissileSpawnDistance = 150.0f;
	UPROPERTY(EditAnywhere)
	float MissileCooldown = 0.4f;
	float MissileLastCast = 0.0f;
	int32 MissileIndex;
	UPROPERTY(EditAnywhere)
	float DashCooldown = 1.0f;
	float DashLastCast = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float DashStrength = 300.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AExplosion> RocketJumpExplosionClass;
	UPROPERTY(EditAnywhere)
	float RocketJumpForwardDistance = 100.0f;
	UPROPERTY(EditAnywhere)
	float RocketJumpHeight = 1000.0f;
	UPROPERTY(EditAnywhere)
	float HideUndergroundLength = 1.5f;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADecalActor> SpellIndicatorClass;
	UPROPERTY()
	ADecalActor* SpellIndicator = nullptr;
	bool bIsAimingSpell = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseSpell> SpellClass;
};
