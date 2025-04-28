// BeamXR Ltd 2025


#include "SBeamXRCameraTargetLineWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBeamXRCameraTargetLineWidget::Construct(const FArguments& InArgs)
{
    CameraOffset = InArgs._CameraOffset;
    TargetOffset = InArgs._TargetOffset;
}

void SBeamXRCameraTargetLineWidget::SetOffsets(float InCameraOffset, float InTargetOffset)
{
    CameraOffset = InCameraOffset;
    TargetOffset = InTargetOffset;
    Invalidate(EInvalidateWidgetReason::Paint);
}

int32 SBeamXRCameraTargetLineWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
    int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    const FVector2D Size = AllottedGeometry.GetLocalSize();
    const float ScaleFactor = 0.5f;  // Adjust for world units to screen

    // Points (invert Y offsets)
    FVector2D StartPoint(0.0f, Size.Y * 0.5f - CameraOffset * ScaleFactor);
    FVector2D EndPoint(Size.X, Size.Y * 0.5f - TargetOffset * ScaleFactor);

    // Draw main white line
    TArray<FVector2D> LinePoints = { StartPoint, EndPoint };
    FSlateDrawElement::MakeLines(
        OutDrawElements,
        LayerId,
        AllottedGeometry.ToPaintGeometry(),
        LinePoints,
        ESlateDrawEffect::None,
        FLinearColor::White,
        true,
        2.0f
    );

    // Draw dots at both ends
    const float DotRadius = 4.0f;
    FSlateDrawElement::MakeBox(
        OutDrawElements,
        LayerId + 1,
        AllottedGeometry.ToPaintGeometry(
            FVector2D(DotRadius * 2.0f, DotRadius * 2.0f),
            FSlateLayoutTransform(StartPoint - FVector2D(DotRadius, DotRadius))
        ),
        FCoreStyle::Get().GetBrush("WhiteBrush"),
        ESlateDrawEffect::None,
        FLinearColor::White
    );
    FSlateDrawElement::MakeBox(
        OutDrawElements,
        LayerId + 1,
        AllottedGeometry.ToPaintGeometry(
            FVector2D(DotRadius * 2.0f, DotRadius * 2.0f),
            FSlateLayoutTransform(EndPoint - FVector2D(DotRadius, DotRadius))
        ),
        FCoreStyle::Get().GetBrush("WhiteBrush"),
        ESlateDrawEffect::None,
        FLinearColor::White
    );

    // Chevron settings
    const float ChevronSpacing = 30.0f;
    const float ChevronSize = 6.0f;

    FVector2D LineVector = EndPoint - StartPoint;
    float LineLength = LineVector.Size();
    FVector2D LineDirection = LineVector.GetSafeNormal();
    FVector2D PerpDirection(-LineDirection.Y, LineDirection.X);  // Perpendicular vector

    for (float Distance = ChevronSpacing; Distance < LineLength - ChevronSpacing; Distance += ChevronSpacing)
    {
        FVector2D ChevronTip = StartPoint + LineDirection * Distance;

        // The arms point backward along the line (against LineDirection)
        FVector2D LeftArm = ChevronTip - LineDirection * ChevronSize + PerpDirection * ChevronSize * 0.5f;
        FVector2D RightArm = ChevronTip - LineDirection * ChevronSize - PerpDirection * ChevronSize * 0.5f;

        // Draw the chevron V
        FSlateDrawElement::MakeLines(
            OutDrawElements,
            LayerId + 2,
            AllottedGeometry.ToPaintGeometry(),
            TArray<FVector2D>({ LeftArm, ChevronTip, RightArm }),
            ESlateDrawEffect::None,
            FLinearColor::White,
            true,
            1.5f
        );
    }

    return LayerId + 3;  // Advance layer for all elements
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
