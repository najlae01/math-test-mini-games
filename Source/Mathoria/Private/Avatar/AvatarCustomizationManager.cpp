// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar/AvatarCustomizationManager.h"
#include "Avatar/HairTextureRow.h"
#include "Avatar/SkinTextureRow.h"
#include "Avatar/OutfitTextureRow.h"
#include "Avatar/AccessoryTextureRow.h"
#include "Avatar/FacialExpressionTextureRow.h"


void UAvatarCustomizationManager::InitializeData()
{
    if (HairTextureTable)
    {
        TArray<FHairTextureRow*> Rows;
        HairTextureTable->GetAllRows(TEXT("Hair Texture Initialization"), Rows);
        for (FHairTextureRow* Row : Rows)
        {
            if (Row && Row->Texture)
            {
                HairTextures.Add(Row->Key, Row->Texture);
            }
        }
    }

    // Skin Textures
    if (SkinTextureTable)
    {
        TArray<FSkinTextureRow*> Rows;
        SkinTextureTable->GetAllRows(TEXT("Skin Texture Initialization"), Rows);
        for (FSkinTextureRow* Row : Rows)
        {
            if (Row && Row->Texture)
            {
                SkinTextures.Add(Row->SkinColor, Row->Texture);
            }
        }
    }

    // Outfit Textures
    if (OutfitTextureTable)
    {
        TArray<FOutfitTextureRow*> Rows;
        OutfitTextureTable->GetAllRows(TEXT("Outfit Texture Initialization"), Rows);
        for (FOutfitTextureRow* Row : Rows)
        {
            if (Row && Row->Texture)
            {
                OutfitTextures.Add(Row->Outfit, Row->Texture);
            }
        }
    }

    // Accessory Textures
    if (AccessoryTextureTable)
    {
        TArray<FAccessoryTextureRow*> Rows;
        AccessoryTextureTable->GetAllRows(TEXT("Accessory Texture Initialization"), Rows);
        for (FAccessoryTextureRow* Row : Rows)
        {
            if (Row && Row->Texture)
            {
                AccessoryTextures.Add(Row->Accessory, Row->Texture);
            }
        }
    }

    // Facial Expression Textures
    if (ExpressionTextureTable)
    {
        TArray<FFacialExpressionTextureRow*> Rows;
        ExpressionTextureTable->GetAllRows(TEXT("Expression Texture Initialization"), Rows);
        for (FFacialExpressionTextureRow* Row : Rows)
        {
            if (Row && Row->Texture)
            {
                ExpressionTextures.Add(Row->Expression, Row->Texture);
            }
        }
    }
}


UTexture2D* UAvatarCustomizationManager::GetHairTexture(EHairStyle Style, EHairColor Color)
{
    FHairStyleColorKey Key{ Style, Color };
    if (UTexture2D** Texture = HairTextures.Find(Key))
    {
        return *Texture;
    }
    return nullptr; // Return nullptr if the texture is not found
}

UTexture2D* UAvatarCustomizationManager::GetTextureForSkin(ESkinColor SkinColor)
{
    if (UTexture2D** Texture = SkinTextures.Find(SkinColor))
    {
        return *Texture;
    }
    return nullptr; // Return nullptr if no matching skin texture is found
}

UTexture2D* UAvatarCustomizationManager::GetTextureForOutfit(EOutfit Outfit)
{
    if (UTexture2D** Texture = OutfitTextures.Find(Outfit))
    {
        return *Texture;
    }
    return nullptr; // Return nullptr if no matching outfit texture is found
}

UTexture2D* UAvatarCustomizationManager::GetTextureForAccessory(EAccessory Accessory)
{
    if (UTexture2D** Texture = AccessoryTextures.Find(Accessory))
    {
        return *Texture;
    }
    return nullptr; // Return nullptr if no matching accessory texture is found
}

UTexture2D* UAvatarCustomizationManager::GetTextureForExpression(EFacialExpression Expression)
{
    if (UTexture2D** Texture = ExpressionTextures.Find(Expression))
    {
        return *Texture;
    }
    return nullptr; // Return nullptr if no matching expression texture is found
}
