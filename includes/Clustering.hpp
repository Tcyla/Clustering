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
    Clustering(int);
    Clustering(const Clustering<T>&);
    ~Clustering();

    int& operator[](size_t i){ return mIdCluster[i]; }
    virtual Clustering<T> operator=(const Clustering<T>&); 

    int  get_nbClusters()     { return mNbClusters; }
    void set_nbClusters(int n){   mNbClusters = n;  }

    NuagePoints<T>   get_nuage()  { return mNuage; } 
    void set_nuage(NuagePoints<T> N) { mNuage = N; }

    virtual void calculClusters() = 0;
};

template <class T> 
Clustering<T>::Clustering()
{

}

template <class T> 
Clustering<T>::Clustering(int)
{

}

template <class T> 
Clustering<T>::Clustering(const Clustering<T>&)
{

}

template <class T> 
Clustering<T>::~Clustering()
{

}

#endif