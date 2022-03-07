#ifndef __CLUSTERING__
#define __CLUSTERING__

#include <NuagePoints.hpp>

template <class T>
class Clustering
{
private:
    int mNbClusters;
    NuagePoints<T> mNuage; 
    int* mIdCluster;
public:
    Clustering();
    Clustering(int, NuagePoints<T>&);
    Clustering(const Clustering<T>&);
    ~Clustering() { delete [] mIdCluster; }

    int& operator[](size_t i){ return mIdCluster[i]; }
    virtual Clustering<T>& operator=(const Clustering<T>&); 

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
    mNbClusters = 1;
    mNuage = NuagePoints<T>();
    mIdCluster = new int[0];
}

template <class T> 
Clustering<T>::Clustering(int nCl, NuagePoints<T>& N): mNbClusters(nCl), mNuage(N)
{
    mIdCluster = new int[mNuage.size()];
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        mIdCluster[i] = -10;
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
}

#endif