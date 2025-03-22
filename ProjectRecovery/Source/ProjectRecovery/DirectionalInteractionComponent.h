// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionDirection.h"
#include "InteractionResult.h"
#include "DirectionalInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionDelegate, UDirectionalInteractionComponent*, Interactor, EInteractionResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectionChangedDelegate, EInteractionDirection, Direction);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRECOVERY_API UDirectionalInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDirectionalInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void Interact(EInteractionDirection InteractionDirection, float Cooldown);

	UFUNCTION(BlueprintCallable)
	void SetDirection(EInteractionDirection NewDirection);

	UFUNCTION(BlueprintCallable)
	void SetOpponent(UDirectionalInteractionComponent* NewOpponent);

	UPROPERTY(BlueprintAssignable)
	FOnInteractionDelegate OnInteractionDealt;

	UPROPERTY(BlueprintAssignable)
	FOnInteractionDelegate OnInteractionReceived;

	UPROPERTY(BlueprintAssignable)
	FOnDirectionChangedDelegate OnDirectionChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDirectionChangedDelegate OnOpponentDirectionChange;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static EInteractionDirection GetBlockingDirection(EInteractionDirection Direction);


protected:

	UPROPERTY()
	TObjectPtr<UDirectionalInteractionComponent> Opponent = nullptr;

	UPROPERTY()
	TEnumAsByte<EInteractionDirection> Direction;

	UPROPERTY(EditAnywhere)
	float MaxDistance = 100.0;

	bool IsInteracting = false;


		
};
