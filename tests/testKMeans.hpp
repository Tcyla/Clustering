#pragma once
#include <gtest/gtest.h>

#include <vector>
#include <valarray>
#include "KMeans.hpp"


/******************************************************
 *                       KMeans                       *
 ******************************************************/

using namespace std;

double Kdist(int a, int b){ return abs(b-a); }

int Ktab1[] = {1, 2, 3, 4, 5, 21, 22, 23, 24, 25};
    
NuagePoints<int> Kn(2, Ktab1, Kdist);


auto tab2 = vector({
                    valarray({2., 1.}), 
                    valarray({1.5, 1.5}),
                    valarray({3., 1.5})
                                        });
NuagePoints<valarray<double>> Kn1(2, tab2.data());


TEST(testKMeans, testAlgo)
{
    KMeans<int> k1(2, Kn);
    for (auto i = 1; i < 5; ++i)
    {
        ASSERT_EQ(k1[i], k1[0]);
        ASSERT_EQ(k1[5+i], k1[5]);
    }
    
    KMeans<valarray<double>> k2(2, Kn1);
    ASSERT_EQ(k2[0], k2[1]);
    ASSERT_NE(k2[2], k2[0]);
    
}
