// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Villager.h"
#include "BehaviorTree/BlackboardComponent.h"
void AAIController_Villager::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}

}