// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpGun.h"

#include "MyCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpGun::APickUpGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickUpGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickUpGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickUpGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	player->GetInventoryComponent()->AddWeapon(TypeOfGun);
	player->SwitchWeapon();
	DestroyPickUp();
}
