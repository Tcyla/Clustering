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

    size_t  get_nbElemCluster(size_t i) const { return mNbElemCluster[i]; }
    
    size_t  get_nbClusters() const { return mNbClusters; }
    
    void set_nbClusters(int n)
    {
        if (n < 0) 
            throw invalid_argument("the number of clusters should be a positive integer.");
        if (n > (int64_t) get_nuage_size())
            throw invalid_argument("the number of clusters should be lesser than the numbre of points.");

        auto oldNbClusters = mNbClusters;
        mNbClusters = n;
        if (mNbClusters > oldNbClusters)
        {
            // ????? !! ? 
            computeNbElemCluster();
        }
    }

    int get_idCluster(size_t i) const { return mIdCluster[i]; }

    T get_point(size_t i) const { return mNuage[i]; }
    
    NuagePoints<T>& get_nuage() { return mNuage; }
    size_t get_nuage_size() const { return mNuage.size(); }
    void set_nuage(NuagePoints<T> N) { mNuage = N; }

    void computeNbElemCluster()
    {
        auto tmp = mNbElemCluster;
        mNbElemCluster = new size_t[mNbClusters+1];
        
        for (auto i = 0l; i <= mNbClusters; ++i)
        {
            mNbElemCluster[i] = 0;
        }

        auto idcluster = 0l;
        for (auto i = 0u; i < this -> get_nuage_size(); ++i)
        {
            idcluster = mIdCluster[i];
            if(idcluster == -10)
                ++(mNbElemCluster[mNbClusters]);
            else
                ++(mNbElemCluster[(unsigned) idcluster]);
        }
        delete [] tmp;
    }

    virtual void calculClusters() = 0;
};

template <class T> 
Clustering<T>::Clustering()
{
    mNbClusters = 0;
    mNuage = NuagePoints<T>();
    mIdCluster = new int[0];
    mNbElemCluster = new size_t[0];
}

template <class T> 
Clustering<T>::Clustering(int nCl, NuagePoints<T>& N): mNbClusters(nCl), mNuage(N)
{
    mIdCluster = new int[mNuage.size()];
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        mIdCluster[i] = -10;
    }
    mNbElemCluster = new size_t[mNbClusters + 1];
    for (auto i = 0l; i <= mNbClusters; ++i)
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
    mNbElemCluster = new size_t[mNbClusters + 1]; 
    for (auto i = 0l; i <= mNbClusters; ++i)
    {
        mNbElemCluster[i] = C.mNbElemCluster[i];
    }
}

template <class T> 
Clustering<T>& Clustering<T>::operator=(const Clustering<T>& C)
{
    this -> mNbClusters = C.mNbClusters;
    this -> mNuage = C.mNuage;
    auto tmp = (this -> mIdCluster);
    this -> mIdCluster = new int[mNuage.size()]; 
    for (auto i = 0u; i < mNuage.size(); ++i)
    {
        this -> mIdCluster[i] = C.mIdCluster[i];
    }
    delete [] tmp;
    auto tmp1 = (this -> mNbElemCluster);
    this -> mNbElemCluster = new size_t[this -> mNbClusters + 1]; 
    for (auto i = 0l; i <= this -> mNbClusters; ++i)
    {
        this -> mNbElemCluster[i] = C.mNbElemCluster[i];
    }
    delete [] tmp1;
    return *this;
}



#endif