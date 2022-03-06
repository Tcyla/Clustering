#ifndef __KMEANS__
#define __KMEANS__

#include<iostream>
#include "Clustering.hpp"

template <class T>
class KMeans : public Clustering<T>
{
private:
    T mTabCentre;
    int mNIter;

    // fonction outils
    void initClusters(); 
    void calculCentroid();

public:
    KMeans();
    ~KMeans();

    virtual KMeans<T> operator=(const KMeans<T>&);
    virtual void calculClusters();
};

template<class T>
ostream& operator<<(ostream& o, KMeans<T> k)
{
    return o; 
}

template<class T>
KMeans<T>::KMeans()
{
}

template<class T>
KMeans<T>::~KMeans()
{
}

// Algorithme KMeans
template<class T>
void KMeans<T>::initClusters()
{

} 

template<class T>
void KMeans<T>::calculCentroid()
{

}

template<class T>
void KMeans<T>::calculClusters()
{
    
}


#endif