/**
* \file:       toolbox.cpp
* \Description Implementation of toolbox class that manages the toolbox
* \Date        8/23/2021
* \author      Jason Neitzert
*/

/************************** Includes ***********************/
#include "toolbox.h"

#pragma comment (lib, "dwrite.lib")
/*********************** Class Definitions *****************/


Toolbox::Toolbox(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2dFactory)
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
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&p_write_factory));
}

void Toolbox::draw(ID2D1HwndRenderTarget* pRenderTarget)
{
    IDWriteTextLayout *p_text_layout = nullptr;
    IDWriteTextFormat* pTextFormat = nullptr;

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

    D2D1_POINT_2F text_start = { 50,5 };

    pRenderTarget->DrawRoundedRectangle(&toolboxRoundedRect, pWhiteBrush, 5, pBoardTextStrokeStyle);
    p_write_factory->CreateTextFormat(
        L"Times New Roman",                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        30.0f,
        L"en-us",
        &pTextFormat
    );
    p_write_factory->CreateTextLayout(L"Toolbox", 7, pTextFormat, 200 - 20, 800 - 20, &p_text_layout);
    pRenderTarget->DrawTextLayout(text_start, p_text_layout, pWhiteBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

}

Toolbox::~Toolbox()
{
    p_write_factory->Release();
}

