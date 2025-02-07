// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/SkinColor.h"
#include "SkinTextureRow.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FSkinTextureRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
    ESkinColor SkinColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
    UTexture2D* Texture;
};
