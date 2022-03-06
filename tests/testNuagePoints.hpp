#pragma once

#include <gtest/gtest.h>
#include "NuagePoints.hpp"

#include <iostream>
#include <vector>
#include <valarray>

using namespace std;

/******************************************************
 *                    NuagePoints                     *
 ******************************************************/

TEST(testNuagePoints, testDistanceEuclidienne)
{
    ASSERT_DOUBLE_EQ(
        distance_euclidienne(
                              vector({1., 2.}), 
                              vector({2., 1.}) 
                            ), 2.);

    ASSERT_DOUBLE_EQ(
        distance_euclidienne(
                              valarray({1., 2., 1.}), 
                              valarray({2., 1., 12.}) 
                            ), 4.);

    ASSERT_ANY_THROW(
        distance_euclidienne(
                             vector({1., 2.}), 
                             vector({2., 1., 3.}) 
                            )
                                 );

}

TEST(testNuagePoints, test)
{
    
}

TEST(testNuagePoints, testGetDistance)
{  

}


double dist(int a, int b){ return abs(b-a); }

TEST(testNuagePoints, testOperatorPlus)
{
    int tab1[] = {1,2};
    
    NuagePoints<int> n(2, tab1, dist);
    NuagePoints<int> n1(2, tab1, dist);
    auto n2 = n + n1;

    for (auto i = 0u; i < n2.size(); ++i)
    {
        ASSERT_EQ(n2[i], 1 + i%2);
    }

    auto tab2 = vector({valarray({1., 2., 1.}), 
                        valarray({2., 1., 12.}) });
    NuagePoints<valarray<double>> n3(2, tab2.data());
    NuagePoints<valarray<double>> n4(2, tab2.data());
    auto n5 = n3 + n4;
    
    for (auto i = 0u; i < n5.size(); ++i)
    {
        for (auto j = 0u; j < n5[i].size(); ++j)
        {    
            ASSERT_EQ(n5[i][j],  tab2[i%2][j]);
        }
    } 
}

