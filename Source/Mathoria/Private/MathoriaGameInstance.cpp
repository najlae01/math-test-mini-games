// Fill out your copyright notice in the Description page of Project Settings.


#include "MathoriaGameInstance.h"
#include "DataTableLoader.h"


void UMathoriaGameInstance::Init()
{
    Super::Init();

    if (!TarlManager) // Ensure it is only created once
    {
        TarlManager = NewObject<UTarlManager>(this);
    }

    if (LevelDataTable)
    {
        UE_LOG(LogTemp, Log, TEXT("LevelDataTable is valid"));

        UDataTableLoader* Loader = NewObject<UDataTableLoader>();
        SetLevelLoader(Loader);
        // Load levels as an array of UObject*
        TArray<UObject*> LoadedLevels = LoadLevelsFromDataTable(LevelDataTable, UTestLevel::StaticClass(), FTestLevelRow::StaticStruct());

        // Cast each element of the array to UTestLevel* and add to LevelTree
        for (UObject* Obj : LoadedLevels)
        {
            if (UTestLevel* TestLevel = Cast<UTestLevel>(Obj))
            {
                TarlManager->LevelTree.Add(TestLevel);
            }
        }
    }
}

void UMathoriaGameInstance::SetLevelLoader(IMathoriaLoader* NewLoader) 
{ 
    LevelLoader = NewLoader;
}

TArray<UObject*> UMathoriaGameInstance::LoadLevelsFromDataTable(UDataTable* DataTable, TSubclassOf<UObject> ClassToCreate, UScriptStruct* RowStruct)
{
    if (LevelLoader)
    {
        return LevelLoader->LoadRowsToArray(DataTable, ClassToCreate, RowStruct);
    }
    else return TArray<UObject*>();
}

