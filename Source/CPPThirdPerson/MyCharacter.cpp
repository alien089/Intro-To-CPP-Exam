// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "CPPThirdPersonGameMode.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	InventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>("Inventoryblabla");
	this->AddInstanceComponent(InventoryComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyCharacter::LookRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), EInputEvent::IE_Pressed, this, &AMyCharacter::SwitchWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AMyCharacter::TryReload);
}


void AMyCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMyCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMyCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(-AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

bool AMyCharacter::CheckIfGun() const
{
	if (Gun == nullptr)
		return false;
	else
		return true;
}

void AMyCharacter::Shoot()
{
	if (!CheckIfGun()) return;
	Gun->PullTrigger();

}

void AMyCharacter::TryReload()
{
	if (!CheckIfGun()) return;
	if (InventoryComponent->CheckIsAmmoMagazineEmpty(ActualGunClass)) return;
	InventoryComponent->RemoveMagazine(ActualGunClass);
	Gun->Reload();
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMyCharacter::SwitchWeapon()
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

void AMyCharacter::TakeWeapon()
{
	if (InventoryComponent->IsWeaponInventoryEmpty()) return;
	ActualGunClass = InventoryComponent->GetActualWeapon(ActualWeaponIndex);
	Gun = GetWorld()->SpawnActor<AGun>(ActualGunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	if (Gun == nullptr) return;
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AMyCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}