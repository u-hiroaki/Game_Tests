#include "CSequence.h"
#include "CDirectXDevice.h"
#include"CMainWindow.h"
#include <math.h>
#include <process.h>
button g_button;
float SinTable[NUMsubSP];
float CosTable[NUMsubSP];
float SinTable2[360];
float CosTable2[360];

void CSequence::Init()
{
    C2DBuffer::begin_first(CDirectXDevice::GetDxDevice().GetDevice());
    float mainx=CMainWindow::GetMainWindow().GetWindowcWidth()/2,
        mainy=CMainWindow::GetMainWindow().GetWindowcHeight()/4;

    mainSP.setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
    tComPtr<IDirect3DTexture9> tex;
    tComPtr<IDirect3DTexture9> tex2;
    tComPtr<IDirect3DTexture9> tex3;
    D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/no_picture.jpg",tex.GetPPtr());
        D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/bullet2.png",tex2.GetPPtr());
    D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/Chara.png",tex3.GetPPtr());    
    mainSP.setTexture(tex,true);
    mainSP.setPos(mainx-64,mainy-64);
    #pragma omp parallel for
    for(int i = 0;i<NUMsubSP;++i)
    {
        int deg= 0;
        deg = (i%36)*10;
        float rad = (float)deg * D3DX_PI/ 180;

        subSP[i].setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
        subSP[i].setTexture(tex2,true);
        subSP[i].setSize(32,32);
        subSP[i].setActivity(false);
        SinTable[i] = sin(rad);
        CosTable[i] = cos(rad);
    }
    this->Ore.setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
    this->Ore.setTexture(tex3,true);
    this->Ore.setPos(mainx-64*0.3f,mainy*3 -64*0.3f);
    this->Ore.setScale(0.3,0.3); 
    this->Ore.setActivity(true);
}

void CSequence::Update(bool frame)
{
   if(!frame)
{    func2();
    func1();
    }
    mainSP.draw();
    Ore.draw();
}

void CSequence::func1()
{
    static int count=0;
    static int timer =0;
    if(!(timer%15))
    {
        float mainX,mainY;
        mainSP.getPos(&mainX,&mainY);
        for(int i=0;i<5;++i)
        {
            if(count >= NUMsubSP)
                break;
            subSP[count].setActivity(true); 
            subSP[count].setPos(mainX+64,mainY+64);
            count++;
        }
    }
    float vec = 3.0f;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,func3,subSP,0,NULL);
    for(int i=0;i<NUMsubSP/2;++i)
    {
        if(!subSP[i].getActivity())
            continue;
        float posX,posY;
        subSP[i].getPos(&posX,&posY);
        subSP[i].setPos(posX+CosTable[i]*vec,posY+vec*SinTable[i]);
        subSP[i].getPos(&posX,&posY);
        if(posX < 0 || posX > 800)
            subSP[i].setActivity(false);
        if(posY < 0 || posY > 600)
            subSP[i].setActivity(false);
		subSP[i].draw();
    }
    //DWORD ret=0;
    WaitForSingleObject(hThread,INFINITE);
    CloseHandle(hThread);
	    for(int i=NUMsubSP/2;i<NUMsubSP;++i)
    {
        if(!subSP[i].getActivity())
            continue;
		subSP[i].draw();
		}
    if(count == NUMsubSP)
    {
        for(int i=0;i<NUMsubSP/4;++i)
            if(subSP[i].getActivity())
                return;
        count=0;
    }
}

void CSequence::func2()
{
    float posX,posY;
    float UD=0.0f,LR=0.0f;
    Ore.getPos(&posX,&posY);
    if(g_button.push[0])
        UD = -5.0f;
    if(g_button.push[1])
        UD = 5.0f;
    if(g_button.push[2])
        LR = -5.0f;
    if(g_button.push[3])
        LR = 5.0f;
    Ore.setPos(posX+LR,posY+UD);
}


void SetUButton(HWND hwnd,LPARAM lparam){g_button.push[0] = true;};
void SetDButton(HWND hwnd,LPARAM lparam){g_button.push[1] = true;};
void SetLButton(HWND hwnd,LPARAM lparam){g_button.push[2] = true;};
void SetRButton(HWND hwnd,LPARAM lparam){g_button.push[3] = true;};

unsigned __stdcall func3(void* ptr)
{
    C2DBuffer* data = (C2DBuffer*)ptr;
    float vec = 3.0f;
     for(int i=NUMsubSP/2;i<NUMsubSP;++i)
    {
        if(!data[i].getActivity())
            continue;
        float posX,posY;
        data[i].getPos(&posX,&posY);
        data[i].setPos(posX+CosTable[i]*vec,posY+vec*SinTable[i]);
        data[i].getPos(&posX,&posY);
        if(posX < 0 || posX > 800)
            data[i].setActivity(false);
        if(posY < 0 || posY > 600)
            data[i].setActivity(false);
    }
     return 0;
}