#pragma once

#include <d2d1.h>

class toolbox
{
public:
    toolbox(ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2dFactory);

    void draw(ID2D1HwndRenderTarget* pRenderTarget);

private:
    ID2D1SolidColorBrush* pWhiteBrush           = nullptr;
    ID2D1StrokeStyle*     pBoardTextStrokeStyle = nullptr;
};