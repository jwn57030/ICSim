#pragma once

/************************** Includes ***********************/
#include <d2d1.h>
#include "toolbox.h"

/*********************** Class Definitions *****************/
class pcb
{
public:
    pcb(HWND hWnd, UINT width, UINT heigth);
    ~pcb();

    void draw();

private:
    ID2D1Factory*          pD2dFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    toolbox*               ptoolbox;
};


