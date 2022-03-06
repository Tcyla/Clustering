#ifndef __NUAGEPOINTS__
#define __NUAGEPOINTS__

#include <iostream>
#include <cmath>
#include <exception>


using namespace std;

template<class T> double distance_euclidienne(T, T);

template <class T>
class NuagePoints
{
private:
    double (*mDistance)(T, T);
    size_t mLenTab;
    T* mTab;

public:
    NuagePoints(): mDistance(nullptr), mLenTab(0) { mTab = T(); }
    
    NuagePoints(int nbobs, T* obs, 
        double(*dis)(T, T) = distance_euclidienne<T>): mDistance(dis), 
                                                       mLenTab(nbobs) 
    {
        mTab = new T[mLenTab];
        for (size_t i = 0; i < mLenTab; ++i)
        {
            mTab[i] = obs[i];
        }
    }
    
    NuagePoints(const NuagePoints<T>& P):  mDistance(P.mDistance),
                                           mLenTab  (P.mLenTab)
    {
        mTab = new T[mLenTab];
        for (size_t i = 0; i < mLenTab; ++i)
        {
            mTab[i] = P[i];
        }
    }

    ~NuagePoints()
    {
        delete [] mTab;
    }

    size_t size(){ return mLenTab; }  
    void set_distance( double(*dis)(T, T) ) { mDistance = dis; }
    double get_distance(T a, T b) { return mDistance(a, b); }

    NuagePoints<T>& operator=(const NuagePoints<T>&);
    T& operator[](size_t i) { return mTab[i]; }
    NuagePoints<T>  operator+(const NuagePoints<T>&);

};


#endif