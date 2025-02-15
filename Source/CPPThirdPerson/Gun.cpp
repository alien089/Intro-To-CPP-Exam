// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	CurrentAmmo = TotalAmountOfAmmo;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::CheckForAmmo() const
{
	if (CurrentAmmo <= 0)	
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Out of Ammo"));
		return false;
	}
	return true;
}

void AGun::PullTrigger()
{
	if (!CheckForAmmo()) return;
	CurrentAmmo--;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("Muzzle"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bSuccess)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor == nullptr) return;

		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		FVector ShotDirection = Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, (-ShotDirection).Rotation());

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

	}


	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Green, true);
}

void AGun::Reload()
{
	CurrentAmmo = TotalAmountOfAmmo;
}

