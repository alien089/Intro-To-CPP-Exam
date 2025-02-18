// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpBase::APickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnOverlapBegin);
}

void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickUpBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AMyCharacter>(OtherActor);
	player->GetInventoryComponent()->AddMagazine(TypeOfGun, AmountOfMagazine);
	DestroyPickUp();
}

void APickUpBase::DestroyPickUp()
{
	Destroy();
}
