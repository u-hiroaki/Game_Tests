#include "CDirectXDevice.h"
#pragma comment(lib,"d3d9.lib")
#include "TemplateUtility.h"


unsigned clearcolor = D3DCOLOR_XRGB(50, 152, 200);

HRESULT CDirectXDevice::Initialize(const HWND in_hwnd,const BOOL in_windowmode,
                                   const int in_wWidth,const int in_wHeight)
{
    m_hwnd =in_hwnd;
    D3DCAPS9 caps;
	DWORD dwFlag;
	D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE disp;
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	if( NULL == ( m_pd3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

   	m_pd3d9->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps);//ﾌﾟﾗｲﾏﾘのﾃﾞｨｽﾌﾟﾚｲｱﾀﾞﾌﾟﾀ(=ｸﾞﾗﾎﾞ)の能力取得
	m_pd3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&disp);
	if(caps.VertexShaderVersion < D3DVS_VERSION(1,1))		//頂点ｼｪｰﾀﾞのﾊﾞｰｼﾞｮﾝ確認
		dwFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;		//1.1未満なのでｿﾌﾄｳｪｱ処理
	else
		dwFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;		//1.1以上なのでﾊｰﾄﾞｳｪｱ処理
	if(caps.MaxStreams < 3)
	{
		MessageBox(in_hwnd,TEXT("頂点ストリーム数が足りません"),TEXT("D3D初期化エラー"),NULL);
		return E_FAIL;
	}

	d3dpp.Windowed = in_windowmode;//ｳｲﾝﾄﾞｳﾓｰﾄﾞの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = in_hwnd;
	if(!d3dpp.Windowed)							//ﾊﾞｯｸﾊﾞｯﾌｧの設定用にフルスクリーンかどうかを判定
		d3dpp.BackBufferFormat = disp.Format;
	else
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//現在の画面モードを利用
	//Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.BackBufferHeight = in_wHeight;
	d3dpp.BackBufferWidth = in_wWidth;
	d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3dpp = d3dpp;
    
    m_pd3d9->CreateDevice(D3DADAPTER_DEFAULT,DeviceType,in_hwnd,dwFlag,&m_d3dpp,&m_pd3ddev);
//   	m_pd3ddev->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(243, 152, 0),1.0f,0);
    return S_OK;
}

void CDirectXDevice::Release()
{
    tSafeRelease(this->m_pd3ddev);
    tSafeRelease(this->m_pd3d9);
}

HRESULT CDirectXDevice::Begin()
{
    m_pd3ddev->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,clearcolor,1.0f,0);
    m_pd3ddev->BeginScene();
    return S_OK;
}

HRESULT CDirectXDevice::End()
{
    m_pd3ddev->EndScene();
    m_pd3ddev->Present(NULL,NULL,NULL,NULL);
    return S_OK;
}

void CDirectXDevice::ResetDevice()
{
    m_pd3ddev->Reset(&m_d3dpp);
}