#ifndef __KMEANS__
#define __KMEANS__

#include "Clustering.hpp"

template <class T>
class KMeans : public Clustering<T>
{
private:
    /* data */
public:
    KMeans(/* args */);
    ~KMeans();
};

template<class T>
KMeans<T>::KMeans(/* args */)
{
}

template<class T>
KMeans<T>::~KMeans()
{
}


#endif