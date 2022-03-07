#include <gtest/gtest.h>

#include "testNuagePoints.hpp"
#include "testKMeans.hpp"
#include "testDBSCAN.hpp"


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
