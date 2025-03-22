// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, int, NewStatValue, int, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRECOVERY_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	virtual void BeginPlay() override;

	int GetStatValue(ECharacterStats Stat);
	int GetCurrentHealthValue() { return Strength; }

	UFUNCTION(BlueprintCallable)
	void IncreaseStatValue(ECharacterStats Stat, int Points);

	UFUNCTION(BlueprintCallable)
	void FillUpCurrentHealth();

	UFUNCTION(BlueprintCallable)
	void DecreaseCurrentHealth(int Points);

	// -- Delegates --

	UPROPERTY(BlueprintAssignable)
	FOnStatChanged OnCurrentHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Health = 1;

	UPROPERTY(BlueprintReadOnly)
	int CurrentHealth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Strength = 1;
		
};
