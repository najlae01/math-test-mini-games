// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/Accessory.h"
#include "AccessoryTextureRow.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FAccessoryTextureRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessory")
    EAccessory Accessory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessory")
    UTexture2D* Texture;
};
