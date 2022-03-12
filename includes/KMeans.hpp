#ifndef __KMEANS__
#define __KMEANS__

#include <iostream>
#include <random>
#include <ctime>
#include <type_traits>

#include "Clustering.hpp"


using namespace std;

template <class T>
class KMeans : public Clustering<T>
{
private:
    int mNIter = 0;
    double mTWCV = -10; // Total Within Cluster Variation
    T* mTabCentre;

    // fonction outils
    void assign2Cluster();
    void initClusters(); 
    void calculCentre();

public:
    KMeans();
    KMeans(int, NuagePoints<T>&);
    KMeans(const KMeans<T>&);
    virtual ~KMeans();

    virtual KMeans<T>& operator=(const KMeans<T>&);
    virtual void calculClusters();

    T get_Centre(size_t i){ return mTabCentre[i]; }
    int get_mNIter(){ return mNIter; }
    double TWCV(){return mTWCV;}
};

template<class T>
ostream& operator<<(ostream& o, KMeans<T> K)
{
    T tmpPoint;
    o << "---------------------------------------------" << endl
      << "------            KMeans               ------" << endl
      << "Nombre de point à classer : " 
      << K.get_nuage().size() << endl
      << "Nombre de Cluster : " 
      << K.get_nbClusters() << endl;
    
    for (auto i=0l; (unsigned) i < K.get_nbClusters(); ++i)
    {
        o << "Cluster " << i << " : " << endl
          << "      ";
        for(auto j = 0u; j < K.get_nuage().size(); ++j)
        {
            if (K[j]==i)
            {
                tmpPoint = K.get_nuage()[j];
                o << "( ";
                for (auto it = begin(tmpPoint); it != end(tmpPoint); ++it)
                {
                    o << *it << " ";
                }
                o << ")"
                  << endl 
                  << "      ";
            }
        }
        o << "Nombre d'éléments : " << K.get_nbElemCluster(i) <<endl;
    }
    o << "Centres : " << endl
      << "      ";
    for (auto i=0u; i < K.get_nbClusters(); ++i)
    {
        o << "Cluster " << i << " : ";
        tmpPoint = K.get_Centre(i);
        o << "( ";
        for (auto it = begin(tmpPoint); it != end(tmpPoint); ++it)
        {
            o << *it << " ";
        }
        o << ")" <<  endl << "      ";
    }

    o << endl
      << "Number of iteration = " << K.get_mNIter()
      << endl
      << "Total Within Cluster Variation = " << K.TWCV() 
      << endl
      << "---------------------------------------------"
      << endl;
    
    return o;
}


/*********************************************************************
 *                             Constructors                          *
 *********************************************************************/

template<class T>
KMeans<T>::KMeans()
{
    mTabCentre = new T[0];
}

template<class T>
KMeans<T>::KMeans(int n, NuagePoints<T>& P) : Clustering<T>(n, P)
{
    mTabCentre = new T[this -> mNbClusters];
    calculClusters();
}

template<class T>
KMeans<T>::KMeans(const KMeans<T>& K) : Clustering<T>(K), mNIter(K.mNIter), mTWCV(K.mTWCV)
{
    mTabCentre = new T[K.mNbClusters];
    for (auto i = 0u; i < K.mNbClusters; ++i)
    {
        mTabCentre[i] = K.mTabCentre[i];
    }
}

template<class T>
KMeans<T>::~KMeans()
{
    delete [] mTabCentre;
}

template<class T>
KMeans<T>& KMeans<T>::operator=(const KMeans<T>& K)
{
    this -> Clustering<T>::operator=(K);
    auto tmp = this -> mTabCentre;
    this -> mTabCentre = new T[K.mNbClusters];
    for (auto i = 0u; i < K.mNbClusters; ++i)
    {
        this -> mTabCentre[i] = K.mTabCentre[i];
    }
    delete [] tmp;
    return *this;
}


/*********************************************************************
 *                       Implementation KMeans                       *
 *********************************************************************/


template<class T>
void KMeans<T>::assign2Cluster()
{
    mTWCV = 0; 
    size_t argmin;
    double min;
    double tmp;
    //Initialise le Nb d'éléments de chaque cluster
    for ( auto i = 0u; i < this->mNbClusters; ++i )
    {
        this->mNbElemCluster[i] = 0;
    }

    // Pour tous les points assigne au le points au cluster minimisant
    // la distance entre le point et le centre du cluster.
    // Ces distances minimales sont sommées pour obtenir la variation 
    // total inter-cluster (TWCV). 
    for ( auto i = 0u; i < this->mNuage.size(); ++i )
    {
        argmin = 0;
        min = this->mNuage.get_distance(mTabCentre[0], this->mNuage[i]);  
        for (auto j = 1u; j < this->mNbClusters; ++j)
        {
            tmp = this->mNuage.get_distance(mTabCentre[j], this->mNuage[i]);
            if (min > tmp)
            {
                argmin = j; 
                min = tmp;
            }
        }
        mTWCV += min; // ajoute le min à TWCV
        // incrémente le nombre d'éléments dans le cluster 
        ++(this->mNbElemCluster[argmin]); 
        // assigne la observation au cluster minimisant la distance
        this->mIdCluster[i] = argmin;        
    }
}

template<class T>
void KMeans<T>::initClusters()
{
    /* Initialise les centre des clusters avec des points aléatoirement tiré */
    srand(time(0));
    auto i=0u;
    size_t randId;
    while(i < this->mNbClusters)
    {
        /* 
         * On Simule un tirage sans remise par des tirages avec remise : 
         *
         * 1. On tire un point au hasard.
         * 2. Si l'observation n'a pas déjà été tirée on la choisit,
         *    sinon retour à l'étape 1.
         * Cet algorithme converge d'autant plus rapidement que le nombre 
         * de clusters est petit par rapport au nombre d'observations.
         * 
         */
        randId = rand() % this->mNuage.size();
        if (this->mIdCluster[randId] == -10)
        {
            this -> mIdCluster[randId] = i;
            this -> mTabCentre[i] = this->mNuage[randId];
            this -> mNbElemCluster[i] = 1; 
            ++i;
        }
    }
}

template<class T>
void KMeans<T>::calculCentre()
{
   
    // Initialise tous les centres à l'origine
    for (auto i = 0u; i < this -> mNbClusters; ++i)
    {
        for(auto it = begin(this -> mTabCentre[i]); it != end(this -> mTabCentre[i]); ++it)
        {
            *it = 0;
        }
    }
    
    //
    for (auto i = 0u; i < this->mNuage.size(); ++i)
    {
        mTabCentre[this -> mIdCluster[i]] += this -> mNuage[i]; // ! FIXME : only works with valarrays
    }

    // Initialise tous les centres à l'origine
    for (auto i = 0u; i < this -> mNbClusters; ++i)
    {
        for(auto it = begin(this -> mTabCentre[i]); it != end(this -> mTabCentre[i]); ++it)
        {
            *it /= this -> mNbElemCluster[i];
        }
    }

}

template<class T>
void KMeans<T>::calculClusters()
{
    mNIter = 0;
    initClusters();
    assign2Cluster();
    auto tmp = mTWCV + 1;
    while (mTWCV < tmp && mNIter<100)
    {
        tmp = mTWCV;
        calculCentre();
        assign2Cluster();
        ++mNIter;
    }
    
}

#endif