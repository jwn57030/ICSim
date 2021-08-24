/**
* \file:       ICSim.cpp 
* \Description Main Starting Point
* \Date        8/23/2021
* \author      Jason Neitzert
*/

/*******************  Includes *************************/
#include "mainWin.h"

/******************* Public Functions ******************/
/**
* \Description Main function for win32
* \param       hINstance     - Window instance
* \param       hPrevInstance - instance this window was spawned from
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
    int     retval = 0;
    MainWin mainWindow(hInstance);

    mainWindow.showWindow(nCmdShow);
    
    /* Wait inside loop until window is closed */
    retval = mainWindow.runMainLoop();

    return retval;
}




