// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureFlagGameMode.h"

#include "CharacterAI.h"
#include "GameFramework/Character.h"

void ACaptureFlagGameMode::PawnKilled(ACharacter* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* player = Cast<APlayerController>(PawnKilled->GetController());
	if (player != nullptr)
	{
		EndGame(false);
		return;
	}
	ACharacterAI* enemy = Cast<ACharacterAI>(PawnKilled);
	enemy->Respawn();
}

void ACaptureFlagGameMode::EndGame(bool bIsPlayerWinner)
{
	if (bIsPlayerWinner)
	{
		//show victory
	}
	else
	{
		//show defeat
	}
}

void ACaptureFlagGameMode::AddFlagTic()
{
	iFlagTic++;
}
