//
// Created by Domitille Prevost on 02/02/2020.
//

#include <gtest/gtest.h>
#include "../include/Point.h"
#include "../include/TimeInterval.h"

static const Point ORIGIN = Point(0, 0);
static const TimeInterval FULL_DAY = TimeInterval(6 * 60, 20 * 60);
/*
int main(int argc, char **argv) {
    Point::SET_ORIGIN(ORIGIN);
    TimeInterval::SET_FULL_DAY(FULL_DAY);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/