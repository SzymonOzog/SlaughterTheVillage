// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlaughterTheVillageGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SLAUGHTERTHEVILLAGE_API ASlaughterTheVillageGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void CharacterKilled(class ABaseCharacter* CharacterKilled);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUD_Class;
	UPROPERTY()
		UUserWidget* HUD;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseMessageClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinMessageClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> StartMessageClass;
	UPROPERTY()
		UUserWidget* StartMessage;


	bool bPlayerStartedGame = false;
	struct FTimerHandle InputTimer;

	void EndGame(bool bPlayerWon) const;
	void StartGame();
	void WaitForInput();
	void CreateHUD();
};
