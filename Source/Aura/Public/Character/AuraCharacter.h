// Copyright Lone Moose Games

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void BeginPlay() override;
	void InitAbilityActorInfo();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
