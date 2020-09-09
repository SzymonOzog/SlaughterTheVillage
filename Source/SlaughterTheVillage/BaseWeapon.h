// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLAUGHTERTHEVILLAGE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ABaseWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Attack();
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		float Damage;
	UPROPERTY(EditDefaultsOnly)
		float Range;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;
};
