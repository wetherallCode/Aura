// Copyright Lone Moose Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

private:
	FName WeaponHandSocket{WeaponHandSocket};

public:
	FORCEINLINE FName GetWeaponHandSocketName() const { return WeaponHandSocket; }
};
