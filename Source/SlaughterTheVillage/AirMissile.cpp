// Fill out your copyright notice in the Description page of Project Settings.


#include "AirMissile.h"
#include "EngineGlobals.h"
#include "PushComponent.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

void AAirMissile::applySpecialEffect(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		FVector EnemyLocation = OtherActor->GetActorLocation();
		FVector PlayerLocation = SelfActor->GetActorLocation();
		FVector MoveAmount = calculateMoveAmount(PlayerLocation, EnemyLocation);
		Character->PushBack(MoveAmount);
	}
}

FVector AAirMissile::calculateMoveAmount(const FVector& PlayerLocation, const FVector& EnemyLocation)
{
	FVector MoveAmount = EnemyLocation - PlayerLocation;
	MoveAmount.Normalize();
	MoveAmount *= PushStrength;
	return MoveAmount;
}