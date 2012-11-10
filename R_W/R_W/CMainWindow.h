#ifndef ___CMAINWINDOW_2011_11_26___
#define ___CMAINWINDOW_2011_11_26___
#include "WindowManager.h"
#include "CSequence.h"
#include "FPSCounter.h"
///メインウィンドウなのでシングルトン


class CMainWindow : public WinManager
{
public:
static	CMainWindow& GetMainWindow()
	{
		static CMainWindow Instance;
		return Instance;
	}
	LRESULT AppProc(UINT msg,WPARAM wParam,LPARAM lParam);
	HRESULT MsgLoop();
	VOID AppLoop();
	HRESULT Release();
private:
	CMainWindow()
		:m_fpsc()
    {ZeroMemory(&m_rect,sizeof(m_rect));};
    ~CMainWindow(){};
	CMainWindow(CMainWindow& obj){};
	void operator=(CMainWindow& obj){};
    CSequence   m_sequence;
	CFPSCounter m_fpsc;
protected:
    void HookKey(WPARAM,LPARAM);
    void ChangeScr2Window();
    void ChangeScr2Full();

	RECT     m_rect;
};

#endif //___CMAINWINDOW_2011_11_26___