// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/HairStyle.h"
#include "Avatar/HairColor.h"
#include "Avatar/SkinColor.h"
#include "Avatar/HairStyleColorKey.h"
#include "Avatar/Outfit.h"
#include "Avatar/Accessory.h"
#include "Avatar/FacialExpression.h"
#include "AvatarCustomizationManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MATHORIA_API UAvatarCustomizationManager : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<FHairStyleColorKey, UTexture2D*> HairTextures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<ESkinColor, UTexture2D*> SkinTextures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<EOutfit, UTexture2D*> OutfitTextures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<EAccessory, UTexture2D*> AccessoryTextures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    TMap<EFacialExpression, UTexture2D*> ExpressionTextures;

    // DataTables references
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    UDataTable* HairTextureTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    UDataTable* SkinTextureTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    UDataTable* OutfitTextureTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    UDataTable* AccessoryTextureTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avatar Customization")
    UDataTable* ExpressionTextureTable;

    void InitializeData();

    // Methods to retrieve textures/colors
    UTexture2D* GetHairTexture(EHairStyle Style, EHairColor Color);
    UTexture2D* GetTextureForSkin(ESkinColor SkinColor);
    UTexture2D* GetTextureForOutfit(EOutfit Outfit);
    UTexture2D* GetTextureForAccessory(EAccessory Accessory);
    UTexture2D* GetTextureForExpression(EFacialExpression Expression);
};