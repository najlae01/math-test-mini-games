// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GradeLevel.h"
#include "Test/MiniGame.h"
#include "Test/MiniGameName.h"
#include "Test/MiniGameSuccessCriteria.h"
#include "TestLevelRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct MATHORIA_API FTestLevelRow : public FTableRowBase
{
    GENERATED_BODY()

public:

    // The grade level associated with this test
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    EGradeLevel GradeLevel;

   // Mini Games and their Success thresholds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    TMap<EMiniGameName, FMiniGameSuccessCriteria> MiniGames;
};