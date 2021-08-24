/**
* \file:       MainWindow.cpp
* \Description Main Window Implementation
* \Date        8/23/2021
* \author      Jason Neitzert
*/

/*************************** Includes ********************************/
#include "MainWin.h"

/********************** Constants and Defines *****************/
constexpr auto MAINWINCLASSNAME = L"mainWinClass";

#define DRAWING_AREA_HEIGHT 1010
#define DRAWING_AREA_WIDTH  2000

/********************* Global Variables ***********************/
static ATOM mainWinClass = 0;

/********************* Public Functions ***********************/

MainWin::~MainWin()
{
    DestroyWindow(hWnd);
    delete pMainPcb;
} 

BOOL MainWin::showWindow(HINSTANCE hInstance, int nCmdShow)
{
    BOOL       retval   = FALSE;
    RECT       wr       = { 0, 0, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT };
    WNDCLASSEX wndClass = { 0 };

    /* Register window class first time through */
    if (!mainWinClass)
    {
        /* Register Window Class Type */
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = MainWin::mainWinMsgCallback;
        wndClass.hInstance = hInstance;
        wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
        wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wndClass.lpszClassName = MAINWINCLASSNAME;

        // register the window class
        mainWinClass = RegisterClassEx(&wndClass);
    }

    if (!mainWinClass)
    {

        hWnd = CreateWindowEx(NULL,
                              MAINWINCLASSNAME,    /* name of the window class */
                              L"ICSim",            /* title of the window */
                              WS_OVERLAPPEDWINDOW, /* window style */
                              300,                 /* x - position of the window */
                              0,                   /* y - position of the window */
                              wr.right - wr.left,  /* width of the window */
                              wr.bottom - wr.top,  /* height of the window */
                              NULL,                /* we have no parent window, NULL */
                              NULL,                /* we aren't using menus, NULL */
                              hInstance,           /* application handle */
                              NULL);               /* used with multiple windows, NULL */

        /* Save this class as user data for the window callback function */
        SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(this));

        /* create the pcb in the window */
        pMainPcb = new PCB(hWnd, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT);

    }



    ShowWindow(hWnd, nCmdShow);
}

void MainWin::draw()
{
    pMainPcb->draw();
}

/* Callback Function for Main Window Message Actions */
LRESULT CALLBACK MainWin::mainWinMsgCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT  retval   = 1;
    MainWin* pmainWin = NULL;
 
    switch (message)
    {
        case WM_PAINT:
        {
            pmainWin = reinterpret_cast<MainWin*>(GetWindowLong(hWnd, GWLP_USERDATA));
            pmainWin->draw();
            ValidateRect(hWnd, NULL);
            break;
        }
       case WM_DESTROY:
       {
          PostQuitMessage(0);
          break;
       }
       default:
       {
           retval = DefWindowProc(hWnd, message, wParam, lParam);
           break;
       }
    }
    return retval;
}

WPARAM MainWin::runMainLoop()
{
    MSG msg = { 0 };

    while (WaitMessage() && GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


