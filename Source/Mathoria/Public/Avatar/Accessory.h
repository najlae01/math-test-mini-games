// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAccessory : uint8
{
    None UMETA(DisplayName = "None"),
    Glasses UMETA(DisplayName = "Glasses"),
    Hat UMETA(DisplayName = "Hat"),
    Earrings UMETA(DisplayName = "Earrings")
};
