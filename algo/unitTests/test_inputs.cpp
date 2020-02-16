//
// Created by Domitille Prevost on 03/02/2020.
//

#include <gtest/gtest.h> // googletest header file
#include "../include/Inputs.h"
#include "../include/TreatmentType.h"
#include "../include/Nurse.h"
#include "../include/Patient.h"
#include "../include/TimeInterval.h"
#include "../include/Treatment.h"


Patient *PatientFactory(int number_treatments, int pos_x, int pos_y){

    Treatment treatment = Treatment(0, 0, TimeInterval(0, 0));
    std::vector<Treatment> treatmentVect;

    if (number_treatments >= 0) {
        for (int i = 0; i < number_treatments; i++) {
            treatmentVect.push_back(treatment);
        }
    }

    Patient *patient = new Patient(0, Point(pos_x, pos_y), treatmentVect);
    return patient;
}

struct inputsFixtures : testing::Test{
    Inputs *inputs_empty;
    Inputs *inputs;

    std::vector<TreatmentType> typesVect = {TreatmentType(0, 0)};
    std::vector<Nurse> nursesVect = {Nurse(3, 0), Nurse(0)};

    Patient *patient1 = PatientFactory(1, 0, 0);
    Patient *patient2 = PatientFactory(2, 0, 0);
    Patient *patient3 = PatientFactory(2, 1, 0);

    std::vector<Patient> patientsVect = {*patient2, *patient1, *patient3};

    inputsFixtures()  {
        inputs_empty = new Inputs(13, 2, 20);
        inputs = new Inputs(13, 2, 0, typesVect, nursesVect, patientsVect);
    }

    ~inputsFixtures(){
        delete inputs_empty;
        delete patient1;
        delete patient2;
        delete patient3;
    }
};

TEST_F(inputsFixtures, constructor_and_print){
    std::string output_empty = "*** Consts ***\nCar speed: 13\nWalk"
                               " speed: 2\nMin car speed: 20\n\n"
                               "*** 0 Treatment type(s) ***\n\n"
                               "*** 0 Nurse(s) ***\n\n"
                               "*** 0 Patient(s) ***";

    EXPECT_EQ(inputs_empty->to_string(), output_empty);
}


TEST_F(inputsFixtures, treatments_list){
    EXPECT_EQ(inputs->treatments_size(), 5);
    EXPECT_EQ(inputs->patients_per_nurse(), 2);
    EXPECT_EQ(inputs->treatments_left(), 5);

    inputs->add_patient(*patient3);
    EXPECT_EQ(inputs->treatments_size(), 7);
    EXPECT_EQ(inputs->patients_per_nurse(), 3);
}

TEST_F(inputsFixtures, get_patient){
    ASSERT_NE(inputs->get_patient(0), nullptr);
    ASSERT_EQ(inputs->get_patient(5), nullptr);
    ASSERT_EQ(inputs_empty->get_patient(0), nullptr);
}

TEST_F(inputsFixtures, get_nurse){
    ASSERT_NE(inputs->get_nurse(0), nullptr);
    ASSERT_EQ(inputs->get_nurse(10), nullptr);

    ASSERT_EQ(inputs_empty->get_nurse(0), nullptr);
}


TEST_F(inputsFixtures, reset){
    inputs_empty->reset();
    inputs->reset();
}


TEST_F(inputsFixtures, getters){
    EXPECT_EQ(inputs_empty->car_speed(), 13);
    EXPECT_EQ(inputs_empty->walk_speed(), 2);
    EXPECT_EQ(inputs_empty->min_car_dist(), 20);

    EXPECT_EQ(inputs_empty->treatments_size(), 0);
    EXPECT_EQ(inputs_empty->patients_per_nurse(), 0);
    EXPECT_EQ(inputs_empty->treatments_left(), 0);
}

TEST_F(inputsFixtures, add_treatment){
    EXPECT_EQ(inputs_empty->types_size(), 0);

    inputs_empty->add_type(TreatmentType(0, 0));

    EXPECT_EQ(inputs_empty->types_size(), 1);
    EXPECT_EQ(inputs_empty->types(), typesVect);
    EXPECT_EQ(*inputs_empty->get_type_by_index(0), typesVect[0]);
}


TEST_F(inputsFixtures, add_nurse){
    EXPECT_EQ(inputs_empty->nurses_size(), 0);

    inputs_empty->add_nurse(Nurse(0, 0));
    inputs_empty->add_nurse(Nurse(0, 1));

    EXPECT_EQ(inputs_empty->nurses_size(), 2);
}