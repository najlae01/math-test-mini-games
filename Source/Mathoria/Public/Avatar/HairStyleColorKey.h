// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/HairColor.h"
#include "Avatar/HairStyle.h"
#include "HairStyleColorKey.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHairStyleColorKey
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hair Customization")
    EHairStyle HairStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hair Customization")
    EHairColor HairColor;

    // Comparison operators for use in TMap
    bool operator==(const FHairStyleColorKey& Other) const
    {
        return HairStyle == Other.HairStyle && HairColor == Other.HairColor;
    }
};

FORCEINLINE uint32 GetTypeHash(const FHairStyleColorKey& Key)
{
    return HashCombine(GetTypeHash(Key.HairStyle), GetTypeHash(Key.HairColor));
}

