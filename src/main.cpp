#include <iostream> // std::cout
#include <valarray> // std::valarray
#include <vector> // std::vector
#include <random>

#include "NuagePoints.hpp"
#include "Clustering.hpp"
#include "KMeans.hpp"
#include "DBSCAN.hpp"

#ifdef __USE_SCIPLOT__
#include <sciplot/sciplot.hpp>  // plotting utilities

using namespace sciplot;

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



int main()
{
    size_t dim = 2;
    size_t nbObs = 20; 

    //EXPL1
    auto obs1 = normalDistribution(dim, nbObs, -2, .05);
    NuagePoints<valarray<double>> n1(nbObs, obs1.data());

    auto obs2 = normalDistribution(dim, nbObs, 3, .05);
    NuagePoints<valarray<double>> n2(nbObs, obs2.data());

    

    // if Gnuplot is on the machine using sciplot to plot the clusters 
    #ifdef __USE_SCIPLOT__

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

        // setting win size
        plot.size(600, 400);
        
        // setting XYlabels 
        plot.xlabel("x");
        plot.ylabel("y");

        // Set the x and y ranges
        plot.xrange(-5.0, 6.0);
        plot.yrange(-5.0, 6.0);

        // Set the legend to be on the bottom along the horizontal
        plot.legend()
            .atOutsideBottom()
            .displayHorizontal()
            .displayExpandWidthBy(2);

        // Plot sin(i*x) from i = 1 to i = 6
        plot.drawPoints( obs1x, obs1y ).pointSize(1).label("Cluster 1");
        plot.drawPoints( obs2x, obs2y ).pointSize(1).label("Cluster 2");

        plot.show();

    #endif

    return EXIT_SUCCESS;
}