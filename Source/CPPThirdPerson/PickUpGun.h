// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpGun.generated.h"

UCLASS()
class CPPTHIRDPERSON_API APickUpGun : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category="PickUp")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere, Category="PickUp")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="PickUp")
	TSubclassOf<AGun> TypeOfGun;
	
public:
	// Sets default values for this actor's properties
	APickUpGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
