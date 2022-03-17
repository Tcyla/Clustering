#include <gtest/gtest.h>

#include "testNuagePoints.hpp"
#include "testKMeans.hpp"
#include "testDBSCAN.hpp"



/*
  * Run coverage for: /home/gracques/Projets/Clustering/.build/CMakeFiles/test_clustering.dir/tests
  Command: /usr/bin/gcov -l -o /home/gracques/Projets/Clustering/.build/CMakeFiles/test_clustering.dir/tests /home/gracques/Projets/Clustering/.build/CMakeFiles/test_clustering.dir/tests/tests.cc.gcda
  Output: File '/home/gracques/Projets/Clustering/tests/tests.cc'
    Lines executed:100.00% of 3
    Creating 'tests.cc.gcda##tests.cc.gcov'

    File '/home/gracques/Projets/Clustering/includes/NuagePoints.hpp'
    Lines executed:98.75% of 80
    Creating 'tests.cc.gcda##NuagePoints.hpp.gcov'

    File '/home/gracques/Projets/Clustering/tests/testNuagePoints.hpp'
    Lines executed:100.00% of 46
    Creating 'tests.cc.gcda##testNuagePoints.hpp.gcov'

    File '/home/gracques/Projets/Clustering/tests/testKMeans.hpp'
    Lines executed:100.00% of 42
    Creating 'tests.cc.gcda##testKMeans.hpp.gcov'

    File '/home/gracques/Projets/Clustering/tests/testDBSCAN.hpp'
    Lines executed:0.00% of 8
    Creating 'tests.cc.gcda##testDBSCAN.hpp.gcov'

    File '/home/gracques/Projets/Clustering/includes/DBSCAN.hpp'
    Lines executed:0.00% of 61
    Creating 'tests.cc.gcda##DBSCAN.hpp.gcov'

    File '/home/gracques/Projets/Clustering/includes/KMeans.hpp'
    Lines executed:100.00% of 71
    Creating 'tests.cc.gcda##KMeans.hpp.gcov'

    File '/home/gracques/Projets/Clustering/includes/Clustering.hpp'
    Lines executed:98.53% of 68
    Creating 'tests.cc.gcda##Clustering.hpp.gcov'

    Lines executed:67.10% of 1088
    
    Covered LOC:         356 
    Not covered LOC:     135
    Total LOC:           491 (Gtest compté)
    Percentage Coverage: 72.51%
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
