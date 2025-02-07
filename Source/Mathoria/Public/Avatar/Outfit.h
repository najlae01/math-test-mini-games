// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EOutfit : uint8
{
    Default UMETA(DisplayName = "Default"),
    Casual UMETA(DisplayName = "Casual"),
    Formal UMETA(DisplayName = "Formal"),
    Sporty UMETA(DisplayName = "Sporty")
};