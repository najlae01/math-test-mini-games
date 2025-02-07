// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFacialExpression : uint8
{
    Neutral UMETA(DisplayName = "Neutral"),
    Happy UMETA(DisplayName = "Happy"),
    Sad UMETA(DisplayName = "Sad"),
    Angry UMETA(DisplayName = "Angry"),
    Excited UMETA(DisplayName = "Excited")
};