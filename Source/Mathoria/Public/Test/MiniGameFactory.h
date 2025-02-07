// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Test/MiniGame.h"
#include "Test/MiniGameName.h"
#include "MiniGameFactory.generated.h"

/**
 * 
 */
UCLASS()
class MATHORIA_API UMiniGameFactory : public UObject
{
	GENERATED_BODY()

public:
	static UMiniGameFactory* Get();

	static UMiniGame* CreateMiniGame(EMiniGameName MiniGameName);
};