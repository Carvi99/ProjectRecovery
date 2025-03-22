#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EInteractionDirection : uint8
{
    None,
    North,
    East,
    South,
    West
};