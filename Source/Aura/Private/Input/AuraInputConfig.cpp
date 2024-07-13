// Copyright Lone Moose Games


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find AbilityInputAction for InputTag: [%s] on  InputConfig [%s]."),
		       *InputTag.ToString(), *GetNameSafe(this))
	}
	return nullptr;
}
