// Fill out your copyright notice in the Description page of Project Settings.


#include "AirMissile.h"
#include "EngineGlobals.h"
#include "PushComponent.h"
#include "BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"

void AAirMissile::applySpecialEffect(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
	{
		FVector EnemyLocation = OtherActor->GetActorLocation();
		FVector PlayerLocation = SelfActor->GetActorLocation();
		FVector MoveAmount = calculateMoveAmount(PlayerLocation, EnemyLocation);
		UE_LOG(LogTemp, Warning, TEXT("MoveAmount is %s"), *MoveAmount.ToString())
		UE_LOG(LogTemp, Warning, TEXT("Old velocity is %s"), *Character->GetMovementComponent()->Velocity.ToString())
		//Velocity behaves different while airbourne so it needs to be scaled down
		//to avoid launching player too far
		if (Character->GetMovementComponent()->IsFalling())
		{
			MoveAmount /= AirbourneScaleDown; 
		}
		Character->GetMovementComponent()->Velocity += MoveAmount;
		UE_LOG(LogTemp, Warning, TEXT("New velocity is %s"), *Character->GetMovementComponent()->Velocity.ToString())
	}
}

FVector AAirMissile::calculateMoveAmount(const FVector& PlayerLocation, const FVector& EnemyLocation)
{
	FVector MoveAmount = EnemyLocation - PlayerLocation;
	MoveAmount.Normalize();
	MoveAmount *= PushStrength;
	return MoveAmount;
}