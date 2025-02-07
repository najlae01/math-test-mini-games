// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameSuccessCriteria.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MATHORIA_API FMiniGameSuccessCriteria
{
    GENERATED_BODY()

public:
    // The number of correct answers required for success
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame Success Criteria")
    int32 RequiredCorrectAnswers;

    // Should differ depending on the Test Level
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame Success Criteria")
    int32 NumberOfQuestions;

    // Whether the player has completed this mini-game successfully
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame Success Criteria")
    bool bCompleted = false;
};