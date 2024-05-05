// Copyright Lone Moose Games


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Perform trace and handle the highlighting and highlight the actors we hit that implement enemy interface
	CursorTrace();
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	// UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<
	// 	UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind your input actions here
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	// Get hit result under cursor
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	// This sets the LastActor to the actor we hit every frame
	if (CursorHit.bBlockingHit)
	{
		LastActor = ThisActor;
		ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
		/*
		 * Line Trace from cursor. Several Scenarios:
		 *  A. LastActor is null and This Actor is null
		 *    - Do Nothing
		 *  B. LastActor is null and This Actor is valid
		 *    - Highlight ThisActor
		 *	C. LastActor is valid and This Actor is null
		 *		- UnHighlight LastActor
		 *	D. LastActor is valid and This Actor is valid, LastActor != ThisActor
		 *		- Highlight ThisActor and UnHighlight LastActor
		 *	E. LastActor is valid and This Actor is valid, LastActor == ThisActor
		 *		- Do Nothing
		 */
		if (LastActor == nullptr)
		{
			if (ThisActor != nullptr)
			{
				// Case B
				ThisActor->HighlightActor();
			}
			else
			{
				// Case A - Do Nothing
			}
		}
		else // LastActor is Valid
		{
			if (ThisActor == nullptr)
			{
				// Case C
				LastActor->UnHighlightActor();
			}
			else // Both Actors are Valid
			{
				if (LastActor != ThisActor)
				{
					// Case D
					LastActor->UnHighlightActor();
					ThisActor->HighlightActor();
				}
				else
				{
					// Case E - Do Nothing
				}
			}
		}
	}
}
