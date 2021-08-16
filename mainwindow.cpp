
/*************************** Includes ********************************/
#include "mainWin.h"

/********************** Constants and Defines *****************/
constexpr auto MAINWINCLASSNAME = L"mainWinClass";

#define DRAWING_AREA_HEIGHT 1010
#define DRAWING_AREA_WIDTH 2000

/********************* Public Functions ***********************/
mainWin::mainWin(HINSTANCE hInstance)
{
    RECT wr = { 0, 0, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT };
    WNDCLASSEX wndClass = { 0 };
    
    /* Register Window Clas Type */
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = mainWin::mainWinMsgCallback;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
    wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wndClass.lpszClassName = MAINWINCLASSNAME;

    // register the window class
    RegisterClassEx(&wndClass);

    hWnd = CreateWindowEx(NULL,
                          MAINWINCLASSNAME,    // name of the window class
                          L"ICSim",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          0,    // y-position of the window
                          wr.right - wr.left,    // width of the window
                          wr.bottom - wr.top,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    /* Save this class as user data for the window callback function */
    SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(this));

    /* create the pcb in the window*/
    pMainPcb = new pcb(hWnd, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT);
}

mainWin::~mainWin()
{
    delete pMainPcb;
} 

void mainWin::showWindow(int nCmdShow)
{
    ShowWindow(hWnd, nCmdShow);
}

void mainWin::draw()
{
    pMainPcb->draw();
}

/* Callback Function for Main Window Message Actions */
LRESULT CALLBACK mainWin::mainWinMsgCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT  retval   = 1;
    mainWin* pmainWin = NULL;
 
    switch (message)
    {
        case WM_PAINT:
        {
            pmainWin = reinterpret_cast<mainWin*>(GetWindowLong(hWnd, GWLP_USERDATA));
            pmainWin->draw();
            ValidateRect(hWnd, NULL);
            break;
        }
       case WM_DESTROY:
       {
          // close the application entirely
          PostQuitMessage(0);
          break;
       }
       default:
       {
           // Handle any messages not handled abouve
           retval = DefWindowProc(hWnd, message, wParam, lParam);
           break;
       }
    }
    return retval;
}

WPARAM mainWin::runMainLoop()
{
    MSG msg = { 0 };

    while (WaitMessage() && GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


