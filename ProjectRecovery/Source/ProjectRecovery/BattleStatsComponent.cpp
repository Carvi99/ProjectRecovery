// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleStatsComponent.h"

// Sets default values for this component's properties
UBattleStatsComponent::UBattleStatsComponent()
{
}

void UBattleStatsComponent::AddBattleStat(EBattleStats Stat, int Points)
{
	if (Stats.Contains(Stat))
	{
		Stats[Stat] += Points;
	}
	else
	{
		Stats.Add(Stat, Points);
	}
}

int UBattleStatsComponent::GetBattleStat(EBattleStats Stat)
{
	if (Stats.Contains(Stat))
	{
		return Stats[Stat];
	}
	
	return -1;
}
