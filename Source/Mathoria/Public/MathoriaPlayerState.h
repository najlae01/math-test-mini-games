// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FirebaseFeatures.h"
#include "Database/DatabaseReference.h"
#include "MathoriaPlayerProfile.h"
#include "Avatar/HairStyle.h"
#include "Avatar/HairColor.h"
#include "Avatar/SkinColor.h"
#include "Avatar/Outfit.h"
#include "Avatar/Accessory.h"
#include "Avatar/FacialExpression.h"
#include "MathoriaPlayerState.generated.h"

/**
 *
 */
class UDatabaseReference;

UCLASS(Blueprintable, BlueprintType)
class MATHORIA_API AMathoriaPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

    AMathoriaPlayerState();

    virtual void BeginPlay() override;

    // Firebase PlayerId (UID)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info", Replicated)
    FString FirebasePlayerId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Profile")
    UMathoriaPlayerProfile* PlayerProfile;

    // Network Connection
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Connection")
    bool IsConnected;

    UFUNCTION(BlueprintCallable, Category = "Firebase")
    bool OnSplashScreen();

    // Save and Load Methods
    UFUNCTION(BlueprintCallable, Category = "Firebase")
    bool SavePlayerData();

    UFUNCTION(BlueprintCallable, Category = "Firebase")
    bool LoadPlayerData();

    UFUNCTION(BlueprintCallable, Category = "Network Disconnection")
    void SetupDisconnection();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    TSubclassOf<UAvatarCustomizationManager> CustomizationManagerClass;

    // Get Texture for Customization
    UFUNCTION(BlueprintCallable, Category = "Customization")
    UTexture2D* GetHairTexture(EHairStyle HairStyle, EHairColor HairColor);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    UTexture2D* GetSkinTexture(ESkinColor SkinColor);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    UTexture2D* GetOutfitTexture(EOutfit Outfit);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    UTexture2D* GetAccessoryTexture(EAccessory Accessory);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    UTexture2D* GetFacialExpressionTexture(EFacialExpression Expression);

private:

    // Helper function to initialize Firebase reference
    void InitializeDatabaseReference();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};