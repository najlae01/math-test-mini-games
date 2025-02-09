#include "UI/PaintWidget.h"
#include "Engine/Canvas.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"


// Called when the widget is constructed
void UPaintWidget::NativeConstruct()
{
    Super::NativeConstruct();

    bIsPainting = false;
    LastPointerPosition = FVector2D::ZeroVector;

    // Clear the Render Target to transparent black
    if (RenderTarget)
    {
        UKismetRenderingLibrary::ClearRenderTarget2D(this, RenderTarget, FLinearColor::White);
    }

    // Create a Dynamic Material Instance for the PaintSurface
    if (PaintSurface && PaintMaterial)
    {
        DynamicMaterialInstance = UMaterialInstanceDynamic::Create(PaintMaterial, this);
        PaintSurface->SetBrushFromMaterial(DynamicMaterialInstance);

        // Bind the Render Target to the Material
        if (DynamicMaterialInstance && RenderTarget)
        {
            DynamicMaterialInstance->SetTextureParameterValue("PaintTexture", RenderTarget);
        }
    }
}

// Handle pointer down events (mouse or touch)
FReply UPaintWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || InMouseEvent.IsTouchEvent())
    {
        bIsPainting = true;
        LastPointerPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
    }
    return FReply::Handled();
}

// Handle pointer move events (mouse or touch)
FReply UPaintWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsPainting)
    {
        // Get the current pointer position in local widget space
        FVector2D CurrentPointerPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

        // Get the widget size and Render Target size
        FVector2D WidgetSize = InGeometry.GetLocalSize();
        FVector2D RenderTargetSize = FVector2D(RenderTarget->SizeX, RenderTarget->SizeY);

        // Map the mouse position to Render Target space
        FVector2D MappedStartPos = MapToRenderTargetSpace(LastPointerPosition, WidgetSize, RenderTargetSize);
        FVector2D MappedEndPos = MapToRenderTargetSpace(CurrentPointerPosition, WidgetSize, RenderTargetSize);

        // Draw on the Render Target using the mapped positions
        DrawOnRenderTarget(MappedStartPos, MappedEndPos);

        // Update the last pointer position
        LastPointerPosition = CurrentPointerPosition;
    }
    return FReply::Handled();
}

// Handle pointer up events (mouse or touch)
FReply UPaintWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || InMouseEvent.IsTouchEvent())
    {
        bIsPainting = false;
    }
    return FReply::Handled();
}

// Draw on the Render Target
void UPaintWidget::DrawOnRenderTarget(const FVector2D& StartPos, const FVector2D& EndPos)
{
    if (!RenderTarget || !DynamicMaterialInstance) return;

    // Create a canvas for drawing
    UCanvas* Canvas = nullptr;
    FVector2D Size;
    FDrawToRenderTargetContext Context;
    UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, RenderTarget, Canvas, Size, Context);

    if (Canvas)
    {
        // Draw a line from StartPos to EndPos
        FCanvasLineItem LineItem(StartPos, EndPos);
        LineItem.LineThickness = 10.0f; // Set the brush thickness
        LineItem.SetColor(FLinearColor::Red); // Set the brush color
        Canvas->DrawItem(LineItem);
    }

    // Finish drawing
    UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, Context);
}


FVector2D UPaintWidget::MapToRenderTargetSpace(const FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2D& RenderTargetSize)
{
    return FVector2D(
        (WidgetPosition.X / WidgetSize.X) * RenderTargetSize.X,
        (WidgetPosition.Y / WidgetSize.Y) * RenderTargetSize.Y
    );
}