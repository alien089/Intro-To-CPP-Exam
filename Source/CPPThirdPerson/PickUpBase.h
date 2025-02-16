// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class CPPTHIRDPERSON_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category="PickUp")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere, Category="PickUp")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="PickUp")
	TSubclassOf<AGun> TypeOfGun;
	
	AMyCharacter* player;
	
public:	
	// Sets default values for this actor's properties
	APickUpBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void DestroyPickUp();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
