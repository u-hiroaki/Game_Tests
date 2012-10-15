#include <windows.h>
#include "CMainWindow.h"
#include "CDirectXDevice.h"
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

INT WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
   	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
    CMainWindow::GetMainWindow().Init(hinstance,nShowCmd,800,600);
    CDirectXDevice::GetDxDevice().Initialize(
        CMainWindow::GetMainWindow().GetWindowHandle(),1,
        CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());

	CMainWindow::GetMainWindow().MsgLoop();
	return 0;
}