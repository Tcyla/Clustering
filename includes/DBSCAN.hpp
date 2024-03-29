#ifndef __DBSCAN__
#define __DBSCAN__

#include "Clustering.hpp"

#include <vector>

#define BREAK() {std::cout << "in " << __FILE__ << " : " << __FUNCTION__ << " (line " << __LINE__ + 1 << ")\n";}

using namespace std;

template <class T>
class DBSCAN : public Clustering<T>
{
private:
    double mEps;
    unsigned mMinPts;
    bool* mIsPtVisT;

    vector<int> calculVoisinage(T);
    bool etendCluster(unsigned, int, vector<int>&);

public:
    DBSCAN();
    DBSCAN(const DBSCAN<T>&);
    DBSCAN(double, unsigned, NuagePoints<T>&);
    DBSCAN(NuagePoints<T>&);
    ~DBSCAN();

    auto minPts() const { return mMinPts; }
    void minPts(unsigned m){ mMinPts = m; }
    void minPts(int m)
    { 
        if (m >= 0)
            mMinPts = m;
        else
            throw invalid_argument("minPts should be positive");
    }

    auto epsilon() const { return mEps; }
    void epsilon(double eps)
    { 
        if (eps > 0) 
            mEps = eps;
        else
            throw invalid_argument("eps should be strictly positive");
    }
    
    virtual DBSCAN& operator=(const DBSCAN<T>&);

    virtual void calculClusters();
};

template<class T>
ostream& operator<<(ostream& o, const DBSCAN<T>& D)
{
    T tmpPoint;
    o << "---------------------------------------------" << endl
      << "------            DBSCAN               ------" << endl
      << "Nombre de point à classer : " 
      << D.get_nuage_size() << endl
      << "MinPts : " 
      << D.minPts() << endl
      << "Epsilon : " 
      << D.epsilon() << endl;
    
    for (auto i=0l; (unsigned) i < D.get_nbClusters(); ++i)
    {
        o << "Cluster " << i << " : " << endl
          << "      ";
        for(auto j = 0u; j < D.get_nuage_size(); ++j)
        {
            if (D.get_idCluster(j)==i)
            {
                tmpPoint = D.get_point(j);
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
        o << "Nombre d'éléments : " << D.get_nbElemCluster(i) <<endl;
    }
    o << "\nBruit : " << endl
      << "      ";
    for(auto j = 0u; j < D.get_nuage_size(); ++j)
    {
        if (D.get_idCluster(j)==-10)
        {
            tmpPoint = D.get_point(j);
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
    o << "Nombre d'éléments : " << D.get_nbElemCluster(D.get_nbClusters()) <<endl;

    o << endl
      << "---------------------------------------------"
      << endl;
    
    return o;
}


template<class T>
DBSCAN<T>::DBSCAN(): Clustering<T>(), mEps(1), mMinPts(1)
{
    mIsPtVisT= new bool[0];
}

template<class T>
DBSCAN<T>::DBSCAN(const DBSCAN<T>& D): Clustering<T>(D), mEps(D.mEps), mMinPts(D.mMinPts)
{
    mIsPtVisT = new bool[D.get_nuage_size()];
    for (auto i = 0u ; D.get_nuage_size() ; ++i)
    {
        mIsPtVisT[i] = D.mIsPtVisT[i];
    }
}

template<class T>
DBSCAN<T>::DBSCAN(double eps, unsigned npt, NuagePoints<T>& N) : Clustering<T>(0, N), mEps(eps), mMinPts(npt)
{  
    mIsPtVisT = new bool[N.size()];
    for(auto i = 0u ; i < N.size(); ++i)
    {
        mIsPtVisT[i]= false;
    }
    calculClusters();
}

template<class T>
DBSCAN<T>::~DBSCAN()
{
    delete [] mIsPtVisT;
}

template<class T>
DBSCAN<T>& DBSCAN<T>::operator=(const DBSCAN<T>& D)
{
    this -> Clustering<T>::operator=(D);
    this -> mEps = D.mEps;
    this -> mMinPts = D.mMinPts;
    auto tmp = this -> mIsPtVisT;
    this -> mIsPtVisT = new bool[D.get_nuage_size()];
    for (auto i = 0u ; i < D.get_nuage_size() ; ++i)
    {
        mIsPtVisT[i] = D.mIsPtVisT[i];
    }
    delete [] tmp;
    return *this;
}

template<class T>
vector<int> DBSCAN<T>::calculVoisinage(T p)
{
    /*
     * Def 1:
     * On dit qu'un point q appartient au epsilon-voisinage 
     * d'un point p ssi dist(p,q) <= epsilon
     * (Ester 1996 voir Readme.md)
     * 
     * [Ester96] propose une amélioration O(log(n)) en utilisant un R*-arbre.
     * 
     * 
     * Complexité : O(n)
     */

    vector<int> voisinage;
    double dist; 
    for (auto i = 0u ; i < (this -> mNuage.size()) ; ++i)
    {
        // distance de p au ieme point
        dist = this -> mNuage.get_distance(this -> mNuage[i], p);

        // si distance inférieure à epsilon ajoute i au voisinage
        if ( dist < mEps )
            voisinage.push_back(i); 
    }
    return voisinage;
}

template<class T>
bool DBSCAN<T>::etendCluster(const unsigned idPt , const int numCluster, vector<int>& vois)
{
    /* 
     *  
     *
     */

    bool res;
    vector<int> tmpVois;

    // On marque le point comme visité
    this -> mIsPtVisT[idPt] = true;
    
    if (vois.size() < mMinPts) // Le point n'est pas un point centrale
    {
        this -> mIdCluster[idPt] = -10;
        res = false;
    }
    else // tous les points de vois sont atteignable par densité
    {
        this -> mIdCluster[idPt] = numCluster;
        // Pour chaque point du voisinage
        size_t count = 0;
        while ( count < vois.size() )
        {
            if (!mIsPtVisT[vois[count]]) // si le point n'a pas été visité
            {
                // on marque le point du voisinage comme visité
                mIsPtVisT[vois[count]] = true;
                // calcul le voisinage du point
                tmpVois = calculVoisinage(this -> mNuage[vois[count]]);
                if (tmpVois.size() >= mMinPts) // tmpVois est suffisament 
                {                              // grand pour être un cluster,
                                               // alors on fusionne les clusters
                    vois.insert(vois.end(), tmpVois.begin(), tmpVois.end());
                }
            }
            if ( this -> mIdCluster[vois[count]] == -10 ) // si le point du 
            {                                      // voisinage n'appartient  
                                                   // à aucun cluster
                //on ajoute le point au cluster
                this -> mIdCluster[vois[count]] = numCluster;
            }
            ++count;
        }
        res = true; 
    }
    return res;

}

template<class T>
void DBSCAN<T>::calculClusters()
{
    vector<int> vois;
    size_t cluster = 0;
    for (auto i = 0u ; i < (this -> mNuage.size()) ; ++i)
    {
        if (!mIsPtVisT[i])
        {           
            vois = calculVoisinage( this -> mNuage[i] );
            if (etendCluster(i, cluster, vois))
            {
                ++cluster;
            }
        }
    }
    this -> set_nbClusters(cluster); 
    this -> computeNbElemCluster(); 
}

#endif