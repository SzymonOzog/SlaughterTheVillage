// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spikes.generated.h"

UCLASS()
class SLAUGHTERTHEVILLAGE_API ASpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpikes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		float Damage = 999.0f;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh = nullptr;
	UFUNCTION()
		virtual void OnSpikesOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
