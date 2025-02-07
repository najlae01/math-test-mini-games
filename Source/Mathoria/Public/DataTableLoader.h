// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MathoriaLoader.h"
#include "DataTableLoader.generated.h"

/**
 * 
 */
UCLASS()
class MATHORIA_API UDataTableLoader : public UObject, public IMathoriaLoader
{
	GENERATED_BODY()

public:
	TArray<UObject*> LoadRowsToArray(UDataTable* DataTable, TSubclassOf<UObject> ClassToCreate, UScriptStruct* RowStruct) override;

};
