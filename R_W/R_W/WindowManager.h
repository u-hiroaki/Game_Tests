#ifndef ___WinManager___
#define ___WinManager___
#include <tchar.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <map>

template <class Key,class Value>
bool insert2map(std::map<Key,Value> &_Table,Key _key,Value _val)
    {
        if(_Table.end() != _Table.find(_key))
            return false;
        else
        {
            _Table.insert(std::map<Key,Value>::value_type(_key,_val));
            return true;}
    }
#ifndef PROP_WINPROC
extern LPCWSTR PROP_WINPROC;
#endif
typedef void (*KeyHookPtr)(HWND,LPARAM);
//³¨İÄŞ³‚ÌŠÇ—¸×½‚ÌŠî’ê¸×½
class WinManager
{
public:
	//ºİ½Ä×¸À‹y‚ÑÃŞ½Ä×¸À
	WinManager(){};
	virtual ~WinManager(){};
protected:
	//ŠeíÒİÊŞ•Ï”
	WNDCLASSEX	m_wcex;//³²İÄŞ³¸×½
	HWND    m_hwnd;//³²İÄŞ³ÊİÄŞÙ
	MSG     m_msg;//Ò¯¾°¼Ş
	int     m_wWidth;//³²İÄŞ³‚Ì•
	int     m_wHeight;//³²İÄŞ³‚Ì‚‚³
    int     m_cWidth;//¸×²±İÄ—Ìˆæ‚Ì•
    int     m_cHeight;//¸×²±İÄ—Ìˆæ‚Ì‚‚³
	int     m_WINDOWMODE;//ÌÙ½¸Ø°İ‚©³²İÄŞ³Ó°ÄŞ‚©
    std::map<WPARAM,KeyHookPtr> m_KeyHookTable;
    static void    PostDestroy(HWND hwnd,LPARAM lp){PostMessage(hwnd,WM_DESTROY,0,0);}
public:
	//ŠeíÒİÊŞŠÖ”
	//‰Šú‰»
	HRESULT Init(HINSTANCE hInstance,int nShowCmd,int,int);
	//º°ÙÊŞ¯¸
	static  LRESULT CALLBACK MyProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	virtual LRESULT AppProc(UINT msg, WPARAM wParam, LPARAM lParam ) = 0;
	//Ò¯¾°¼ŞÙ°Ìß
	virtual HRESULT MsgLoop() = 0;
	virtual VOID	AppLoop() = 0;
	virtual HRESULT Release() = 0;
    inline  HWND GetWindowHandle()const{return m_hwnd;}
    inline  int GetWindowcHeight()const {return m_cHeight;}
    inline  int GetWindowcWidth()const{return m_cWidth;}
    bool SetKeyHook(UINT msg,KeyHookPtr ptr){return insert2map(m_KeyHookTable,msg,ptr);}
	BOOL SetWindowTitle(const wchar_t* in_title);
};

#endif //___WinManager___