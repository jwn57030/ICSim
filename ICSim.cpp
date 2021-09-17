/**
* \file:       ICSim.cpp 
* \Description Main Starting Point
* \Date        8/23/2021
* \author      Jason Neitzert
*/

/*******************  Includes *************************/
#include <windows.h>
#include "components/pcb.h"

/********************** Constants and Defines *****************/
constexpr auto MAINWINCLASSNAME = L"mainWinClass";

#define DRAWING_AREA_HEIGHT 1010
#define DRAWING_AREA_WIDTH  2000

/*************** Private Functions *********************/

/**
* \Description Main Window Message Loop
* \return      WPARAM - return value when message loop exits.
* \author      Jason Neitzert
* \date        8/24/2021
*/
static int runMainLoop()
{
    BOOL waitRet = TRUE;
    BOOL getRet  = TRUE;
    int  retVal = 0;
    MSG  msg     = {};

    /* GetMessage returns a bool but a -1 also indicates an error condition as well */
    while ((waitRet = WaitMessage()) && (getRet = GetMessage(&msg, NULL, 0, 0)) && (getRet != -1))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if ((FALSE == waitRet) || (-1 == getRet))
    {
        /* Display Error Popup using GetLastError */

        retVal = -1;
    }

    return retVal;
}

/**
* \Description Callback Function for Main Window Message Actions
* \param       hWnd    - window callback is for
* \param       message - message id
* \param       wParam  - wparam for callback
* \param       lParam  - lparam fpr callback
* \return      LRESULT - result of callback.
* \author      Jason Neitzert
* \date        8/24/2021
*/
static LRESULT CALLBACK mainWinMsgCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT  retval   = 1;
    PCB*     pMainPCB = nullptr;
    
    switch (message)
    {
        case WM_PAINT:
        {
            pMainPCB = reinterpret_cast<PCB*>(GetWindowLong(hWnd, GWLP_USERDATA));
            pMainPCB->draw();
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

/**
* \Description Register Window Classes Used In Program
* \param       hINstance - program instance
* \return      BOOL      - were classes registered correctly.
* \author      Jason Neitzert
* \date        8/24/2021
*/
static BOOL registerWindowClasses(HINSTANCE hInstance)
{
    BOOL       retval   = FALSE;
    WNDCLASSEX wndClass = { 0 };

    /* Register Window Class Type */
    wndClass.cbSize        = sizeof(WNDCLASSEX);
    wndClass.style         = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = mainWinMsgCallback;
    wndClass.hInstance     = hInstance;
    wndClass.hCursor       = LoadCursor(NULL, IDC_HAND);
    wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wndClass.lpszClassName = MAINWINCLASSNAME;

    if (0 != RegisterClassEx(&wndClass))
    {
        retval = TRUE;
    }

    return retval;
}

/**
* \Description Creates Main Window
* \param       hINstance - Window instance
* \return      HWND      - handle to created window
* \author      Jason Neitzert
* \date        8/24/2021
*/
static HWND createMainWindow(HINSTANCE hInstance)
{
    RECT wr = { 0, 0, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT };

    return CreateWindowEx(NULL,
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
}

/******************* Public Functions ******************/
/**
* \Description Main Function for Win32
* \param       hINstance     - program instance
* \param       hPrevInstance - previous program instance
* \param       lpCmpLine     - command line options 
* \return      int           - return value of program
* \author      Jason Neitzert
* \date        8/23/2021
*/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    BOOL retVal    = FALSE;
    PCB* pMainPcb  = nullptr;
    HWND hWnd      = nullptr;

    if ((FALSE == registerWindowClasses(hInstance)) &&
        (nullptr != (hWnd = createMainWindow(hInstance))))
    {
        /* Display  Error Popup */

    }
    /* create the pcb in the window */
    else if (nullptr == (pMainPcb = new PCB(hWnd, DRAWING_AREA_WIDTH, DRAWING_AREA_HEIGHT)))
    {
        /* Display Error Popup */
    }
    else
    {
        /* Save the PCB instance as user data for the window callback function */
        if (0 == SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(pMainPcb)))
        {
            /* Display Error Popup */

        }
        else
        {
            /* Show window and wait inside mesage loop until window is closed */
            ShowWindow(hWnd, nCmdShow);

            if (FALSE == (retVal = runMainLoop()))
            {
                /* Display error popup */

            }
        }

        delete pMainPcb;
    }
    
    if (FALSE == retVal)
    {
        

    }

    MessageBox(hWnd, L"TESTING THE ERROR", L"ERROR TEST", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);

    return retVal;
}




