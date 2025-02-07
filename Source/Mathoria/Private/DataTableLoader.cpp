// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableLoader.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"

#include "Test/TestLevelRow.h"
#include "Test/TestLevel.h"
#include "Avatar/SkinTextureRow.h"


TArray<UObject*> UDataTableLoader::LoadRowsToArray(UDataTable* DataTable, TSubclassOf<UObject> ClassToCreate, UScriptStruct* RowStruct)
{
    if(!DataTable || !ClassToCreate || !RowStruct)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid parameters passed to LoadLevelsFromDataTable."));
        return TArray<UObject*>();
    }

    TArray<UObject*> ObjectsArray;

    // Iterate through all rows in the DataTable
    for (const FName& RowName : DataTable->GetRowNames())
    {
        FString ContextString;

        // Create an instance of ClassToCreate (use ClassToCreate instead of UObject)
        UObject* NewObjectInstance = NewObject<UObject>(GetTransientPackage(), ClassToCreate);

        // Ensure the class is valid and we have a valid instance to work with
        if (NewObjectInstance)
        {
            // Cast the new object instance to the specific class type (e.g., UTestLevel)
            if (UTestLevel* TestLevel = Cast<UTestLevel>(NewObjectInstance))
            {
                // Get the row data (cast it to the specific row struct)
                const FTestLevelRow* Row = DataTable->FindRow<FTestLevelRow>(RowName, ContextString);
                if (!Row)
                {
                    continue;
                }
                // Initialize the instance with the row data
                TestLevel->GradeLevel = Row->GradeLevel;
                TestLevel->MiniGames = Row->MiniGames;
                TestLevel->CurrentMiniGameIndex = -1;

                // Maintain the original order
                for (const TPair<EMiniGameName, FMiniGameSuccessCriteria>& Entry : TestLevel->MiniGames)
                {
                    UE_LOG(LogTemp, Error, TEXT("MiniGame %s LOADED"), *UEnum::GetValueAsString(Entry.Key));
                    TestLevel->MiniGameOrder.Add(Entry.Key);
                }

                // Log the specific TestLevel data (for example)
                UE_LOG(LogTemp, Error, TEXT("Loaded Test Level for Grade Level %d"),
                     TestLevel->GradeLevel);

                // Add the newly created level to the array
                ObjectsArray.Add(TestLevel);
            }
        }
    }

    return ObjectsArray;
}