// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EHairStyle : uint8
{
    Default UMETA(DisplayName = "Default"),
    Short UMETA(DisplayName = "Short"),
    Long UMETA(DisplayName = "Long"),
    Curly UMETA(DisplayName = "Curly")
};
