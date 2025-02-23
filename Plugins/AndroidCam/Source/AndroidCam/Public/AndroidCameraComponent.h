#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Texture2D.h"
#include "Rendering/Texture2DResource.h"
#include "RHI.h"
#include "RHIResources.h"
#include "RenderResource.h"
#include "AndroidCameraComponent.generated.h"

USTRUCT()
struct FUpdateTextureRegionsData
{
    GENERATED_BODY()

    //UTexture2D* Texture;
    FTexture2DResource* Texture2DResource;
    int32 MipIndex;
    uint32 NumRegions;
    FUpdateTextureRegion2D* Regions;
    uint32 SrcPitch;
    uint32 SrcBpp;
    uint8* SrcData;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANDROIDCAM_API UAndroidCameraComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    UTexture2D* androidCameraTexture;
    bool bActive = false;
    TArray<FColor> rawData;
    FUpdateTextureRegion2D* echoUpdateTextureRegion;
    int32 width = 320;
    int32 height = 240;

    int YUVtoRGB(int y, int u, int v);
    const float frameRate = 30.f;
    float timer = 0;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void updateTexture(void* data);

    UFUNCTION(BlueprintCallable, Category = Android)
    void updateCamera(float delta);

    UFUNCTION(BlueprintCallable, Category = Android)
    UTexture2D* getAndroidCameraTexture();

    UFUNCTION(BlueprintCallable, Category = Android)
    void shutDownCamera();
};