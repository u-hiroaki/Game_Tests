#include "CMainWindow.h"
#include "CDirectXDevice.h"
#include <stdio.h>
#include <d3dx9.h>

#include "C2DSprite.h"
#include <stdlib.h>
#include <math.h>

C2DSprite sprite[100];
float Xvec = 1.0f;
float Yvec = 1.0f;
float vect[100];
float deg[100]; 


LRESULT CMainWindow::AppProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_KEYDOWN:HookKey(wParam,lParam);break;
	}
    return DefWindowProc( this->m_hwnd, msg, wParam, lParam );
}

HRESULT CMainWindow::MsgLoop()
{
	
    tComPtr<IDirect3DTexture9> tex;
	srand(201);
    D3DXCreateTextureFromFile(CDirectXDevice::GetDxDevice().GetDevice(),L"Data\\no_picture.jpg",tex.GetPPtr());
	for(int i=0;i<100;++i)
	{
		sprite[i].setScreenSize(this->GetWindowcWidth(),this->GetWindowcHeight());
	    sprite[i].setPivot(64.0f,64.0f);
		sprite[i].setTexture(tex,false);
		deg[i] = rand() % 360;
		vect[i] = rand() % 2 + 1.0f;
		sprite[i].setPos(this->GetWindowcWidth()/2-64.0f,this->GetWindowcHeight()/2-64.0f);

	}
	while(1)
	{
		if(PeekMessage(&m_msg,NULL,0,0,PM_REMOVE))
		{
			if(m_msg.message==WM_QUIT)
				break;
			else
			{
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
		}
        else{ this->AppLoop();Sleep(1);}
	}
	return S_OK;
}

VOID CMainWindow::AppLoop()
{
	for(int i=0;i<100;++i)
    {
		float px,py;
	    sprite[i].getPos(&px,&py);
		if(px+vect[i]*cos(deg[i]) > this->GetWindowcWidth()-128.0f)
		 Xvec = -1.0f;
		else if(px-vect[i]*cos(deg[i]) < 0.000f)
			Xvec = 1.0f;
		if(py+vect[i]*sin(deg[i]) > this->GetWindowcHeight()-128.0f)
			Yvec = -1.0f;
		else if(py-vect[i]*sin(deg[i]) <0.000f)
			Yvec = 1.0f;

    sprite[i].setPos(px+cos(deg[i])*1.0f*Xvec,py+3.0f*sin(deg[i])*Yvec);
     sprite[i].setAlpha(1.0f);
     sprite[i].setRotate(deg[i]);
     sprite[i].draw();
	}
    CDirectXDevice::GetDxDevice().Begin();
    C2DSprite::drawAll(CDirectXDevice::GetDxDevice().GetDevice());
    C2DSprite::clearDrawList();
    CDirectXDevice::GetDxDevice().End();
}

HRESULT CMainWindow::Release()
{
    C2DSprite::end_last();
	return S_OK;
}

void CMainWindow::HookKey(WPARAM wparam,LPARAM lparam)
{
	switch(wparam)
    {
    case VK_ESCAPE:PostMessage(this->GetWindowHandle(),WM_DESTROY,0,0);
				break;
            default :break;
		}
    std::map<WPARAM,KeyHookPtr>::iterator it =m_KeyHookTable.find(wparam);
    if(it != m_KeyHookTable.end())
        (*((*it).second))(this->GetWindowHandle(),lparam);
}

void CMainWindow::ChangeScr2Window()
{
    ShowWindow(m_hwnd,SW_HIDE);
    ChangeDisplaySettings(NULL,0);
	SetWindowLongPtr(m_hwnd,GWL_STYLE,WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX);
	SetWindowPos(m_hwnd,HWND_NOTOPMOST,
    m_rect.left,
    m_rect.top,
    m_wWidth,
    m_wHeight,
    0);


	SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    ShowWindow(m_hwnd, SW_SHOW);
    m_WINDOWMODE = TRUE;
}

void CMainWindow::ChangeScr2Full()
{
    GetWindowRect(m_hwnd,&m_rect);
    ShowWindow(m_hwnd,SW_HIDE);
    SetWindowLongPtr(m_hwnd,GWL_STYLE,WS_POPUP | WS_VISIBLE | WS_BORDER);
    SetWindowPos(m_hwnd,HWND_TOPMOST,0,0,m_cWidth,m_cHeight,0);

    DEVMODE	dev;
    dev.dmSize			= sizeof(DEVMODE);
    dev.dmFields		= DM_PELSWIDTH | DM_PELSHEIGHT;
    dev.dmPelsHeight	= m_cHeight;
    dev.dmPelsWidth		= m_cWidth;
    ChangeDisplaySettings(&dev,CDS_FULLSCREEN);

	SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    ShowWindow(m_hwnd, SW_SHOW);
    m_WINDOWMODE = FALSE;
}