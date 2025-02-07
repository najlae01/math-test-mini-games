// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Test/TarlManager.h"
#include "MathoriaLoader.h"
#include "MathoriaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MATHORIA_API UMathoriaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// Called when the game instance is initialized
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TARL")
	UTarlManager* TarlManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TARL", meta = (AllowPrivateAccess = "true"))
	UDataTable* LevelDataTable;  // Stores test levels


	/** Load levels from a DataTable */
	void SetLevelLoader(IMathoriaLoader* NewLoader);
	TArray<UObject*> LoadLevelsFromDataTable(UDataTable* DataTable, TSubclassOf<UObject> ClassToCreate, UScriptStruct* RowStruct);

private:
	IMathoriaLoader* LevelLoader;
};