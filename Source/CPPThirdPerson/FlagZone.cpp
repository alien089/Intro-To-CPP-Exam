// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagZone.h"

#include "CaptureFlagGameMode.h"
#include "MyCharacter.h"

// Sets default values
AFlagZone::AFlagZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFlagZone::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AFlagZone::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AFlagZone::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(FlagTimer, this, &AFlagZone::AddTic, 1.0f, true);
	GetWorldTimerManager().PauseTimer(FlagTimer);
}

// Called every frame
void AFlagZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlagZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* player = Cast<AMyCharacter>(OtherActor);
	if (player != nullptr)
		GetWorldTimerManager().UnPauseTimer(FlagTimer);
}

void AFlagZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* player = Cast<AMyCharacter>(OtherActor);
	if (player != nullptr)
		GetWorldTimerManager().PauseTimer(FlagTimer);
}

void AFlagZone::AddTic() const
{
	ACaptureFlagGameMode* GameMode = GetWorld()->GetAuthGameMode<ACaptureFlagGameMode>();
	if (GameMode != nullptr)
		GameMode->AddFlagTic();
}

