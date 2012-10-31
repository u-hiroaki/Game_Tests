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
    C2DSprite Ore;
    bool subSPFlg[NUMsubSP];

    void func1();
    void func2();
};
struct button
{
    bool push[4];
};
extern button g_button;
void SetUButton(HWND hwnd,LPARAM lparam);
void SetDButton(HWND hwnd,LPARAM lparam);
void SetLButton(HWND hwnd,LPARAM lparam);
void SetRButton(HWND hwnd,LPARAM lparam);