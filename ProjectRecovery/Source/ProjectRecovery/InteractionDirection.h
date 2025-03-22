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

namespace EInteractionDirectionUtils
{
    static EInteractionDirection BlockingDirection(EInteractionDirection Direction)
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
}