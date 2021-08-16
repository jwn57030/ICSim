#pragma once

/************************** Includes ***********************/
#include <d2d1.h>

#if 0
#include <d3d11.h>
#endif
class pcb
{
public:
    pcb(HWND hWnd, UINT width, UINT heigth);
    ~pcb();

    void draw();
#if 0
private:

    // global declarations
    IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
    ID3D11Device* dev;                     // the pointer to our Direct3D device interface
    ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
    ID3D11RenderTargetView* backbufferRenderTarget;
#endif
    ID2D1Factory* pD2dFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pLightSlateGrayBrush;
    ID2D1SolidColorBrush* pCornflowerBlueBrush;
    ID2D1StrokeStyle* pBoardTextStrokeStyle;

};


