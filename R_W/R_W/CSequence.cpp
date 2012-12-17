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
    L"Data/chicken.png",tex.GetPPtr());
        D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/bullet2.png",tex2.GetPPtr());
    D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/Chara.png",tex3.GetPPtr());    
    mainSP.setTexture(tex,true);
    mainSP.setPos(mainx-128,mainy-128);
    #pragma omp parallel for
    for(int i = 0;i<NUMsubSP;++i)
    {
        int deg= 0;
        deg = (i%36)*20;
        float rad = (float)deg * D3DX_PI/ 180;

        subSP[i].setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
        subSP[i].setTexture(tex2,true);
        subSP[i].setScale(0.5,0.5);
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
    (this->*funcptr)();
}
void CSequence::InnerUpdate()
{
    func2();
    func1();
    mainSP.draw();
    Ore.draw();
}

void CSequence::func1()
{
    static int count=0;
    static int timer =0;
    if((timer%10)==0)
    {
        float mainX,mainY;
        mainSP.getPos(&mainX,&mainY);
        for(int i=0;i<10;++i)
        {
            if(count >= NUMsubSP)
                break;
            subSP[count].setActivity(true); 
            subSP[count].setPos(mainX+128,mainY+128);
            count++;
        }
    }
    float vec = 0.25f;
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
    timer++;
}

void CSequence::func2()
{
    float posX,posY;
    static int move=1.0f;
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
    mainSP.getPos(&posX,&posY);
    mainSP.setPos(posX+5*move,posY);
    if(move < 0 && posX <-10)
        move *= -1;
    else if(move > 0 && posX > 800 - 200)
        move *= -1;
}


void SetUButton(HWND hwnd,LPARAM lparam){g_button.push[0] = true;};
void SetDButton(HWND hwnd,LPARAM lparam){g_button.push[1] = true;};
void SetLButton(HWND hwnd,LPARAM lparam){g_button.push[2] = true;};
void SetRButton(HWND hwnd,LPARAM lparam){g_button.push[3] = true;};

unsigned __stdcall func3(void* ptr)
{
    C2DBuffer* data = (C2DBuffer*)ptr;
    float vec = 0.25f;
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

void CSequence::InnerInit()
{
    static int init_count = 0;
    if(!init_count)
    {
        HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,func4,this,0,NULL);
        tComPtr<IDirect3DTexture9> tex4;
        D3DXCreateTextureFromFile(
        CDirectXDevice::GetDxDevice().GetDevice(),
        L"Data/now_loading.png",tex4.GetPPtr());    
         this->loading.setTexture(tex4,true);
         this->loading.setPos(200,100);
    }
    loading.setAlpha((float)(100-init_count)/100);
    loading.draw();
    if(init_count == 100)
        this->funcptr = &CSequence::InnerUpdate;
    init_count++;
}

unsigned __stdcall func4(void* ptr)
{
    CSequence* seq = (CSequence*) ptr;
    seq->Init();
    return 0;
}