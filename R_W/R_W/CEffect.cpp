#include "CEffect.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "d3dx9.lib")

bool CEffect::CreateEffectFromFile(const wchar_t* filename)
{
    if(m_effect_ptr.GetPtr()==NULL)
        return false;
    ID3DXBuffer *error = 0;
    //if(FAILED( D3DXCreateEffectFromFile( dev, L"Shader\\sample.fx", 0, 0, 0, 0, &effect, &error) ))
    //{
    //    return false;
    //}

    return false;
}