// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureFlagGameMode.h"
#include <string>
#include "CharacterAI.h"
#include "MyPlayerController.h"
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

void ACaptureFlagGameMode::AddFlagTic()
{
	iFlagTic++;
	if (iFlagTic == TargetPoints)
		EndGame(true);
	if (iFlagTic <= TargetPoints)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Actual Points: %d"), iFlagTic));
}

void ACaptureFlagGameMode::EndGame(bool bIsPlayerWinner) const
{
	AMyPlayerController* controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	controller->GameHasEnded(controller->GetPawn(), bIsPlayerWinner);
}
