// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/Outfit.h"
#include "OutfitTextureRow.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FOutfitTextureRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
    EOutfit Outfit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
    UTexture2D* Texture;
};
