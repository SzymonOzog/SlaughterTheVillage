// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SlaughterTheVillageGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"

void ASlaughterTheVillageGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (StartMessageClass)
	{
		StartMessage = CreateWidget<UUserWidget>(GetWorld(), StartMessageClass);
		if (StartMessage)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			PlayerController->InputComponent->BindAction(TEXT("StartGame"), IE_Pressed, this, &ASlaughterTheVillageGameModeBase::StartGame);
			UGameplayStatics::GetPlayerPawn(this, 0)->DisableInput(PlayerController);

			StartMessage->AddToViewport();
			GetWorldTimerManager().SetTimer(InputTimer, this, &ASlaughterTheVillageGameModeBase::WaitForInput, 0.5f, true, 0.5f);
		}
	}
}

void ASlaughterTheVillageGameModeBase::WaitForInput()
{
	if (bPlayerStartedGame)
	{
		StartMessage->RemoveFromViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		UGameplayStatics::GetPlayerPawn(this, 0)->EnableInput(PlayerController);

		GetWorldTimerManager().ClearTimer(InputTimer);
	}
}

void ASlaughterTheVillageGameModeBase::StartGame()
{
	bPlayerStartedGame = true;
}
