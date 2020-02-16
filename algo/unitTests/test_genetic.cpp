//
// Created by Domitille Prevost on 03/02/2020.
//

#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../include/Solution.h"
#include "../include/Genetic.h"
#include "../include/Point.h"
#include <vector>


static const short CAR_SPEED = 15; // in km/h
static const short WALK_SPEED = 5; // in km/h
static const short MIN_CAR_DIST = 1000; // in m
static const Point ORIGIN = Point(0, 0);
static const TimeInterval FULL_DAY = TimeInterval(6 * 60, 20 * 60);
static const Time START_TIME = FULL_DAY.start_time(), END_TIME = FULL_DAY.end_time();

struct GeneticTest : testing::Test
{
    // TreatmentTypes
    TreatmentType flu = TreatmentType(0, 30);
    TreatmentType cancer = TreatmentType(1, 90);
    Inputs inputs1 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);

    Solution sol_3x3_sorted = Solution(3, 3, {0, 1, 2, 3, 4, 5, 6, 7, 8});

    Solution sol_2x2_sorted = Solution(2, 2, {0, 1, 2, 3});

    Solution sol_3x3_random = Solution(3, 3, {1, 4, 6, 2, 0, 3, 5, 7, 8});

    GeneticTest() {
        inputs1.add_type(flu);
        inputs1.add_nurse(Nurse(0));
        inputs1.add_nurse(Nurse(1));
        inputs1.add_patient(Patient(0, Point(0, 0), 0, 0));
        inputs1.add_patient(Patient(1, Point(0, 2000), 1, 0));
        inputs1.add_patient(Patient(2, Point(2000, 2000), 2, 0));
        inputs1.add_patient(Patient(3, Point(2000, 0), 3, 0));
    }
};

void test_generate_population(int pop_size, int nurses, int patients_per_nurse, Genetic gen)
{
    std::vector<Solution> pop = gen.generate_population(pop_size, nurses, patients_per_nurse);

    ASSERT_EQ(pop.size(), pop_size);
    ASSERT_EQ(pop[0].nurses(), nurses);
    ASSERT_EQ(pop[0].patients_per_nurse(), patients_per_nurse);
    std::cout << pop[0].code_to_string() << "..." << std::endl;
    if (pop_size > 1){
        ASSERT_NE(pop[0].code_to_string(), pop[1].code_to_string());
    }

    //Test use of random
    std::vector<Solution> pop2 = gen.generate_population(pop_size, nurses, patients_per_nurse);
    if (pop_size > 1){
        EXPECT_NE(pop[0].code_to_string(), pop2[0].code_to_string());
        //Size matrix and values
        ASSERT_LE(pop[0].get(nurses - 1, patients_per_nurse -1),
                nurses * patients_per_nurse -1);
    }
}

TEST_F(GeneticTest, generate_population){
    Genetic gen(&inputs1);

    test_generate_population(3, 2, 4, gen);
    test_generate_population(8, 10, 10, gen);
    test_generate_population(1, 1, 1, gen);
}

TEST_F(GeneticTest, update_best_solution){
    Genetic gen(&inputs1);

    Solution best_solution(2, 2, {0, 2, 1, 3});
    std::vector<Solution> population;
    population.push_back(sol_2x2_sorted);

    TEST_SET_POPULATION(gen, population);
    TEST_SET_BEST_SOLUTION(gen, best_solution);

    int previous_fitness = Genetic::fitness(best_solution, &inputs1);
    TEST_SET_BEST_FITNESS(gen, previous_fitness);

    gen.update_best_solution();

    ASSERT_NE(gen.best_fitness(), previous_fitness);
}

/*
class MockSolution : public Solution {

    public:
        MockSolution(int nurses, int treatment, std::vector<int> code) :
            Solution{nurses, treatment, code}{}

            MOCK_METHOD(void, mutate, (double rate), ());
};

using testing::_;

TEST_F(GeneticTest, mutation){
    Inputs inputs1 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    Genetic gen(&inputs1, 4);

    MockSolution sol1(2, 2, {0, 2, 1, 3});
    MockSolution sol2(2, 2, {0, 2, 1, 3});

    std::vector<Solution> new_pop = {sol1, sol2, sol2, sol2};
//    EXPECT_CALL(sol1, mutate(testing::Ge(0)));
//    EXPECT_CALL(sol2, mutate(testing::_));
//    sol1.mutate(0.006);
    gen.mutation(new_pop);
}
*/

