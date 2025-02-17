// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAI.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "CPPThirdPersonGameMode.h"


// Sets default values
ACharacterAI::ACharacterAI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	InventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>("Inventory");
	this->AddInstanceComponent(InventoryComponent);
}

// Called when the game starts or when spawned
void ACharacterAI::BeginPlay()
{
	Super::BeginPlay();

	SwitchWeapon();
	CurrentHealth = MaxHealth;
}

// Called every frame
void ACharacterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACharacterAI::CheckIfGun() const
{
	if (Gun == nullptr)
		return false;
	else
		return true;
}

void ACharacterAI::Shoot()
{
	if (!CheckIfGun()) return;
	Gun->PullTrigger();

}

void ACharacterAI::TryReload()
{
	if (InventoryComponent->CheckIsAmmoMagazineEmpty(ActualGunClass)) return;
	InventoryComponent->RemoveMagazine(ActualGunClass);
	Gun->Reload();
}

void ACharacterAI::Respawn()
{
	
}

float ACharacterAI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;

	if (IsDead())
	{
		ACPPThirdPersonGameMode* GameMode = GetWorld()->GetAuthGameMode<ACPPThirdPersonGameMode>();

		if (GameMode != nullptr)
		GameMode->PawnKilled(this);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
	}

	return DamageToApply;
}

void ACharacterAI::SwitchWeapon()
{
	if (ActualWeaponIndex + 1 < InventoryComponent->GetWeaponInventorySize())
		ActualWeaponIndex++;
	else
		ActualWeaponIndex = 0;

	if (CheckIfGun())
	{
		Gun->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Gun->Destroy();
	}
	
	TakeWeapon();
}

void ACharacterAI::TakeWeapon()
{
	if (InventoryComponent->IsWeaponInventoryEmpty()) return;
	ActualGunClass = InventoryComponent->GetActualWeapon(ActualWeaponIndex);
	Gun = GetWorld()->SpawnActor<AGun>(ActualGunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	if (Gun == nullptr) return;
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool ACharacterAI::IsDead() const
{
	return CurrentHealth <= 0;
}