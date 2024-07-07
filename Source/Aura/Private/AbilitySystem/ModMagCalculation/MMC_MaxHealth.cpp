// Copyright Lone Moose Games


#include "AbilitySystem/ModMagCalculation/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	/* Configure the Attribute */
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot = false;

	/* Add the Attribute to an array to operate on */
	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	/* Gather Tags from Source and Target */
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	/* Store Tags in an FAggregatorEvaluateParameters struct to use in GetCapturedAttributeMagnitude() */
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	/* Always Initialize variables */
	float VigorMagnitude{0.f};
	/* Capture the Magnitude of Vigor */
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluateParameters, VigorMagnitude);
	/* Clamp magnitude at 0 */
	VigorMagnitude = FMath::Max(VigorMagnitude, 0.f);

	/**
	 * Get Player Level
	 * You can get the Source Object of the Gameplay Effect from the Spec
	 * As long as the Gameplay Effect has a sourec object you can cast it to the ICombatInterface;
	 */
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + (2.5f * VigorMagnitude) + (10.f * PlayerLevel);
}
