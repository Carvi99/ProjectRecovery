// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
}

void UCharacterStatsComponent::BeginPlay()
{
	CurrentHealth = Health;
}

int UCharacterStatsComponent::GetStatValue(ECharacterStats Stat)
{
	switch (Stat)
	{
		case ECharacterStats::Health:
			return Health;

		case ECharacterStats::Strength:
			return Strength;

		default:
			return 0;
	}
}

void UCharacterStatsComponent::IncreaseStatValue(ECharacterStats Stat, int Points)
{
	switch (Stat)
	{
		case ECharacterStats::Health:
			Health += Points;
			break;

		case ECharacterStats::Strength:
			Strength += Points;
			break;
	}
}

void UCharacterStatsComponent::FillUpCurrentHealth()
{
	int PreviousHealthPoints = CurrentHealth;
	CurrentHealth = Health;

	if (OnCurrentHealthChanged.IsBound())
	{
		OnCurrentHealthChanged.Broadcast(CurrentHealth, CurrentHealth - PreviousHealthPoints);
	}
}

void UCharacterStatsComponent::DecreaseCurrentHealth(int Points)
{

	if (Points < 1) { return; }
	int PreviousHealthPoints = CurrentHealth;
	CurrentHealth = FMath::Min(FMath::Max(0, CurrentHealth - Points), Health);

	if (PreviousHealthPoints != CurrentHealth && OnCurrentHealthChanged.IsBound())
	{
		OnCurrentHealthChanged.Broadcast(CurrentHealth, -Points);
	}
}