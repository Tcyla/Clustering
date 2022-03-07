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
    KMeans(int, NuagePoints<T>&);
    ~KMeans();

    virtual KMeans<T> operator=(const KMeans<T>&);
    virtual void calculClusters();

    double TWCV(){return mTWCV;}
};

template<class T>
ostream& operator<<(ostream& o, KMeans<T> K)
{
    o << "            KMeans               " << endl;
    
    for (auto i=0u; i < K.get_nbClusters(); ++i)
    {
        o << "Cluster " << i << " : " << endl
          << "( ";
        for(auto j = 0u; j < K.get_nuage().size(); ++j)
        { 
            o << K.get_nuage()[i][j] << " ";
        }
        o << " )" << endl;
    }
    o << "Total Within Cluster Variation = " << K.TWCV();
    
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