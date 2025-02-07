// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGradeLevel : uint8
{
    One UMETA(DisplayName = "Grade 1"),
    Two UMETA(DisplayName = "Grade 2"),
    Three UMETA(DisplayName = "Grade 3"),
    Four UMETA(DisplayName = "Grade 4"),
    Five UMETA(DisplayName = "Grade 5"),
    Six UMETA(DisplayName = "Grade 6")
};
