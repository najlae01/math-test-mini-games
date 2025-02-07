// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GradeLevel.h"
#include "Test/MiniGame.h"
#include "Test/MiniGameName.h"
#include "Test/MiniGameSuccessCriteria.h"
#include "Test/MiniGameFactory.h"
#include "TestLevel.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MATHORIA_API UTestLevel : public UObject
{
    GENERATED_BODY()

public:
    UTestLevel();

    // The grade level associated with this test
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    EGradeLevel GradeLevel;

    // Mini Games and their Success thresholds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    TMap<EMiniGameName, FMiniGameSuccessCriteria> MiniGames;

    // Ordered list of mini-games
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    TArray<EMiniGameName> MiniGameOrder;

    // Index of the current mini-game
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    int32 CurrentMiniGameIndex = -1;

    // Current Mini-game
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Level")
    UMiniGame* CurrentMiniGame;

    // Factory-based function to create a mini-game
    UFUNCTION(BlueprintCallable, Category = "Test Level")
    UMiniGame* StartMiniGame(EMiniGameName MiniGameName);

    UFUNCTION(BlueprintCallable, Category = "TARL")
    UMiniGame* StartNextMiniGame();

    UFUNCTION(BlueprintCallable, Category = "Test Level")
    static UTestLevel* CreateTestLevel(int32 InTestLevelID, const EGradeLevel InGradeLevel, TMap<EMiniGameName, FMiniGameSuccessCriteria> InMiniGames);
};
