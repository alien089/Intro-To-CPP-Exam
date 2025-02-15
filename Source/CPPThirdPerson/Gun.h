// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

//class USkeletalMeshComponent;

UCLASS()
class CPPTHIRDPERSON_API AGun : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Particle System")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Particle System")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stats")
	int TotalAmountOfAmmo = 10;
	int CurrentAmmo = 0;
	
public:
	// Sets default values for this actor's properties
	AGun();

	virtual void Tick(float DeltaTime) override;

	void PullTrigger();
	void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool CheckForAmmo() const;
};
