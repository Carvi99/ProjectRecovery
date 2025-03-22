#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EInteractionResult : uint8
{
    Success,
    Blocked,
    Clashed
};