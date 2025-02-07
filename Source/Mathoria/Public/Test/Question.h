// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GradeLevel.h"
#include "MathArea.h"
#include "Answer.h"
#include "Difficulty.h"
#include "Question.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MATHORIA_API FQuestion
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGradeLevel GradeLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMathArea MathArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MathTopic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnswer Answer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDifficulty Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HintText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAnswer> PossibleAnswers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EstimatedCompletionTime;
};
