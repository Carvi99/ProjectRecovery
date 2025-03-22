#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EDirection : uint8
{
    None,
    North,
    East,
    South,
    West
};

namespace EDirectionUtils
{
    static EDirection BlockingDirection(EDirection Direction)
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