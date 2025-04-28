// BeamXR Ltd 2025

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BEAMXRDIRECTORKITOPENXRUI_API SBeamXRCameraTargetLineWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SBeamXRCameraTargetLineWidget)
        : _CameraOffset(0.0f)
        , _TargetOffset(0.0f)
        {
        }
        SLATE_ARGUMENT(float, CameraOffset)
        SLATE_ARGUMENT(float, TargetOffset)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    void SetOffsets(float InCameraOffset, float InTargetOffset);

protected:
    virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
        int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
    float CameraOffset;
    float TargetOffset;
};