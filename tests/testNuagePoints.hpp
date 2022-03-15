#pragma once

#include <gtest/gtest.h>
#include "NuagePoints.hpp"

#include <iostream>
#include <vector>
#include <valarray>

using namespace std;
using darray = valarray<double>;
using dvect = vector<double>;

/******************************************************
 *                      Distances                     *
 ******************************************************/


TEST(testNuagePoints, testDistanceEuclidienne)
{
    ASSERT_DOUBLE_EQ(
        distance_euclidienne(
                              vector({1., sqrt(2)+1.}), 
                              vector({sqrt(2)+1., 1.}) 
                            ), 2.);

    ASSERT_DOUBLE_EQ(
        distance_euclidienne(
                              valarray({1., 2., 1.}), 
                              valarray({2., 1., 2.}) 
                            ), sqrt(3.));

    ASSERT_ANY_THROW(
        distance_euclidienne(
                             vector({1., 2.}), 
                             vector({2., 1., 3.}) 
                            )
                                 );

}

TEST(testNuagePoints, testDistanceMinkovski)
{
    double val = distance_minkovsky<dvect, 1>(
                                            vector({1., 1.}), 
                                            vector({1.5, 1.5}) 
                                           );
    EXPECT_DOUBLE_EQ( val, 1. );

    val = distance_minkovsky<darray, 2>(
                                        valarray({1., 2., 1.}), 
                                        valarray({2., 1., 2.})
                                        );
    EXPECT_DOUBLE_EQ( val, sqrt(3.) );

    val = distance_minkovsky<darray, -1>(
                                        valarray({1., 10., 1.}), 
                                        valarray({2., 1., 2.}) 
                                        );
    EXPECT_DOUBLE_EQ( val, 9 );
}

/******************************************************
 *                    NuagePoints                     *
 ******************************************************/

/*
 *                     Constantes
 */

vector tab ({ 
                vector({1., 2.}), 
                vector({2., 1., 3.}) 
            });

NuagePoints n(tab.size(), tab.data()); // should throw !!!

vector tab1({
                valarray({1., 2., 1.}), 
                valarray({2., 1., 2.})
            });
NuagePoints n1(tab1.size(), tab1.data());
vector tab3({
                valarray({1., 2., 1.}), 
                valarray({2., 1., 2.}),
                valarray({1., 2., 1.}), 
                valarray({2., 1., 2.}),
                valarray({1., 2., 1.}), 
                valarray({2., 1., 2.}),
                valarray({1., 2., 1.}), 
                valarray({2., 1., 2.})
            });
NuagePoints n8(tab3.size(), tab3.data());


/*
 *                        Tests
 */

TEST(testNuagePoints, testGetSize)
{
    ASSERT_EQ(n1.size(), 2);
    ASSERT_EQ(n8.size(), 8);
}

TEST(testNuagePoints, testGetDistance)
{  
    ASSERT_DOUBLE_EQ(n.get_distance(vector({ 3., 0.}), 
                                    vector({ 0.,  4.})), 5);
    ASSERT_DOUBLE_EQ(n.get_distance(vector({ 5., 0.}), 
                                    vector({ 0.,  12.})), 13);
}

TEST(testNuagePoints, testSetDistance)
{
    n1.set_distance( distance_minkovsky<darray, 3> );
    
    ASSERT_DOUBLE_EQ(
                     n1.get_distance(valarray({1., 2., 1.}), 
                                    valarray({2., 1., 2.})),
                     powf(3, (double) 1/3)
                    );
}

TEST(testNuagePoints, testOperatorBrakets)
{
    for(unsigned i = 0 ; i < n1.size(); ++i)
    {
        ASSERT_EQ(n1[0][i], valarray({1., 2., 1.})[i]);
        ASSERT_EQ(n1[1][i], valarray({2., 1., 2.})[i]);
    }
    ASSERT_THROW(n1[3], out_of_range);
}

TEST(testNuagePoints, testOperatorPlus)
{
    auto tab2 = vector({valarray({1., 2., 1.}), 
                        valarray({2., 1., 12.}) });
    NuagePoints<darray> n3(2, tab2.data());
    NuagePoints<darray> n4(2, tab2.data());
    auto n5 = n3 + n4;

    for (auto i = 0u; i < n5.size(); ++i)
    {
        for (auto j = 0u; j < n5[i].size(); ++j)
        {    
            ASSERT_EQ(n5[i][j],  tab2[i%2][j]);
        }
    }
}

// test constructors
