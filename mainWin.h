
#pragma once

/***************************** Includes *************************/
#include <windows.h>
#include "pcb.h"

class mainWin
{
    public:
        mainWin(HINSTANCE hInstance);
        ~mainWin();

        void showWindow(int nCmdShow);
        WPARAM runMainLoop();
     
    private:
        pcb *pMainPcb = nullptr;
        HWND hWnd     = nullptr;

        static LRESULT CALLBACK mainWinMsgCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void draw();
};

