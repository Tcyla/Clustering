#pragma once
#include <gtest/gtest.h>

#include <vector>
#include <valarray>
#include "DBSCAN.hpp"


/*
 * 
 */


/******************************************************
 *                       DBSCAN                       *
 ******************************************************/

using namespace std;
using darray = valarray<double>;

class testDBSCAN : public ::testing::Test, public DBSCAN<darray>
{
    public:
    NuagePoints<darray> n;
    DBSCAN<darray> db;
    testDBSCAN()
    {
        auto tab = vector({
                            valarray({-1., -1.}), 
                            valarray({1.5, 1.5}), 
                            valarray({1.51, 1.52}), 
                            valarray({1.51, 1.53}),
                            });
        n  = NuagePoints(tab.size(), tab.data());
        db = DBSCAN(1., 3, n);
    }
};

TEST_F(testDBSCAN, testEpsilon)
{
    ASSERT_EQ(db.epsilon(), 1.); 
    db.epsilon(.4);
    ASSERT_EQ(db.epsilon(), .4);
    ASSERT_THROW(db.epsilon(-4), invalid_argument);
}

TEST_F(testDBSCAN, testMinPts)
{
    ASSERT_EQ(db.minPts() ,3);
    db.minPts(7);
    ASSERT_EQ(db.minPts(),7);
    ASSERT_THROW(db.minPts(-4), invalid_argument);
}

TEST_F(testDBSCAN, testCalculCluster)
{
    ASSERT_EQ( db[0], -10  ); // point 0 : bruit
    ASSERT_EQ( db[1],   0  ); // point 1 : cluster 0
    ASSERT_EQ( db[2],   0  ); // point 2 : cluster 0
    ASSERT_EQ( db[3],   0  ); // point 3 : cluster 0
}
