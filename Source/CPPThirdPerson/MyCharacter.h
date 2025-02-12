// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInventoryComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGun;

UCLASS()
class CPPTHIRDPERSON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxHealth = 10000;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> ActualGunClass;

	UPROPERTY()
	AGun* Gun;
	int ActualWeaponIndex = 0;
	
	UPROPERTY(EditDefaultsOnly)
	UWeaponInventoryComponent* InventoryComponent;


public:

	AMyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SwitchWeapon();
	
	virtual void TakeWeapon();
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION()
	void Shoot();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void LookUp(float AxisValue);
	UFUNCTION()
	void LookRight(float AxisValue);

	bool CheckIfGun();
};
