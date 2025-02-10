// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Components/ActorComponent.h"
#include "CPPThirdPerson/Gun.h"
#include "WeaponInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTHIRDPERSON_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponInventoryComponent();

	UPROPERTY(EditAnywhere, Category= "WeaponList")
	TArray<TSubclassOf<AGun>> WeaponInventory;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
