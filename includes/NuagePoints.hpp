#ifndef __NUAGEPOINTS__
#define __NUAGEPOINTS__

#include <iostream>
#include <cmath>
#include <iterator>
#include <exception>
#include <cassert>


using namespace std;

template<class T> double distance_euclidienne(T, T);

// ? Which assumptions on T? 

template <class T>
class NuagePoints
{
private:
    double (*mDistance)(T, T);
    size_t mLenTab;
    T* mTab;

public:
    NuagePoints(): mDistance(nullptr), mLenTab(0) { mTab = new T[0]; }
    
    NuagePoints(size_t nbobs, T* obs, 
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
            mTab[i] = P.mTab[i];
        }
    } // Has no tests

    ~NuagePoints()
    {
        delete [] mTab;
    }

    size_t size() const { return mLenTab; }
    void set_distance( double(*dis)(T, T) ) { mDistance = dis; }
    double get_distance(T a, T b) const { return mDistance(a, b); }

    NuagePoints<T>& operator=(const NuagePoints<T>&); // Has no tests
    
    T operator[] (size_t i) const
    { 
        if (i >= (this -> size()))
        {
            throw out_of_range("");        
        }
        return mTab[i]; 
    }
    
    NuagePoints<T>  operator+(const NuagePoints<T>&);

};

template<class T>
ostream& operator<<(ostream& o, NuagePoints<T> P)
{
    T tmpPoint;
    for(auto j = 0u; j < P.size(); ++j)
    {
        
        tmpPoint = P[j];
        o << "( ";
        for (auto it = begin(tmpPoint); it != end(tmpPoint); ++it)
        {
            o << *it << " ";
        }
        o << ")\n";
    
    }
    return o; 
}

template<class T>
NuagePoints<T>& NuagePoints<T>::operator=(const NuagePoints<T>& P)
{
    this -> mLenTab = P.mLenTab;
    this -> mDistance = P.mDistance;
    auto tmpTab = mTab; 
    mTab = new T[mLenTab];
    for (size_t i = 0; i < mLenTab; ++i)
    {
        mTab[i] = P.mTab[i];
    } 
    delete [] tmpTab;
    return *this;
}

template<class T>
NuagePoints<T> NuagePoints<T>::operator+(const NuagePoints<T>& P)
{
    size_t len = mLenTab + P.mLenTab;
    T tmpTab[len];
    size_t i = 0;
    while( i < mLenTab )
    {
        tmpTab[i] = (*this)[i];
        ++i;
    }
    assert(i==mLenTab);
    while( i < len )
    {
        tmpTab[i] = P.mTab[i-mLenTab];
        ++i;
    }
    assert(i==len);
    NuagePoints<T> res(len, tmpTab, mDistance);
    return res;
}

template<class T> 
double distance_euclidienne(T a, T b)
{
    if (a.size() != b.size())
    {
        throw invalid_argument("a and b should have the same length");
    } 
    double res = 0;
    auto iteA = begin(a);
    auto iteB = begin(b);
    while (iteA != end(a) && iteB != end(b))
    {
        res += (double) ((*iteA) - (*iteB)) * ((*iteA) - (*iteB));
        ++iteA;
        ++iteB;
    }
    return sqrt(res);
}

template<class T, int p> 
double distance_minkovsky(T a, T b)
{
   /* 
    ** Distance de Minkovsky définie par
    ** $$d_p(x,y) = \left(\sum_{k=1}^d{\|x_k-y_k\|^p}\right)^{1/p} $$
    ** pour $ p \geq 1 $
    ** 
    ** si $p=-1$ 
    ** on considère la norme de minkovsky infinie
    ** d_\infty (x, y) = \max_{k\in\{1, ... , d\}\|x_k-y_k\|}
    */

    if (p < 1 && p!=-1)
    {
        throw invalid_argument("p should be equal to -1 or greater or equal to 1");
    }

    if (a.size() != b.size())
    {
        throw invalid_argument("a and b should have the same length");
    } 
    double res = 0;
    auto iteA = begin(a);
    auto iteB = begin(b);

    if (p == -1)
    {
        while (iteA != end(a) && iteB != end(b))
        {
            res = max(fabs((*iteA) - (*iteB)), res);
            ++iteA;
            ++iteB;
        }
    }
    else if (p==2)
    {
        while (iteA != end(a) && iteB != end(b))
        {
            res += (double) ((*iteA) - (*iteB)) * ((*iteA) - (*iteB));
            ++iteA;
            ++iteB;
        }
        res = sqrt(res);
    }
    else
    {
        while (iteA != end(a) && iteB != end(b))
        {
            res += powf(fabs((*iteA) - (*iteB)), p);
            ++iteA;
            ++iteB;
        }
        res = powf(res, (double) 1/p);
    }
    
    return res;
}

#endif