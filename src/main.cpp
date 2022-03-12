#include <iostream> // std::cout
#include <valarray> // std::valarray
#include <vector> // std::vector
#include <string> // std::string
#include <random>

#include "NuagePoints.hpp"
#include "Clustering.hpp"
#include "KMeans.hpp"
#include "DBSCAN.hpp"

#ifdef __USE_SCIPLOT__
#include <sciplot/sciplot.hpp>  // plotting utilities

using namespace sciplot;

// ATTENTION SEULEMENT EN 2D!

template<class T>
auto plot_clusters(Clustering<T>& C)
{
    auto nbClusters = C.get_nbClusters();
    bool hasNoCluster = false;
    std::vector<std::vector<double>> Xs(nbClusters + 1);
    std::vector<std::vector<double>> Ys(nbClusters + 1);
    
    int idCluster;
    for(auto i = 0u; i < C.get_nuage().size(); ++i)
    {
        idCluster = C[i];
        if (idCluster != -10)
        {
            Xs[idCluster].push_back( (C.get_nuage())[i][0] );
            Ys[idCluster].push_back( (C.get_nuage())[i][1] );
        }
        else
        {
            if (!hasNoCluster)
                hasNoCluster = true;

            Xs[nbClusters].push_back( (C.get_nuage())[i][0] );
            Ys[nbClusters].push_back( (C.get_nuage())[i][1] );
        }
    }

    // creating a new plot object
    Plot plot; 

    // Set the legend to be on the bottom along the horizontal
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    //
    std::string str("Cluster ");
    for (auto i = 0u; i < nbClusters; ++i)
    {
        plot.drawPoints( Xs[i], Ys[i] ).pointSize(1).label(str + std::to_string(i));
    }

    if (hasNoCluster)
        plot.drawPoints( Xs[nbClusters], Ys[nbClusters] ).pointSize(1).label("Bruit");

    return plot;
}

template<class T>
auto plot_clusters(int nbObs, T obs1, T obs2)
{
    // spliting Xs and Ys into 2 different array
    std::valarray<double> obs1x(nbObs);
    std::valarray<double> obs1y(nbObs);
    for (size_t i = 0; i < nbObs; ++i)
    {
        obs1x[i] = obs1[i][0];
        obs1y[i] = obs1[i][1];
    }

    std::valarray<double> obs2x(nbObs);
    std::valarray<double> obs2y(nbObs);
    for (size_t i = 0; i < nbObs; ++i)
    {
        obs2x[i] = obs2[i][0];
        obs2y[i] = obs2[i][1];
    }

    // creating a new plot object
    Plot plot; 

    // Set the legend to be on the bottom along the horizontal
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    // 
    plot.drawPoints( obs1x, obs1y ).pointSize(1).label("Cluster 1");
    plot.drawPoints( obs2x, obs2y ).pointSize(1).label("Cluster 2");

    return plot;
}



#endif


auto normalDistribution(size_t dim, size_t nbObs, double moy, double var)
{
    std::vector<std::valarray<double>> res;
    std::valarray<double> pt(dim);

    std::random_device rd{};
    std::normal_distribution<double> dist(moy, std::sqrt(var));
    
    for (size_t i = 0; i < nbObs; ++i)
    {
       for(size_t j = 0; j < dim; ++j)
       {
           pt[j] = dist(rd);
       }
       res.push_back(pt);
    }

    return res; 
}

auto cercleBruit(size_t nbObs, double rayon, double var)
{
    std::vector<std::valarray<double>> res;
    std::valarray<double> pt(2);

    std::random_device rd{};
    std::normal_distribution<double> dist(0, std::sqrt(var));
    
    for (size_t i = 0; i < nbObs; ++i)
    {
       pt[0] = rayon * cos(2*M_PI * i / nbObs) + dist(rd);
       pt[1] = rayon * sin(2*M_PI * i / nbObs) + dist(rd);
       res.push_back(pt);
    }

    return res; 
}

int main()
{
    size_t dim = 2;
    size_t nbObs = 10; 

    // EXPL1
    //          Setups 
    
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
              << "$                  EXEMPLE 1                $\n"
              << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
              << std::endl;
    
    auto obs1 = normalDistribution(dim, nbObs, -1, .05);
    NuagePoints<valarray<double>> n1(nbObs, obs1.data());

    auto obs2 = normalDistribution(dim, nbObs, 1, .05);
    NuagePoints<valarray<double>> n2(nbObs, obs2.data());

    auto n3 = n1 + n2;

    //          Kmeans
    KMeans k(2,n3);
    std::cout << k << std::endl;

    //          DBCAN
    DBSCAN d(.5, 3, n3);
    std::cout << d;
    
    // EXPL2
    //          Setups
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
              << "$                  EXEMPLE 2                $\n"
              << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
              << std::endl;
    
    auto obs4 = cercleBruit(nbObs, 2., .03);
    NuagePoints<valarray<double>> n4(nbObs, obs4.data());

    auto obs5 = cercleBruit(nbObs, .5, .03);    
    NuagePoints<valarray<double>> n5(nbObs, obs5.data());

    auto n6 = n4 + n5;
    
    //          Kmeans
    KMeans k1(2,n6);
    std::cout << k1;

    //          DBSCAN

    DBSCAN d1(.7, 3, n6);
    std::cout << d1;

    // if Gnuplot is on the machine using sciplot to plot the clusters 
    #ifdef __USE_SCIPLOT__

        // creating a new plot object
        Plot plotk = plot_clusters(k);
        Plot plotk1 = plot_clusters(k1);

        // Set the x and y ranges
        plotk.xrange(-5.0, 6.0);
        plotk.yrange(-5.0, 6.0);
        
        // Set the x and y ranges
        plotk1.xrange(-3, 3);
        plotk1.yrange(-3, 3);


        // creating a new plot object
        Plot plotd = plot_clusters(d);
        Plot plotd1 = plot_clusters(d1);

        // Set the x and y ranges
        plotd.xrange(-5.0, 6.0);
        plotd.yrange(-5.0, 6.0);
        
        // Set the x and y ranges
        plotd1.xrange(-3, 3);
        plotd1.yrange(-3, 3);

        // //
        // plotk.xlabel("Kmeans");
        // plotk.ylabel("Exemple 1");
        // plotk1.ylabel("Exemple 2");
        // plotd.xlabel("DBSCAN");

        Figure fig = {
                      {plotk, plotd}, 
                      {plotk1, plotd1}
                              };
        
        fig.size(600, 600);
        fig.palette("matlab");
        fig.show();
        fig.save("../result.png");
        

    #endif

    return EXIT_SUCCESS;
}