// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/HairStyleColorKey.h"
#include "HairTextureRow.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FHairTextureRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hair")
    FHairStyleColorKey Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hair")
    UTexture2D* Texture;
};
