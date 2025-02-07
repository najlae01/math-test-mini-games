// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Answer.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MATHORIA_API FAnswer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnswerText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCorrect;
};
