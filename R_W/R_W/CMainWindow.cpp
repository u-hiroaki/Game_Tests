#include "CMainWindow.h"
#include "CDirectXDevice.h"
#include <stdio.h>
#include <d3dx9.h>

#include "C2DSprite.h"
#include <stdlib.h>
#include <math.h>
bool frame = false;

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
    m_sequence.Init();
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
        else{
            this->AppLoop();Sleep(1);
        }
	}
	return S_OK;
}

VOID CMainWindow::AppLoop()
{
        m_sequence.Update(frame);
    CDirectXDevice::GetDxDevice().Begin();
    C2DBuffer::drawAll(CDirectXDevice::GetDxDevice().GetDevice());
    C2DSprite::drawAll(CDirectXDevice::GetDxDevice().GetDevice());
    C2DSprite::clearDrawList();
        C2DBuffer::clearDrawList();
    CDirectXDevice::GetDxDevice().End();
    frame = false;
    g_button.push[0]=false;
        g_button.push[1]=false;
            g_button.push[2]=false;
                g_button.push[3]=false;
}

HRESULT CMainWindow::Release()
{
    C2DSprite::end_last();
    C2DBuffer::end_last();
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