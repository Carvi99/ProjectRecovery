// Fill out your copyright notice in the Description page of Project Settings.

#include "DirectionalInteractionComponent.h"

// Sets default values for this component's properties
UDirectionalInteractionComponent::UDirectionalInteractionComponent(){}

void UDirectionalInteractionComponent::Interact(EInteractionDirection InteractionDirection)
{

	if (IsInteracting) { return; }

	IsInteracting = true;

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this] {IsInteracting = false; }, 0.3f, false);

	SetDirection(InteractionDirection);

	if(!IsValid(Opponent)) { return; }
	if (FVector::Distance(Opponent->GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation()) < MaxDistance) { return; }

	// Interaction always successful if Forward Vectors align to an extent
	if (Opponent->GetOwner()->GetActorForwardVector().Dot(GetOwner()->GetActorForwardVector()) > 0.5)
	{
		OnInteractionDealt.Broadcast(Opponent, EInteractionResult::Success);
		Opponent->OnInteractionReceived.Broadcast(this, EInteractionResult::Success);
		return;
	}

	if (Opponent->Direction == EInteractionDirectionUtils::BlockingDirection(Direction))
	{
		if (Opponent->IsInteracting)
		{
			OnInteractionDealt.Broadcast(Opponent, EInteractionResult::Clashed);
			Opponent->OnInteractionReceived.Broadcast(this, EInteractionResult::Clashed);
		}
		else
		{
			OnInteractionDealt.Broadcast(Opponent, EInteractionResult::Blocked);
			Opponent->OnInteractionReceived.Broadcast(this, EInteractionResult::Blocked);
		}
	}
	else
	{
		OnInteractionDealt.Broadcast(Opponent, EInteractionResult::Success);
		Opponent->OnInteractionReceived.Broadcast(this, EInteractionResult::Success);
	}

}

void UDirectionalInteractionComponent::SetDirection(EInteractionDirection NewDirection)
{

	Direction = NewDirection;

	if (OnDirectionChanged.IsBound())
	{
		OnDirectionChanged.Broadcast(Direction);
	}

	if (IsValid(Opponent) && Opponent->OnOpponentDirectionChange.IsBound())
	{
		Opponent->OnOpponentDirectionChange.Broadcast(Direction);
	}

}

void UDirectionalInteractionComponent::SetOpponent(UDirectionalInteractionComponent* NewOpponent)
{
	Opponent = NewOpponent;
}
