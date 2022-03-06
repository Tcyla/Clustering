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
