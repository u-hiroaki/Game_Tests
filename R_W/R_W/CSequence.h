#pragma once
#include "C2DSprite.h"
#include "C2DBuffer.h"
//const int NUMsubSP = 1500;//682;
#define NUMsubSP  2000
class CSequence
{
    typedef void (CSequence::*upfunc)();
public:
    CSequence(){
        funcptr = &CSequence::InnerInit;
    }
    ~CSequence(){}
    void Update(bool frame);
    void InnerUpdate();
    void Init();
    void InnerInit();
protected:
    C2DSprite mainSP;
    C2DBuffer subSP[NUMsubSP];
    C2DSprite Ore;
    C2DSprite loading;
    bool subSPFlg[NUMsubSP];
    upfunc  funcptr;
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
unsigned __stdcall func3(void* );
unsigned __stdcall func4(void* );