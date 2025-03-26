// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleStats.h"
#include "BattleStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRECOVERY_API UBattleStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleStatsComponent();

	UFUNCTION(BlueprintCallable)
	void AddBattleStat(EBattleStats Stat, int Points);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBattleStat(EBattleStats Stat);

protected:
	UPROPERTY()
	TMap<TEnumAsByte<EBattleStats>, int32> Stats;

};
