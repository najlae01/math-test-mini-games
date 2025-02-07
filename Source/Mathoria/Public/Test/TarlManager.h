// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Test/TestLevelRow.h"
#include "Test/TestLevel.h"
#include "MathoriaPlayerState.h"
#include "TarlManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MATHORIA_API UTarlManager : public UObject
{
    GENERATED_BODY()

public:
    void Initialize();

    static UTarlManager* Get();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TARL")
    TArray<UTestLevel*> LevelTree;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TARL")
    UTestLevel* CurrentLevel;

    UPROPERTY()
    AMathoriaPlayerState* PlayerStateRef;


    /** Starts the test */
    UFUNCTION(BlueprintCallable, Category = "TARL")
    void StartTest();

    /** Start the mini-game for the current level */
    UFUNCTION(BlueprintCallable, Category = "TARL")
    void StartMiniGame();

    /** Checks if the player can start the test */
    UFUNCTION(BlueprintCallable, Category = "TARL")
    bool CanStartTest();

    /** Move to a lower test level when the player fails the current mini-game of this text level */
    UFUNCTION(BlueprintCallable, Category = "TARL")
    void MoveToLowerLevel();

    /** Checks if the player failed or passed the mini-game before deciding on the next min-game to load */
    UFUNCTION(BlueprintCallable, Category = "TARL")
    bool EvaluateMiniGameSuccess(EMiniGameName MiniGameName);

    UFUNCTION(BlueprintCallable, Category = "TARL")
    void NotifyMiniGameCompleted();

    UFUNCTION(Category = "TARL")
    void SetCurrentMiniGame(UMiniGame* CurrentGame);

    UFUNCTION(Category = "TARL")
    void SetPlayerMathLevel();
};
