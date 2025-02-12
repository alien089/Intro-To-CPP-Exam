// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpGun.h"

#include "Components/SphereComponent.h"

// Sets default values
APickUpGun::APickUpGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
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

