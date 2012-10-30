#include <windows.h>
#include "CMainWindow.h"
#include "CDirectXDevice.h"
#include <stdlib.h>
#include <crtdbg.h>
#include "TemplateUtility.h"
#define _CRTDBG_MAP_ALLOC

#include "C2DSprite.h"

extern bool frame;
void test(HWND hwnd,LPARAM lparam)
{
    SetWindowText(hwnd,TEXT("すぺーすきーがおされたっぽい"));
    frame = true;
}

void test2(HWND hwnd,LPARAM lparam)
{
    SetWindowText(hwnd,TEXT("えーがおされたっぽい"));
}

void SetClearRed(HWND hwnd,LPARAM lparam)
{
    SetWindowText(hwnd,TEXT("あかいよ！"));
    clearcolor = D3DCOLOR_XRGB(255,0,0);
}

void SetClearBlue(HWND hwnd,LPARAM lparam)
{
    SetWindowText(hwnd,TEXT("あおいよ！"));
    clearcolor = D3DCOLOR_XRGB(0,0,255);
}

void SetClearGreen(HWND hwnd,LPARAM lparam)
{
    SetWindowText(hwnd,TEXT("みどりだよ！！"));
    clearcolor = D3DCOLOR_XRGB(0,255,0);
}



INT WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
   	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
    CMainWindow::GetMainWindow().Init(hinstance,nShowCmd,800,600);
    CMainWindow::GetMainWindow().SetKeyHook(VK_SPACE,test);
    CMainWindow::GetMainWindow().SetKeyHook('A',test2);
    CMainWindow::GetMainWindow().SetKeyHook('R',SetClearRed);
    CMainWindow::GetMainWindow().SetKeyHook('G',SetClearGreen);
    CMainWindow::GetMainWindow().SetKeyHook('B',SetClearBlue);
    CDirectXDevice::GetDxDevice().Initialize(
        CMainWindow::GetMainWindow().GetWindowHandle(),1,
        CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
    C2DSprite::begin_first(CDirectXDevice::GetDxDevice().GetDevice());
	CMainWindow::GetMainWindow().MsgLoop();
	return 0;
}