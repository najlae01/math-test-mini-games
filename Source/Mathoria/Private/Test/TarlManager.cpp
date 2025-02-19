// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TarlManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MathoriaGameInstance.h"


void UTarlManager::Initialize()
{
    // Get the PlayerState
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerStateRef = PlayerController->GetPlayerState<AMathoriaPlayerState>();
        if (PlayerStateRef)
        {
            UE_LOG(LogTemp, Warning, TEXT("PlayerStateRef successfully initialized."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to cast PlayerState to AMathoriaPlayerState."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController."));
    }
}

UTarlManager* UTarlManager::Get()
{
    if (GEngine)
    {
        UMathoriaGameInstance* GameInstance = Cast<UMathoriaGameInstance>(GEngine->GetWorldContexts()[0].OwningGameInstance);
        return GameInstance ? GameInstance->TarlManager : nullptr;
    }
    return nullptr;
}


// Function to check if the player can take the test
bool UTarlManager::CanStartTest()
{
    return (PlayerStateRef && PlayerStateRef->PlayerProfile);
}

void UTarlManager::StartTest()
{
    if (!PlayerStateRef)
    {
        UE_LOG(LogTemp, Error, TEXT("StartTest() failed: PlayerStateRef is null!"));
        return;
    }

    if (!PlayerStateRef->PlayerProfile)
    {
        UE_LOG(LogTemp, Error, TEXT("StartTest() failed: PlayerProfile is null!"));
        return;
    }

    if (!CanStartTest()) return;

    if (LevelTree.Num() > 0)
    {
        // Start the test level according to the player school grade
        EGradeLevel Grade = PlayerStateRef->PlayerProfile->SchoolGrade;
        // Find the test level that matches the player's grade
        for (UTestLevel* Level : LevelTree)
        {
            if (Level && Level->GradeLevel == Grade)
            {
                CurrentLevel = Level;
                break; // Stop searching once found
            }
        }
        if (CurrentLevel)
        {
            StartMiniGame();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No test level found for grade %d"), (int32)Grade);
        }
    }
    else
    {
        CurrentLevel = nullptr; // Default to nullptr if no levels are in the tree
    }
}


void UTarlManager::StartMiniGame()
{
    for (auto& MiniGamePair : CurrentLevel->MiniGames)
    {
        CurrentLevel->CurrentMiniGame = CurrentLevel->StartMiniGame(MiniGamePair.Key);
        return;
    }
}

void UTarlManager::MoveToLowerLevel()
{
    if (!CurrentLevel)
    {
        UE_LOG(LogTemp, Error, TEXT("CurrentLevel is null!"));
        return;
    }


    int32 CurrentLevelIndex = LevelTree.Find(CurrentLevel);
    if (CurrentLevelIndex == INDEX_NONE) return;

    if (CurrentLevel->GradeLevel <= EGradeLevel::One)
    {
        SetPlayerMathLevel();
    }

    // Move down to a lower level
    for (int32 i = CurrentLevelIndex - 1; i >= 0; --i)
    {
        if (LevelTree[i] && LevelTree[i]->GradeLevel < CurrentLevel->GradeLevel)
        {
            CurrentLevel = LevelTree[i];
            StartMiniGame(); // Start mini-game for the lower level
            return;
        }
    }

}


bool UTarlManager::EvaluateMiniGameSuccess(EMiniGameName MiniGameName)
{
    if (!CurrentLevel || !CurrentLevel->MiniGames.Contains(MiniGameName))
        return false;

    // Ensure CurrentMiniGame is valid
    if (!CurrentLevel->CurrentMiniGame)
    {
        UE_LOG(LogTemp, Error, TEXT("EvaluateMiniGameSuccess: CurrentMiniGame is null"));
        return false;
    }

    return CurrentLevel->CurrentMiniGame->CheckSuccess(CurrentLevel->MiniGames[MiniGameName].RequiredCorrectAnswers);
}


void UTarlManager::NotifyMiniGameCompleted()
{
    if (!PlayerStateRef || !PlayerStateRef->PlayerProfile || !CurrentLevel || !CurrentLevel->CurrentMiniGame) return;

    // Set mini-game completion status
    CurrentLevel->MiniGames[CurrentLevel->CurrentMiniGame->MiniGameName].bCompleted = true;

    bool bResult = EvaluateMiniGameSuccess(CurrentLevel->CurrentMiniGame->MiniGameName);
    //bool bResult = true; // remove it later
    //UE_LOG(LogTemp, Warning, TEXT("NotifyMiniGameCompleted: bResult = %s"), bResult ? TEXT("true") : TEXT("false"));

    UE_LOG(LogTemp, Warning, TEXT("Mini-game %s completed successfully!"), *UEnum::GetValueAsString(CurrentLevel->CurrentMiniGame->MiniGameName));

    if (bResult)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mini-game %s completed successfully!"), *UEnum::GetValueAsString(CurrentLevel->CurrentMiniGame->MiniGameName));

        if (CurrentLevel)
        {
            UE_LOG(LogTemp, Warning, TEXT("Starting next mini-game..."));
            UMiniGame* NextMiniGame = CurrentLevel->StartNextMiniGame();

            if (NextMiniGame)
            {
                SetCurrentMiniGame(NextMiniGame);
                UE_LOG(LogTemp, Warning, TEXT("Next mini-game set: %s"), *UEnum::GetValueAsString(NextMiniGame->MiniGameName));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("All mini-games completed or No mini-games available in the level."));
                SetPlayerMathLevel();
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("CurrentLevel is null! Cannot start the next mini-game."));
        }
    }
    else
    {
        // Now decide the next step
        MoveToLowerLevel();
    }

    PlayerStateRef->PlayerProfile->OnMiniGameCompleted(CurrentLevel->CurrentMiniGame->MiniGameName, bResult);
}


void UTarlManager::SetCurrentMiniGame(UMiniGame* NewMiniGame)
{
    if (NewMiniGame && CurrentLevel)
    {
        CurrentLevel->CurrentMiniGame = NewMiniGame;
        UE_LOG(LogTemp, Warning, TEXT("CurrentMiniGame updated to: %s"), *UEnum::GetValueAsString(CurrentLevel->CurrentMiniGame->MiniGameName));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to set CurrentMiniGame. Invalid input."));
    }
}

void UTarlManager::SetPlayerMathLevel()
{
    if (!PlayerStateRef || !PlayerStateRef->PlayerProfile || !CurrentLevel ) return; 

    // Player has completed their test and their math level matches the level test GradeLevel
    EGradeLevel FinalMathLevel = CurrentLevel->GradeLevel;
    UE_LOG(LogTemp, Warning, TEXT("Player completed the test! Math Level = %s."), *UEnum::GetValueAsString(FinalMathLevel));
    PlayerStateRef->PlayerProfile->MathLevel = FinalMathLevel;
    //UpdateMathLevelUI(FinalMathLevel);
}
