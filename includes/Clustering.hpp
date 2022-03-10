#ifndef __CLUSTERING__
#define __CLUSTERING__

#include <NuagePoints.hpp>

using namespace std;

template <class T>
class Clustering
{
protected:
    int mNbClusters;
    NuagePoints<T> mNuage; 
    int* mIdCluster;
    size_t* mNbElemCluster;
public:
    Clustering();
    Clustering(int, NuagePoints<T>&);
    Clustering(const Clustering<T>&);
    virtual ~Clustering() 
    { 
        delete [] mIdCluster;
        delete [] mNbElemCluster; 
    }

    int& operator[](size_t i){ return mIdCluster[i]; }
    virtual Clustering<T>& operator=(const Clustering<T>&); 

    size_t  get_nbElemCluster(size_t i){ return mNbElemCluster[i]; }
    
    int  get_nbClusters(){ return mNbClusters; }
    void set_nbClusters(int n)
    {   
        if (n>0) 
        { 
            mNbClusters = n; 
        } 
        else 
        { 
            throw invalid_argument("Number of Clusters should be positive.");
        }
    }

    NuagePoints<T>   get_nuage()  { return mNuage; } 
    void set_nuage(NuagePoints<T> N) { mNuage = N; }

    virtual void calculClusters() = 0;
};

template <class T> 
Clustering<T>::Clustering()
{
    mNbClusters = 0;
    mNuage = NuagePoints<T>();
    mIdCluster = new int[0];
    mNbClusters = new size_t[0];
}

template <class T> 
Clustering<T>::Clustering(int nCl, NuagePoints<T>& N): mNbClusters(nCl), mNuage(N)
{
    mIdCluster = new int[mNuage.size()];
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        mIdCluster[i] = -10;
    }
    mNbElemCluster = new size_t[mNbClusters];
    for (auto i = 0l; i < mNbClusters; ++i)
    {
        mNbElemCluster[i] = 0;
    }
}

template <class T> 
Clustering<T>::Clustering(const Clustering<T>& C)
{
    mNbClusters = C.mNbClusters;
    mNuage = C.mNuage;
    mIdCluster = new int[mNuage.size()]; 
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        mIdCluster[i] = C.mIdCluster[i];
    }
    mNbElemCluster = new size_t[mNbClusters]; 
    for (auto i = 0l; i < mNbClusters; ++i)
    {
        mNbElemCluster[i] = C.mNbElemCluster[i];
    }
}

template <class T> 
Clustering<T>& Clustering<T>::operator=(const Clustering<T>& C)
{
    mNbClusters = C.mNbClusters;
    mNuage = C.mNuage;
    auto tmp = mIdCluster;
    mIdCluster = new int[mNuage.size()]; 
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        mIdCluster[i] = C.mIdCluster[i];
    }
    delete [] tmp;
    auto tmp1 = mNbElemCluster;
    mNbElemCluster = new size_t[mNbClusters]; 
    for (auto i = 0l; i < mNbClusters; ++i)
    {
        mNbElemCluster[i] = C.mNbElemCluster[i];
    }
    delete [] tmp1;
    return *this;
}

#endif