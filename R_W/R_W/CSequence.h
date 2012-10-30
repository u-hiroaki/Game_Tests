#pragma once
#include "C2DSprite.h"
const int NUMsubSP = 1000;//682;
class CSequence
{
public:
    CSequence(){}
    ~CSequence(){}
    void Update(bool frame);
    void Init();
protected:
    C2DSprite mainSP;
    C2DSprite subSP[NUMsubSP];
    bool subSPFlg[NUMsubSP];

    void func1();
};