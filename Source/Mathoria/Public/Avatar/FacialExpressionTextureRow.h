// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/FacialExpression.h"
#include "FacialExpressionTextureRow.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FFacialExpressionTextureRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Facial Expression")
    EFacialExpression Expression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Facial Expression")
    UTexture2D* Texture;
};