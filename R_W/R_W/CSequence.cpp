#include "CSequence.h"
#include "CDirectXDevice.h"
#include"CMainWindow.h"
#include <math.h>

float SinTable[NUMsubSP];
float CosTable[NUMsubSP];
void CSequence::Init()
{
    float mainx=CMainWindow::GetMainWindow().GetWindowcWidth()/2,
        mainy=CMainWindow::GetMainWindow().GetWindowcHeight()/4;
    mainSP.setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
    tComPtr<IDirect3DTexture9> tex;
    tComPtr<IDirect3DTexture9> tex2;
    D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/no_picture.jpg",tex.GetPPtr());
        D3DXCreateTextureFromFile(
    CDirectXDevice::GetDxDevice().GetDevice(),
    L"Data/bullet.png",tex2.GetPPtr());
    mainSP.setTexture(tex,true);
    mainSP.setPivotCenter();
    mainSP.setPos(mainx,mainy);
    for(int i = 0;i<NUMsubSP;++i)
    {
        int tmp = (i+90) / 180;
        int deg= 0;
        if(tmp&1)
        {
            deg = 180 -(i+90)%180;
        }
        else deg = (i+90)%180;
        float rad = (float)deg * 2 * D3DX_PI/ 360;
        subSP[i].setScreenSize(CMainWindow::GetMainWindow().GetWindowcWidth(),
        CMainWindow::GetMainWindow().GetWindowcHeight());
        subSP[i].setPos(mainx+15*(i%10),mainy);
        subSP[i].setTexture(tex2,true);
        subSP[i].setScale(0.2,0.2);
        subSP[i].setActivity(false);
        SinTable[i] = sin(rad);
        CosTable[i] = 3*cos(rad);
    }

}

void CSequence::Update(bool frame)
{
    mainSP.draw();
//    if(frame)
        func1();
    for(int i=0;i<NUMsubSP;++i)
        subSP[i].draw();
}

void CSequence::func1()
{
    static int timer = 0;
    static int count = 0;
    if(timer % 2 == 0)
    {
        for(int i=0;i<10;++i)
      { 
          subSP[count].setActivity(true);
          subSP[NUMsubSP-count].setActivity(true);
        if(count < NUMsubSP/2)
            ++count;
        }
    }
    for(int i=0;i<NUMsubSP;++i)
    {
        float posX,posY;
        float vec = 4.0f;
        subSP[i].getPos(&posX,&posY);
        if(subSP[i].getActivity())
            subSP[i].setPos(posX+vec*CosTable[i],posY+vec*SinTable[i]);
    }
    timer++;
}