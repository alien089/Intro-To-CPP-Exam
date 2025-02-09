// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviour == nullptr) return;

	RunBehaviorTree(AIBehaviour);

	GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
}


//void AShooterAIController::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//
//
//	if (LineOfSightTo(PlayerPawn))
//	{
//		FVector PlayerLocation = PlayerPawn->GetActorLocation();
//		//Set player location
//		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
//		//Set last known location
//		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
//	}
//	else
//	{
//		//clear player location
//		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
//	}
//}



bool AShooterAIController::IsDead() const
{
	AMyCharacter* ControlledCharacter = Cast<AMyCharacter>(GetPawn());

	if (ControlledCharacter != nullptr)
		return ControlledCharacter->IsDead();

	return true;
}