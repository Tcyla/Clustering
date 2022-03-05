#ifndef __DBSCAN__
#define __DBSCAN__

#include "Clustering.hpp"

template <class T>
class DBSCAN : public Clustering<T>
{
private:
    /* data */
public:
    DBSCAN(/* args */);
    ~DBSCAN();
};

template<class T>
DBSCAN<T>::DBSCAN(/* args */)
{
}

template<class T>
DBSCAN<T>::~DBSCAN()
{
}


#endif