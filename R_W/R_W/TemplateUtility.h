#ifndef ___TEMPLATE_UTILITY_2012_01_12___
#define ___TEMPLATE_UTILITY_2012_01_12___
template<class T> inline void tSafeRelease(T *ptr)
{
    if(ptr)
    {
        ptr->Release();
        ptr=NULL;
    }
}

template<class T> inline void tSafeDelete(T *ptr)
{
    if(ptr)
    {
        delete ptr;
        ptr =NULL;
    }
}

template<class T> inline void tSafeDeleteArray(T *ptr)
{
    if(ptr)
    {
        delete[] ptr;
        ptr = NULL;
    }
}

template<class T,class U> inline bool IsHit(const T& obj1 , const U& obj2)
{
    return true;
}
#endif//___TEMPLATE_UTILITY_2012_01_12___