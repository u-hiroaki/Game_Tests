#ifndef ___C_EFFECT_H_2012_10_17___
#define ___C_EFFECT_H_2012_10_17___
#include <d3d9.h>
#include <d3dx9.h>
#include "DXTemplateUtility.h"

class CEffect
{
public:
    CEffect(){
    }
    ~CEffect(){}
    bool CreateEffectFromFile(const wchar_t* filename);
private:
    tComPtr<ID3DXEffect> m_effect_ptr;
};

#endif//___C_EFFECT_H_2012_10_17___