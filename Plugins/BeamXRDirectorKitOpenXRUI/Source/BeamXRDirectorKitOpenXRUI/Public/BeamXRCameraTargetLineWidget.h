// BeamXR Ltd 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeamXRCameraTargetLineWidget.generated.h"

class SBeamXRCameraTargetLineWidget;

/**
 * 
 */
UCLASS()
class BEAMXRDIRECTORKITOPENXRUI_API UBeamXRCameraTargetLineWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Offsets")
    float CameraOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Offsets")
    float TargetOffset = 0.0f;

    UFUNCTION(BlueprintCallable, Category = "Offsets")
    void SetOffsets(float InCameraOffset, float InTargetOffset);

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void ReleaseSlateResources(bool bReleaseChildren) override;
    virtual void SynchronizeProperties() override;

private:
    TSharedPtr<SBeamXRCameraTargetLineWidget> MySlateWidget;
	
};
