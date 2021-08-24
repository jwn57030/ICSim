/**
* \file:       toolbox.h
* \Description Definition of toolbox class that manages the toolbox
* \Date        8/23/2021
* \author      Jason Neitzert
*/

#pragma once

#include <d2d1.h>
#include <dwrite.h>

class toolbox
{
public:
    toolbox(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2dFactory);
    ~toolbox();

    void draw(ID2D1HwndRenderTarget* pRenderTarget);

private:
    ID2D1SolidColorBrush* pWhiteBrush           = nullptr;
    ID2D1StrokeStyle*     pBoardTextStrokeStyle = nullptr;
    IDWriteFactory*       p_write_factory       = nullptr;
};