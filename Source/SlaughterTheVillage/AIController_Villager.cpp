// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Villager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BrainComponent.h"
void AAIController_Villager::StopExecutingBehaviour() const
{
	BrainComponent->PauseLogic("");
}
void AAIController_Villager::StartExecutingBehaviour() const
{
	BrainComponent->ResumeLogic("");
	BrainComponent->RestartLogic();
}
void AAIController_Villager::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}