// Copyright Lone Moose Games


#include "Player/AuraPlayerController.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedLocalPlayerSubsystemc>(
		GetLocalPlayer());
	// UEnahancedLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnahancedLocalPlayerSubsystem>();
	check(Subsystem);
}
