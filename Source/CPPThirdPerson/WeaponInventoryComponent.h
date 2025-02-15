// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <map>
#include "Components/ActorComponent.h"
#include "CPPThirdPerson/Gun.h"
#include "WeaponInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTHIRDPERSON_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	std::map<TSubclassOf<AGun>, int> AmmoMagazine;
	TArray<TSubclassOf<AGun>> WeaponInventory;
	
public:	
	// Sets default values for this component's properties
	UWeaponInventoryComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddWeapon(TSubclassOf<AGun> gun);
	TSubclassOf<AGun> GetActualWeapon(int index);
	bool IsWeaponInventoryEmpty() const;
	int GetWeaponInventorySize() const;

	void AddMagazine(TSubclassOf<AGun> typeOfGun, int magazineCount);
	bool RemoveMagazine(TSubclassOf<AGun> typeOfGun);
	bool CheckIsAmmoMagazineEmpty(TSubclassOf<AGun> typeOfGun);
};
