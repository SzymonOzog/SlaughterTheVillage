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
	FTransform CalculateMissileSpawnTransform();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseMissile> MissileClass;
};
