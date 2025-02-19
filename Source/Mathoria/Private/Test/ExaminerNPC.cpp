// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/ExaminerNPC.h"
#include "Test/TARLManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MathoriaGameInstance.h"


void AExaminerNPC::StartTestOnInteraction()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        AMathoriaPlayerState* PlayerStateRef = PlayerController->GetPlayerState<AMathoriaPlayerState>();
        /*PlayerStateRef->LoadPlayerData();*/
        if (PlayerStateRef)
        {
            UE_LOG(LogTemp, Warning, TEXT("Starting TARL Test!"));

            UMathoriaGameInstance* GameInstance = Cast<UMathoriaGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
            if (GameInstance && GameInstance->TarlManager)
            {
                GameInstance->TarlManager->Initialize();
                GameInstance->TarlManager->StartTest();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("TARLManager is not initialized!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player is not authenticated. Cannot start the test."));
        }
    }
}