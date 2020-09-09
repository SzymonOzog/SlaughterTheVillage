// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Villager.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API AAIController_Villager : public AAIController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;
private:
    UPROPERTY(EditAnywhere)
        UBehaviorTree* AIBehavior;
};
