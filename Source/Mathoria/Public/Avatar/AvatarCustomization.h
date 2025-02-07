// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Avatar/HairStyleColorKey.h"
#include "Avatar/SkinColor.h"
#include "Avatar/Outfit.h"
#include "Avatar/Accessory.h"
#include "Avatar/FacialExpression.h"
#include "AvatarCustomization.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FAvatarCustomization
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<FHairStyleColorKey, UTexture2D*> Hair;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    ESkinColor SkinColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    EOutfit Outfit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TArray<EAccessory> Accessories;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    EFacialExpression FacialExpression;

    FAvatarCustomization()
        : SkinColor(ESkinColor::Fair),
        Outfit(EOutfit::Casual),
        FacialExpression(EFacialExpression::Neutral)
    {
    }
};
