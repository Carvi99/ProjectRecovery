// Fill out your copyright notice in the Description page of Project Settings.

#include "DirectionalInteractionComponent.h"

// Sets default values for this component's properties
UDirectionalInteractionComponent::UDirectionalInteractionComponent(){}

void UDirectionalInteractionComponent::Interact(EInteractionDirection InteractionDirection, float Cooldown)
{
	if (InteractionDirection == EInteractionDirection::None) { return; }
	if (IsInteracting) { return; }

	IsInteracting = true;

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this] {IsInteracting = false; }, Cooldown, false);

	SetDirection(InteractionDirection);

	if(!IsValid(Opponent)) { return; }

	if (FVector::Distance(Opponent->GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation()) > MaxDistance) { return; }

	// Interaction always successful if Owning Actor is behind Opponent Actor
	bool IsBehindOpponent = Opponent->GetOwner()->GetActorForwardVector().Dot(GetOwner()->GetActorForwardVector()) > 0.5;
	IsBehindOpponent = IsBehindOpponent && (Opponent->GetOwner()->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal().Dot(Opponent->GetOwner()->GetActorForwardVector()) > 0.5f;
	if (IsBehindOpponent)
	{
		OnInteractionDealt.Broadcast(Opponent, EInteractionResult::Success);
		Opponent->OnInteractionReceived.Broadcast(this, EInteractionResult::Success);
		return;
	}

	if (Opponent->Direction == GetBlockingDirection(Direction))
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

	if (Direction == NewDirection) { return; }

	if (OnDirectionChanged.IsBound())
	{
		OnDirectionChanged.Broadcast(Direction);
	}

	if (IsValid(Opponent) && Opponent->OnOpponentDirectionChange.IsBound())
	{
		Opponent->OnOpponentDirectionChange.Broadcast(Direction);
	}

	Direction = NewDirection;

}

void UDirectionalInteractionComponent::SetOpponent(UDirectionalInteractionComponent* NewOpponent)
{
	Opponent = NewOpponent;
}

EInteractionDirection UDirectionalInteractionComponent::GetBlockingDirection(EInteractionDirection Direction)
{
	switch (Direction)
	{
	case North:
		return North;

	case East:
		return West;

	case South:
		return South;

	case West:
		return East;

	default:
		return None;
	}
}
