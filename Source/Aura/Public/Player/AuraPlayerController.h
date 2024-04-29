// Copyright Lone Moose Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
};
