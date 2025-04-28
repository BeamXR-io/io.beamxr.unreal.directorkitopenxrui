// BeamXR Ltd 2025


#include "BeamXRCameraTargetLineWidget.h"
#include "SBeamXRCameraTargetLineWidget.h"

TSharedRef<SWidget> UBeamXRCameraTargetLineWidget::RebuildWidget()
{
    MySlateWidget = SNew(SBeamXRCameraTargetLineWidget)
        .CameraOffset(CameraOffset)
        .TargetOffset(TargetOffset);

    return MySlateWidget.ToSharedRef();
}

void UBeamXRCameraTargetLineWidget::SetOffsets(float InCameraOffset, float InTargetOffset)
{
    CameraOffset = InCameraOffset;
    TargetOffset = InTargetOffset;

    SynchronizeProperties();  // Force update
}

void UBeamXRCameraTargetLineWidget::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    if (MySlateWidget.IsValid())
    {
        MySlateWidget->SetOffsets(CameraOffset, TargetOffset);
    }
}

void UBeamXRCameraTargetLineWidget::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    // Important to prevent Slate widget leak warnings
    MySlateWidget.Reset();
}