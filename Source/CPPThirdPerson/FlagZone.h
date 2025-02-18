// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FlagZone.generated.h"

UCLASS()
class CPPTHIRDPERSON_API AFlagZone : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle FlagTimer;
	
public:
	UPROPERTY(EditAnywhere, Category="FlagTrigger")
	UBoxComponent* Trigger;
	
	UPROPERTY(EditAnywhere, Category="Flag")
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	AFlagZone();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AddTic() const;
};
