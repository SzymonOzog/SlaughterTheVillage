// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SLAUGHTERTHEVILLAGE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
		
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure)
    inline bool IsPlayerDead() const { return CurrentHealth <= 0; }
	UFUNCTION(BlueprintPure)
    inline float GetHealthPercent() const { return CurrentHealth / MaxHealth; }
	inline float GetPlayerReach() const { return PlayerReach; }
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	virtual void Attack();
	void RotateToControllerYaw();
	inline bool IsCharacterAttacking() const { return bIsAttacking; }
	inline void PushBack(FVector PushDirection) { PushBack(PushDirection, PushBackDuration); }
	void PushBack(FVector PushDirection, float Duration);
	void StopPushBack() const;
	void HitSpikes();
	inline float GetSpikeHitTime() const { return SpikeHitTime; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly)
	float Speed = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float AirControl = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float JumpHeight = 600.0f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly)
	float PushBackDuration = 0.2f;
	float PlayerReach;
	float SpikeHitTime;
	float FrictionFactor;
	bool bIsAttacking = false;
	
	void SetupCharacterMovement();
	float CalculatePlayerReach() const;
	void HandleDeath();
	void StopAttacking();



};
