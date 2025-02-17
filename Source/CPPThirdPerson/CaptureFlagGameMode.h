// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPThirdPersonGameMode.h"
#include "CaptureFlagGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPTHIRDPERSON_API ACaptureFlagGameMode : public ACPPThirdPersonGameMode
{
	GENERATED_BODY()
private:
	int iFlagTic = 0;
private:
	void EndGame(bool bIsPlayerWinner);
	
public:
	void AddFlagTic();
	virtual void PawnKilled(ACharacter* PawnKilled) override;

};
