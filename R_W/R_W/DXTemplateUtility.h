#ifndef ___DX_TEMPLATE_UTILITY_2012_01_16___
#define ___DX_TEMPLATE_UTILITY_2012_01_16___
#include <d3d9.h>

//COMPtrのテンプレート
template<class T> class tComPtr
{
private:
    T*  m_Instance;
public:
    explicit tComPtr(T* ptr=NULL)
    {
        m_Instance = ptr;
    }
    tComPtr(const tComPtr& obj)
    {
        if(obj.m_Instance)
            obj.m_Instance->AddRef();
        m_Instance = obj.m_Instance;
    }
    tComPtr& operator=(const tComPtr& obj){
        if(obj.m_Instance)
            obj.m_Instance->AddRef();
        if(m_Instance)
            m_Instance->Release();
        m_Instance = obj.m_Instance;
        return *this;
    }
    ~tComPtr(){if(m_Instance)m_Instance->Release();};
    T* GetPtr(){return m_Instance;}
    T** GetPPtr(){return &m_Instance;}
    T** ToCreator(){
        if(m_Instance)
            m_Instance->Release();
        return &m_Instance;
    }
};

#endif//___DX_TEMPLATE_UTILITY_2012_01_16___