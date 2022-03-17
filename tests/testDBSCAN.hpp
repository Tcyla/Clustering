#pragma once
#include <gtest/gtest.h>

#include <vector>
#include <valarray>
#include "DBSCAN.hpp"


/******************************************************
 *                       DBSCAN                       *
 ******************************************************/

using namespace std;
using darray = valarray<double>;

class testDBSCAN : public ::testing::Test, public DBSCAN<darray>
{
    public:
    DBSCAN<darray> db;
    testDBSCAN()
    {
        auto tab = vector({
                            valarray({-1., -1.}), 
                            valarray({1.5, 1.5}), 
                            valarray({1.51, 1.52}), 
                            valarray({1.51, 1.53}),
                            });
        NuagePoints<darray> n(tab.size(), tab.data());
        db = DBSCAN<darray>(1., 3, n);
    }
};

TEST_F(testDBSCAN, testCalculClusters)
{
    
}
