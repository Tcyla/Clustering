#include <iostream> // std::cout
#include <valarray> // std::valarray

#include "NuagePoints.hpp"
#include "Clustering.hpp"
#include "KMeans.hpp"
#include "DBSCAN.hpp"

#ifdef __HAS_SCIPLOT__
#include <sciplot/sciplot.hpp>  // plotting utilities

using namespace sciplot;

void draw_clusters()
{
    /*
     *
     */

    
}

#endif


// Génère des nuages de points EXPL1 
// auto nuage1(); 

// Génère des nuages de points EXPL2
// auto nuage2();

int main(int argc, char** argv)
{
    //EXPL1

    //EXPL2



#ifdef __HAS_SCIPLOT__
    std::cout << "has SCIPLOT" << std::endl;
    draw_clusters();
#endif

    return EXIT_SUCCESS;
}