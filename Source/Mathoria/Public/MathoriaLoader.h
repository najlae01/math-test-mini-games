// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MathoriaLoader.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMathoriaLoader : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATHORIA_API IMathoriaLoader
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<UObject*> LoadRowsToArray(UDataTable* DataTable, TSubclassOf<UObject> ClassToCreate, UScriptStruct* RowStruct) = 0;
};
