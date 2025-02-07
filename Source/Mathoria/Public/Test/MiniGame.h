// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Test/MiniGameName.h"
#include "MiniGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MATHORIA_API UMiniGame : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame")
    EMiniGameName MiniGameName;

    // Player's score in the mini-game
    UPROPERTY(BlueprintReadWrite, Category = "MiniGame")
    int32 PlayerCorrectAnswers;

    // Starts the mini-game
    UFUNCTION(BlueprintCallable, Category = "MiniGame")
    virtual void StartMiniGame();

    // Determines if the player succeeded in the mini-game
    UFUNCTION(BlueprintCallable, Category = "MiniGame")
    virtual bool CheckSuccess(int32 RequiredCorrectAnswers);
};