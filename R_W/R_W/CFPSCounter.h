#ifndef ___C_FPS_COUNTER_2012_0130___
#define ___C_FPS_COUNTER_2012_0130___
#include <windows.h>
#include <list>
class CFPSCounter
{
public:
    CFPSCounter(){};
    ~CFPSCounter(){};
    double GetFPS()const{return m_fps}

private:
    double m_fps;
    std::list<LARGE_INTEGER> m_data;
};
#endif//___C_FPS_COUNTER_2012_0130___