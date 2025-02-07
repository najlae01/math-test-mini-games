// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC.h"
#include "ExaminerNPC.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MATHORIA_API AExaminerNPC : public ANPC
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	void StartTestOnInteraction();
};
