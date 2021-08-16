/*******************  Includes *************************/
#include "mainWin.h"

/******************* Public Functions ******************/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    int retval = 0;
    mainWin *mainWindow = NULL;

    mainWindow = new mainWin(hInstance);

    mainWindow->showWindow(nCmdShow);

    retval = mainWindow->runMainLoop();

    delete mainWindow;

    return retval;
}




