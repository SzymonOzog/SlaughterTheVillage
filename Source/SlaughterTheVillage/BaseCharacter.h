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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(EditDefaultsOnly)
		float Speed = 1.0f;
	UFUNCTION(BlueprintPure)
		inline bool IsPlayerDead() const { return CurrentHealth <= 0; }
	UFUNCTION(BlueprintPure)
		inline float GetHealthPercent() const { return CurrentHealth / MaxHealth; }
private:
	UPROPERTY(EditDefaultsOnly)
		float AirControl = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float JumpHeight = 600.0f;
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere)
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABaseWeapon> WeaponClass;
	class ABaseWeapon* Weapon = nullptr;

	void SetupCharacterMovement();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Attack();
};
