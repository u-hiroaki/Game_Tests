#include "WindowManager.h"
#pragma comment(lib, "winmm.lib")
const LPTSTR WINDOWNAME = TEXT("NewGame");
const LPTSTR APPLICATIONNAME = TEXT("MainWindow");
LPCWSTR PROP_WINPROC = L"MyProc";

/*******************************************************************
		name	:	WinManager::INIT
		brief	:	初期化処理
		return	:	HRESULT
		param	hInstance	:	インスタンスハンドル
		param	nShowCmd	:	インスタンスハンドル
*******************************************************************/

HRESULT WinManager::Init(HINSTANCE hInstance,int nShowCmd,int width,int height)
{
	ZeroMemory(&m_wcex,sizeof(WNDCLASSEX));
	m_wcex.style			= CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc		= MyProc;	
	m_wcex.hInstance		= hInstance;
	m_wcex.cbSize			= sizeof(WNDCLASSEX);
	m_wcex.hCursor			= LoadCursor(0, IDC_ARROW);
	m_wcex.lpszClassName	= APPLICATIONNAME;
	m_wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);

	if(RegisterClassEx(&m_wcex) == 0)
	{
		return E_FAIL;
	}
	m_cWidth = width;
    m_cHeight = height;
	m_wWidth  = width + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	m_wHeight = height + GetSystemMetrics(SM_CYFIXEDFRAME) * 2
					+GetSystemMetrics(SM_CYCAPTION);
	m_WINDOWMODE = 1;

	if(m_WINDOWMODE)
	{
			//Windowモード
		m_hwnd = CreateWindow(
								APPLICATIONNAME,
								WINDOWNAME,
								WS_OVERLAPPED | WS_MINIMIZEBOX |WS_SYSMENU |WS_CAPTION | WS_VISIBLE,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								m_wWidth,m_wHeight,
								GetDesktopWindow(), 
								NULL,
								m_wcex.hInstance,
								NULL );
	}	
	else
	{	
			//フルスクリーン
		m_hwnd = CreateWindow(
								APPLICATIONNAME,
								WINDOWNAME,
								WS_POPUP | WS_VISIBLE | WS_BORDER,
								0,
								0,
								width,
								height,
								HWND_DESKTOP,
								NULL,
								m_wcex.hInstance,
								NULL );
		DEVMODE	dev;
		dev.dmFields		= DM_PELSWIDTH | DM_PELSHEIGHT;
		dev.dmSize			= sizeof(DEVMODE);
		dev.dmPelsHeight	= height;
		dev.dmPelsWidth		= width;
		ChangeDisplaySettings(&dev,CDS_FULLSCREEN);
	}
	SetProp(m_hwnd,PROP_WINPROC, this);
    ShowWindow(m_hwnd,nShowCmd);
    UpdateWindow(m_hwnd);
	return S_OK;
}



//ウィンドウプロシージャ
LRESULT WinManager::MyProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	
	WinManager* me =(WinManager*) GetProp(hWnd,PROP_WINPROC);
	switch( msg )
	{
	case WM_DESTROY:
		RemoveProp(hWnd, PROP_WINPROC);
		me->Release();
		PostQuitMessage(0);
		return S_OK;
    }
	if(me)
		return me->AppProc(msg, wParam, lParam);
	else
		return DefWindowProc( hWnd, msg, wParam, lParam );
}

BOOL WinManager::SetWindowTitle(const wchar_t* in_title)
{
	return SetWindowTextW(this->m_hwnd,in_title);
}