// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "AIController.h"
#include "BaseCharacter.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{

}
EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (ABaseCharacter* ControlledCharacter = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		ControlledCharacter->Attack();
	}
	else
	{
		return EBTNodeResult::Type::Failed;
	}
	return EBTNodeResult::Type::Succeeded;
}
