// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameName.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMiniGameName : uint8
{
    ReadingNumbersOneDigit UMETA(DisplayName = "Reading Numbers of One Digit"),
    ReadingNumbersTwoDigits UMETA(DisplayName = "Reading Numbers of Two Digits"),
    Addition UMETA(DisplayName = "Addition"),
    Subtraction UMETA(DisplayName = "Subtraction"),
    Multiplication UMETA(DisplayName = "Multiplication"),
    Division UMETA(DisplayName = "Division"),
    Problem UMETA(DisplayName = "Problem")
};