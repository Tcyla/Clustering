#ifndef __KMEANS__
#define __KMEANS__

#include<iostream>
#include "Clustering.hpp"

template <class T>
class KMeans : public Clustering<T>
{
private:
    T* mTabCentre;
    int mNIter;
    double mTWCV = nan; // Total Within Cluster Variation

    // fonction outils
    void initClusters(); 
    void calculCentroid();

public:
    KMeans();
    ~KMeans();

    virtual KMeans<T> operator=(const KMeans<T>&);
    virtual void calculClusters();

    double TWCV(){return mTWCV;}
};

template<class T>
ostream& operator<<(ostream& o, KMeans<T> K)
{
    o << "            KMeans               " << endl
      /* 
                (repeat for each Cluster)
      << "Cluster " << i << " : " << endl; 
                (points du cluster)
      */
      << "Total Within Cluster Variation = " << K.TWCV();
    
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