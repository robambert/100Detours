//
// Created by Domitille Prevost on 03/02/2020.
//
#include <gtest/gtest.h>
#include "../include/Solution.h"
#include "../include/Utils.h"
#include "../include/Genetic.h"
#include "../include/Inputs.h"
#include <iostream>

class testSolution : public testing::Test{
    public:
        Solution solution = Solution(2, 2, {0, 1, 2, 3});
        Solution solution3 = Solution(3, 4, {0, 1, 2, 3, 4, 5, 6, 7, 8});


    public : testSolution(){
        solution.fitness(0, 1);
        solution.fitness(1, 1);
    }
};


void tester_serial_walk(std::vector<int> array, int dist1, int dist2, Solution solution1){
    TEST_SET_DISTANCES(solution1, array);
    EXPECT_EQ(solution1.longest_serial_walk_distance(0).first, dist1);
    EXPECT_EQ(solution1.longest_serial_walk_distance(0).second, dist2);
}


TEST_F(testSolution, longest_serial_walk_distance){
    Solution solution1 = Solution(1, 5, {0, 1, 2, 3, 4});

    tester_serial_walk({0, 0, 0, 0}, 0, 5, solution1);
    tester_serial_walk({0, 1, 1, 1}, 0, 2, solution1);
    tester_serial_walk({0, 1, 0, 0}, 2, 5, solution1);
    tester_serial_walk({1, 1, 1, 1}, 0, 1, solution1);

    Solution solution2 = Solution(1, 2, {1, 2});
    tester_serial_walk({0}, 0, 2, solution2);
}


TEST_F(testSolution, longest_serial_walk){

    std::pair<int, int> point_0 = solution.longest_serial_walk_distance(0);
    std::pair<int, int> point_1 = solution.longest_serial_walk_distance(1);

    ASSERT_EQ(point_0.first, 0) << "Start point nurse 0";
    ASSERT_EQ(point_0.second, 2) << "End point nurse 0";
    ASSERT_EQ(point_1.first, 0) << "End point nurse 1";
    ASSERT_EQ(point_1.second, 2) << "End point nurse 1";
}


TEST_F(testSolution, constructor_crossing_point){
    Solution solution_parent = Solution(2, 3, {6, 1, 2, 3, 4, 5});

    Solution solution_child = Solution(solution_parent, {1, 0}, {3, 1}, true);
    EXPECT_EQ(solution_child.get(0, 0), 0);
    EXPECT_EQ(solution_child.get(0, 1), 1);
    EXPECT_EQ(solution_child.get(0, 2), 2);
    EXPECT_EQ(solution_child.get(1, 0), 3);
    EXPECT_EQ(solution_child.get(1, 1), 0);
    EXPECT_EQ(solution_child.get(1, 2), 0);
}


TEST_F(testSolution, mutate){
    srand(9);

    // Utilise pour prevoir le fonctionnement de la fonction
    // random avec le seed a 9.


    //    std::cout << (random01() < 0.5) << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << (random01() < 0.5) << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << (random01() < 0.5) << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << (random01() < 0.5) << std::endl;
    //    std::cout << random(0, 1)  << std::endl;
    //    std::cout << random(0, 1)  << std::endl;

    int sol00 = solution.get(0, 0);
    int sol01 = solution.get(0, 1);
    int sol10 = solution.get(1, 0);
    int sol11 = solution.get(1, 1);

    EXPECT_NE(solution.fitness(0), -1);

    solution.mutate(0.5);

    EXPECT_EQ(sol01, solution.get(0, 0));
    EXPECT_EQ(sol00, solution.get(1, 0));
    EXPECT_EQ(sol10, solution.get(0, 1));
    EXPECT_EQ(sol11, solution.get(1, 1));
    EXPECT_EQ(solution.fitness(0), -1) << "Fitness nurse 0 not reset to -1";
    EXPECT_EQ(solution.fitness(1), -1) << "Fitness nurse 1 not reset to -1";
}


TEST_F(testSolution, mutate_statistic){

    int i00[4]= {0,0,0,0};
    int i01[4]= {0,0,0,0};
    int i10[4]= {0,0,0,0};
    int i11[4]= {0,0,0,0};

    for (int j = 0; j < 10000; j++){
        solution.mutate(0.5);
        i00[solution.get(0, 0)] += 1;
        i01[solution.get(1, 0)] += 1;
        i10[solution.get(0, 1)] += 1;
        i11[solution.get(1, 1)] += 1;
    }
    for (int i = 0; i < 4; i++){
        ASSERT_TRUE(2450 < i00[i]);
        ASSERT_TRUE(i00[i] < 2550);
    }
}


TEST_F(testSolution, fitness){
    ASSERT_EQ(solution.fitness(), 2);

    solution.fitness(1, -1);
    ASSERT_EQ(solution.fitness(), -1);
}
