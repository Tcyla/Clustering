#pragma once
#include <gtest/gtest.h>

#include <vector>
#include <valarray>
#include "KMeans.hpp"


/******************************************************
 *                       KMeans                       *
 ******************************************************/

using namespace std;
using darray = valarray<double>;

class testKMeans : public ::testing::Test
{
public:
    NuagePoints<darray> Kn;
    NuagePoints<darray> Kn1;
    KMeans<darray>K;
    KMeans<darray>K1;
    KMeans<darray>K2;
    
    testKMeans()
    {
        auto tab = vector({
                            valarray({2., 1., 2.}), 
                            valarray({1.5, 1.5, 3.}),
                            valarray({3., 1.5, 4.}), 
                            valarray({-3., .5, 4.}) 
                            });
        auto tab2 = vector({
                            valarray({2., 1.}), 
                            valarray({1.5, 1.5}),
                            valarray({3., 1.5})
                            });
 
        Kn = NuagePoints<darray>(tab2.size(), tab2.data());
        Kn1 = NuagePoints<darray>(tab.size(), tab.data());
        K = KMeans(2, Kn);
        K1 = KMeans(3, Kn1);
        K2 = KMeans(K);
    }
};

/*
 *                   Méthodes héritées
 */

TEST_F(testKMeans, testGetPoint)
{
    ASSERT_DOUBLE_EQ(K.get_point(0)[0], 2.); 
    ASSERT_DOUBLE_EQ(K.get_point(0)[1], 1.); 
    ASSERT_DOUBLE_EQ(K.get_point(1)[0], 1.5); 
    ASSERT_DOUBLE_EQ(K.get_point(1)[1], 1.5); 
    ASSERT_DOUBLE_EQ(K.get_point(2)[0], 3.); 
    ASSERT_DOUBLE_EQ(K.get_point(2)[1], 1.5); 
}

TEST_F(testKMeans, testGetNuageSize)
{

    ASSERT_EQ(K.get_nuage_size(), 3);
    ASSERT_EQ(K1.get_nuage_size(), 4);
}

TEST_F(testKMeans, testGetNbClusters)
{
    ASSERT_EQ(K.get_nbClusters(), 2);
    ASSERT_EQ(K1.get_nbClusters(), 3);
}

TEST_F(testKMeans, testSetNbClusters)
{
    K.set_nbClusters(1);
    ASSERT_EQ(K.get_nbClusters(), 1);
    
    K.set_nbClusters(2);
    ASSERT_EQ(K.get_nbClusters(), 2);
    
    ASSERT_THROW(K.set_nbClusters(10), invalid_argument);
    ASSERT_THROW(K.set_nbClusters(-10), invalid_argument);
}

TEST_F(testKMeans, testGetNbElemCluster)
{
    // ?
}

/*
 *                    Méthodes propres
 */

TEST_F(testKMeans, testConstructors)
{
    
}


TEST_F(testKMeans, testGetCentre)
{
    
}

TEST_F(testKMeans, testGetnIter)
{
    
}

TEST_F(testKMeans, testGetTWCV)
{
    
}


TEST_F(testKMeans, testCalculClusters)
{
    
}
