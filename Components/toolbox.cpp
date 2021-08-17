#pragma once

/************************** Includes ***********************/
#include "toolbox.h"

/*********************** Class Definitions *****************/


toolbox::toolbox(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2dFactory)
{
    D2D1_STROKE_STYLE_PROPERTIES boardTextStrokeProperties = { D2D1_CAP_STYLE_ROUND,
                                                               D2D1_CAP_STYLE_ROUND,
                                                               D2D1_CAP_STYLE_ROUND,
                                                               D2D1_LINE_JOIN_ROUND,
                                                               5,
                                                               D2D1_DASH_STYLE_SOLID,
                                                               0 };

    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AntiqueWhite),
        &pWhiteBrush);

    pD2dFactory->CreateStrokeStyle(&boardTextStrokeProperties,
                                   nullptr,
                                   0,
                                   &pBoardTextStrokeStyle);
}

void toolbox::draw(ID2D1HwndRenderTarget* pRenderTarget)
{
    D2D1_RECT_F toolboxRect =
    {
        5,
        5,
        200,
        800
    };

    D2D1_ROUNDED_RECT toolboxRoundedRect =
    {
        toolboxRect,
        1,
        1
    };

    pRenderTarget->DrawRoundedRectangle(&toolboxRoundedRect, pWhiteBrush, 5, pBoardTextStrokeStyle);
}

