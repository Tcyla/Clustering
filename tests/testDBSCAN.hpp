#pragma once
#include <gtest/gtest.h>

#include <vector>
#include <valarray>
#include "DBSCAN.hpp"

/******************************************************
 *                       DBSCAN                       *
 ******************************************************/

using namespace std;

double DBdist(int a, int b){ return abs(b-a); }

int DBtab1[] = {1,2};
    
NuagePoints<int> DBn (2, DBtab1, DBdist);
NuagePoints<int> DBn1(2, DBtab1, DBdist);

auto DBtab2 = vector({valarray({1., 2., 1.}), 
                        valarray({2., 1., 12.}) });
NuagePoints<valarray<double>> DBn3(2, DBtab2.data());
NuagePoints<valarray<double>> DBn4(2, DBtab2.data());


TEST(testDBSCAN, test)
{
    
}
