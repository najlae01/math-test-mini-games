// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESkinColor : uint8
{
    Default UMETA(DisplayName = "Default"),
    Fair UMETA(DisplayName = "Fair"),
    Medium UMETA(DisplayName = "Medium"),
    Dark UMETA(DisplayName = "Dark")
};