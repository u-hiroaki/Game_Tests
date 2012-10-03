#ifndef ___C_DIRECTX_DEVICE_2011_11_29___
#define ___C_DIRECTX_DEVICE_2011_11_29___
#include <windows.h>
#include <d3d9.h>
#include "DXTemplateUtility.h"
//DirectXのデバイス管理クラス
//出来るなら、Dx9とDx11でやれたらいいね?
//要リファクタリング
class CDirectXDevice
{
public:
    static      CDirectXDevice& GetDxDevice(){
    static      CDirectXDevice Instance;
    return      Instance;}
    void     Release();
    HRESULT     Initialize(const HWND,const BOOL,const int,const int);
    LPDIRECT3DDEVICE9 GetDevice(){return m_pd3ddev;}
//    void        SetBackBufferFormat(const int,const int);
    HRESULT     Begin();
    HRESULT     End();
private:
    CDirectXDevice(){
        m_pd3ddev=NULL;
        m_pd3d9=NULL;
        m_hwnd=NULL;
    }
    CDirectXDevice(CDirectXDevice& obj){}
    ~CDirectXDevice(){this->Release();}
    void operator=(CDirectXDevice& obj){};
	LPDIRECT3DDEVICE9			m_pd3ddev;
	LPDIRECT3D9					m_pd3d9;
    HWND                        m_hwnd;
	D3DPRESENT_PARAMETERS       m_d3dpp;
    void    ResetDevice();
};

extern unsigned clearcolor;
#endif//___C_DIRECTX_DEVICE_2011_11_29___