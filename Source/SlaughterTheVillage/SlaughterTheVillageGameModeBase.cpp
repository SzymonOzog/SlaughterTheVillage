// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SlaughterTheVillageGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "PlayerCharacter.h"
#include "Villager.h"
#include "EngineUtils.h"

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
void ASlaughterTheVillageGameModeBase::CharacterKilled(ABaseCharacter* CharacterKilled)
{
	if (Cast<APlayerCharacter>(CharacterKilled))
	{
		EndGame(false);
		return;
	}
	for (TActorIterator<AVillager> It(GetWorld()); It; ++It)
	{
		if (!It->IsPlayerDead())
		{
			return;
		}
	}
	//No Villagers left, player has won
	EndGame(true);
}

void ASlaughterTheVillageGameModeBase::WaitForInput()
{
	if (bPlayerStartedGame)
	{
		StartMessage->RemoveFromViewport();
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		UGameplayStatics::GetPlayerPawn(this, 0)->EnableInput(PlayerController);

		GetWorldTimerManager().ClearTimer(InputTimer);

		CreateHUD();
	}
}

void ASlaughterTheVillageGameModeBase::StartGame()
{
	bPlayerStartedGame = true;
}

void ASlaughterTheVillageGameModeBase::CreateHUD()
{
	if (HUD_Class)
	{
		UUserWidget* HUD = CreateWidget<UUserWidget>(GetWorld(), HUD_Class);
		if (HUD)
		{
			HUD->AddToViewport();
		}
	}
}

void ASlaughterTheVillageGameModeBase::EndGame(bool bPlayerWon)
{
	if (bPlayerWon)
	{
		if (WinMessageClass)
		{
			UUserWidget* WinMessage = CreateWidget<UUserWidget>(GetWorld(), WinMessageClass);
			if (WinMessage)
			{
				WinMessage->AddToViewport();
			}
		}
	}
	else
	{
		if (LoseMessageClass)
		{
			UUserWidget* LoseMessage = CreateWidget<UUserWidget>(GetWorld(), LoseMessageClass);
			if (LoseMessage)
			{
				LoseMessage->AddToViewport();
			}
		}
	}
}
