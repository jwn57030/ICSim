/**
* \file:       MainWin.h
* \Description Definition of Main Window Class
* \Date        8/23/2021
* \author      Jason Neitzert
*/

#pragma once

/***************************** Includes *************************/
#include <windows.h>
#include "components/PCB.h"

/*********************** Class Definitions **********************/
class MainWin
{
   public:
      ~MainWin();

      void showWindow(HINSTANCE hInstance, int nCmdShow);
      WPARAM runMainLoop();
     
   private:
      PCB *pMainPcb = nullptr;
      HWND hWnd     = nullptr;

      static LRESULT CALLBACK mainWinMsgCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
      void draw();
};

