/**
* \file:       pcb.cpp
* \Description Implementation of pcb class that manages the circuit board
* \Date        8/23/2021
* \author      Jason Neitzert
*/

/********************* Includes *******************************/
#include "pcb.h"

/***************** Libs To Link ********************************/
#pragma comment(lib, "d2d1.lib")

/***************** Public Functions **************************/

/**
* \Description Constructor for PCB Class
* \param       hWnd   - Window the PCB should be put in.
* \param       width  - how wide the window is where we are putting the PCB
* \param       heigth - how hight the window is where we are putting the PCB.
* \return      void
* \author      Jason Neitzert
* \date        8/23/2021
*/
PCB::PCB(HWND hWnd, UINT width, UINT heigth):pRenderTarget(NULL), pD2dFactory(NULL)
{
    D2D1_SIZE_U                  size                      = D2D1::SizeU(width, heigth);


    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2dFactory);
    
    pD2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                        D2D1::HwndRenderTargetProperties(hWnd, size),
                                        &pRenderTarget);

    ptoolbox = new Toolbox(pRenderTarget, pD2dFactory);
}

/**
* \Description Constructor for PCB Class
* \param       void
* \return      void
* \author      Jason Neitzert
* \date        8/23/2021
*/
PCB::~PCB()
{
    delete ptoolbox;
    pRenderTarget->Release();
    pD2dFactory->Release();
}

/**
* \Description Draw thre PCB and everything on it
* \param       void
* \return      void
* \author      Jason Neitzert
* \date        8/23/2021
*/
void PCB::draw()
{
    pRenderTarget->BeginDraw();

    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkGreen));

    ptoolbox->draw(pRenderTarget);
        
    pRenderTarget->EndDraw();
}


