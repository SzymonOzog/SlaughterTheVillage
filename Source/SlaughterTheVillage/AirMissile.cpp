// Fill out your copyright notice in the Description page of Project Settings.


#include "AirMissile.h"
#include "EngineGlobals.h"
#include "PushComponent.h"
#include "BaseCharacter.h"

void AAirMissile::applySpecialEffect(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ABaseCharacter>(OtherActor))
	{
		FVector EnemyLocation = OtherActor->GetActorLocation();
		FVector PlayerLocation = SelfActor->GetActorLocation();
		FVector MoveAmount = calculateMoveAmount(PlayerLocation, EnemyLocation);
		UPushComponent* PushComponent = NewObject<UPushComponent>(OtherActor, TEXT("PushComponent"));
		PushComponent->SetDestination(EnemyLocation + MoveAmount);
		OtherActor->AddInstanceComponent(PushComponent);
		PushComponent->RegisterComponent();
	}
}

FVector AAirMissile::calculateMoveAmount(const FVector& PlayerLocation, const FVector& EnemyLocation)
{
	FVector MoveAmount = EnemyLocation - PlayerLocation;
	float Scale = MoveAmount.GetAbsMax() / PushDistance;
	MoveAmount /= Scale;
	return MoveAmount;
}