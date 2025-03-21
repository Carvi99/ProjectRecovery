// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Direction.h"
#include "InteractionResult.h"
#include "DirectionalInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionDelegate, UDirectionalInteractionComponent*, Interactor, EInteractionResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectionChangedDelegate, EDirection, Direction);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRECOVERY_API UDirectionalInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDirectionalInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void SetDirection(EDirection NewDirection);

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


protected:

	UPROPERTY()
	TObjectPtr<UDirectionalInteractionComponent> Opponent = nullptr;

	UPROPERTY()
	TEnumAsByte<EDirection> Direction;

	UPROPERTY(EditAnywhere)
	float MaxDistance = 300.0;

	bool IsInteracting = false;


		
};
