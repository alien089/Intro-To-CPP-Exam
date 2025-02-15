// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryComponent.h"

// Sets default values for this component's properties
UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponInventoryComponent::AddWeapon(TSubclassOf<AGun> gun)
{
	WeaponInventory.Add(gun);
}

TSubclassOf<AGun> UWeaponInventoryComponent::GetActualWeapon(int index)
{
	return WeaponInventory[index];
}

bool UWeaponInventoryComponent::IsWeaponInventoryEmpty() const
{
	return WeaponInventory.IsEmpty();
}

int UWeaponInventoryComponent::GetWeaponInventorySize() const
{
	return WeaponInventory.Num();
}

void UWeaponInventoryComponent::AddMagazine(TSubclassOf<AGun> typeOfGun, int magazineCount)
{
	int actualAmmo = 0;
	
	if (AmmoMagazine.contains(typeOfGun))
		 actualAmmo = AmmoMagazine.find(typeOfGun)->second;
	
	AmmoMagazine.insert_or_assign(typeOfGun, actualAmmo + magazineCount);
	actualAmmo = AmmoMagazine.find(typeOfGun)->second;
}

bool UWeaponInventoryComponent::RemoveMagazine(TSubclassOf<AGun> typeOfGun)
{
	int ammo = AmmoMagazine.find(typeOfGun)->second;
	
	if (ammo > 0)
	{
		AmmoMagazine.insert_or_assign(typeOfGun, ammo - 1);
		return true;
	}
	return false;
}

bool UWeaponInventoryComponent::CheckIsAmmoMagazineEmpty(TSubclassOf<AGun> typeOfGun)
{
	int ammo = AmmoMagazine.find(typeOfGun)->second;
	if (ammo == 0)
		return true;
	return false;
}

