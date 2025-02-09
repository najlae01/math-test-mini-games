// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MathoriaUserWidget.h"
#include "PaintWidget.generated.h"

/**
 * 
 */

class UImage;
class UMaterialInstanceDynamic;
class UTextureRenderTarget2D;


UCLASS(BlueprintType)
class MATHORIA_API UPaintWidget : public UMathoriaUserWidget
{
	GENERATED_BODY()

protected:
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

    // Pointer event handlers
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    // Properties
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* PaintSurface; // The Image widget used as the drawing surface

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Paint System")
    UMaterialInterface* PaintMaterial; // The material used for drawing

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Paint System")
    UTextureRenderTarget2D* RenderTarget; // The Render Target used for drawing

    UPROPERTY(BlueprintReadOnly)
    UMaterialInstanceDynamic* DynamicMaterialInstance; // Dynamic Material Instance for the PaintSurface

private:
    // Helper function to draw on the Render Target
    void DrawOnRenderTarget(const FVector2D& StartPos, const FVector2D& EndPos);

    FVector2D MapToRenderTargetSpace(const FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2D& RenderTargetSize);

    bool bIsPainting; // Whether the user is currently painting
    FVector2D LastPointerPosition; // The last recorded pointer position
};