// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Villager.h"
UBTService_UpdatePlayer::UBTService_UpdatePlayer()
{
	NodeName = TEXT("Update Player if seen and in range");
}
void UBTService_UpdatePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		if (AVillager* ControlledVillager = Cast<AVillager>(OwnerComp.GetAIOwner()->GetCharacter()))
		{
			FVector PlayerLocation = PlayerPawn->GetActorLocation();
			FVector VillagerLocation = ControlledVillager->GetActorLocation();
			if (ControlledVillager->GetVisionRange() >= FVector::Distance(PlayerLocation, VillagerLocation))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
