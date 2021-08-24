/**
* \file:       pcb.cpp
* \Description Definition of pcb class that manages the circuit board
* \Date        8/23/2021
* \author      Jason Neitzert
*/

#pragma once

/************************** Includes ***********************/
#include "toolbox.h"

/*********************** Class Definitions *****************/
class PCB
{
public:
    PCB(HWND hWnd, UINT width, UINT heigth);
    ~PCB();

    void draw();

private:
    ID2D1Factory*          pD2dFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    Toolbox*               ptoolbox;
};
