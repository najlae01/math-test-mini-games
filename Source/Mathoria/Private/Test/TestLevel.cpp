// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestLevel.h"

UTestLevel::UTestLevel()
{
    // Initialize default values
    GradeLevel = EGradeLevel::One;
    CurrentMiniGame = nullptr; 
    CurrentMiniGameIndex = -1;

    for (const TPair<EMiniGameName, FMiniGameSuccessCriteria>& Entry : MiniGames)
    {
        MiniGameOrder.Add(Entry.Key);
    }

}

UMiniGame* UTestLevel::StartMiniGame(EMiniGameName MiniGameName)
{
    if (!MiniGames.Contains(MiniGameName))
    {
        UE_LOG(LogTemp, Warning, TEXT("MiniGame %s not found in MiniGames map!"), *UEnum::GetValueAsString(MiniGameName));
        return nullptr;
    }

    UMiniGameFactory* Factory = UMiniGameFactory::Get();
    if (!Factory)
    {
        UE_LOG(LogTemp, Error, TEXT("MiniGameFactory is null!"));
        return nullptr;
    }

    CurrentMiniGame = Factory->CreateMiniGame(MiniGameName);
    if (!CurrentMiniGame)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create MiniGame: %s"), *UEnum::GetValueAsString(MiniGameName));
        return nullptr;
    }

    // Update index only if it exists in MiniGameOrder
    int32 NewIndex = MiniGameOrder.IndexOfByKey(MiniGameName);
    if (NewIndex != INDEX_NONE)
    {
        CurrentMiniGameIndex = NewIndex;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MiniGame %s is not in MiniGameOrder!"), *UEnum::GetValueAsString(MiniGameName));
    }

    UE_LOG(LogTemp, Warning, TEXT("MiniGame %s Created Successfully"), *UEnum::GetValueAsString(MiniGameName));
    return CurrentMiniGame;
}

UMiniGame* UTestLevel::StartNextMiniGame()
{
    if (MiniGameOrder.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No mini-games available in the level."));
        return nullptr;
    }

    // Ensure valid index before incrementing
    if (CurrentMiniGameIndex == INDEX_NONE)
    {
        CurrentMiniGameIndex = 0; // Start at first mini-game
    }
    else if (CurrentMiniGameIndex < MiniGameOrder.Num() - 1)
    {
        CurrentMiniGameIndex++;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("All mini-games completed. Handle level completion."));
        return nullptr;
    }

    EMiniGameName NextMiniGame = MiniGameOrder[CurrentMiniGameIndex];

    UE_LOG(LogTemp, Warning, TEXT("Starting MiniGame: %s"), *UEnum::GetValueAsString(NextMiniGame));

    UMiniGame* NewMiniGame = StartMiniGame(NextMiniGame);

    if (NewMiniGame)
    {
        CurrentMiniGame = NewMiniGame;  // Ensure we update it correctly
        UE_LOG(LogTemp, Warning, TEXT("CurrentMiniGame updated to: %s"), *UEnum::GetValueAsString(CurrentMiniGame->MiniGameName));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to start MiniGame: %s"), *UEnum::GetValueAsString(NextMiniGame));
    }

    return CurrentMiniGame;
}



UTestLevel* UTestLevel::CreateTestLevel(int32 InTestLevelID,
    const EGradeLevel InGradeLevel,
    TMap<EMiniGameName, FMiniGameSuccessCriteria> InMiniGames)
{
    UTestLevel* NewTestLevel = NewObject<UTestLevel>(GetTransientPackage(), UTestLevel::StaticClass());
    //NewTestLevel->TestLevelID = InTestLevelID;
    NewTestLevel->GradeLevel = InGradeLevel;
    NewTestLevel->MiniGames = InMiniGames;
    NewTestLevel->CurrentMiniGameIndex = -1;

    // Maintain the original order
    for (const TPair<EMiniGameName, FMiniGameSuccessCriteria>& Entry : InMiniGames)
    {
        NewTestLevel->MiniGameOrder.Add(Entry.Key);
    }

    return NewTestLevel;
}