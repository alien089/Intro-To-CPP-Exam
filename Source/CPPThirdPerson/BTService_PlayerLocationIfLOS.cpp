// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfLOS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"


UBTService_PlayerLocationIfLOS::UBTService_PlayerLocationIfLOS()
{
	NodeName = "Update Player Location If In LOS";
}

void UBTService_PlayerLocationIfLOS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn == nullptr) return;
	if (OwnerComp.GetAIOwner() == nullptr) return;

	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

}
