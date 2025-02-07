// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EHairColor : uint8
{
    Black UMETA(DisplayName = "Black"),
    Brown UMETA(DisplayName = "Brown"),
    Blonde UMETA(DisplayName = "Blonde"),
    Red UMETA(DisplayName = "Red")
};