#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EBattleStats : uint8
{
    AttackAttempts,
    AttackAttemptsByEnemy,
    Hits,
    HitsByEnemy,
    Parried,
    Blocked,
    BlockedByOpponent,
    DealtDamage,
    SufferedDamage,
    Time
};