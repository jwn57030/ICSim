/********************* Includes *******************************/
#include "pcb.h"
#if 0
#include <dwrite.h>
#pragma comment (lib, "dwrite.lib")
#endif
/***************** Libs To Link ********************************/
#pragma comment(lib, "d2d1.lib")


/***************** Public Functions **************************/
pcb::pcb(HWND hWnd, UINT width, UINT heigth):pRenderTarget(NULL), pD2dFactory(NULL)
{
    D2D1_SIZE_U                  size                      = D2D1::SizeU(width, heigth);
    D2D1_STROKE_STYLE_PROPERTIES boardTextStrokeProperties = { D2D1_CAP_STYLE_ROUND,
                                                               D2D1_CAP_STYLE_ROUND,
                                                               D2D1_CAP_STYLE_ROUND,
                                                               D2D1_LINE_JOIN_ROUND,
                                                               5,
                                                               D2D1_DASH_STYLE_SOLID,
                                                               0 };

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2dFactory);
    
    pD2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                        D2D1::HwndRenderTargetProperties(hWnd, size),
                                        &pRenderTarget);
    
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                                         &pLightSlateGrayBrush);

    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                                         &pCornflowerBlueBrush);

     pD2dFactory->CreateStrokeStyle(&boardTextStrokeProperties,
                                    nullptr,
                                    0,
                                    &pBoardTextStrokeStyle);
}

void pcb::draw()
{
    D2D1_RECT_F toolboxRect =
    { 
        5,
        5,
        200,
        400
    };
    
    D2D1_ROUNDED_RECT toolboxRoundedRect =
    {
        toolboxRect,
        1,
        1
    };


    pRenderTarget->BeginDraw();

    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkGreen));
        
    pRenderTarget->DrawRoundedRectangle(&toolboxRoundedRect, pLightSlateGrayBrush, 5, pBoardTextStrokeStyle);

    pRenderTarget->EndDraw();
#if 0
    IDWriteFactory* pDWriteFactory = nullptr;
    IDWriteTextFormat* pTextFormat = nullptr;
    
    const wchar_t* wszText = nullptr;
    UINT32 cTextLength = 0;

    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&pDWriteFactory)
    );


    pDWriteFactory->CreateTextFormat(
        L"Gabriola",                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        72.0f,
        L"en-us",
        &pTextFormat
    );

    wszText = L"Hello World using  DirectWrite!";
    cTextLength = (UINT32)wcslen(wszText);

    pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    
#endif
}


pcb::~pcb()
{
    pLightSlateGrayBrush->Release();
    pCornflowerBlueBrush->Release();
    pBoardTextStrokeStyle->Release();
    pRenderTarget->Release();
    pD2dFactory->Release();
}
