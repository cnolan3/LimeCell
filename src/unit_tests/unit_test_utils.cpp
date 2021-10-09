/*!
 * @file unit_test_utils.cpp
 * unit tests for utility functions
 * 
 * @author Connor Nolan
 */
#include <boost/test/unit_test.hpp>

#include "../utils.h"

BOOST_AUTO_TEST_CASE(getArrayXY_single_row_success)
{
    int* arr = new int[5]{ 0, 1, 2, 3, 4 };

    int num = getArrayXY<int>(arr, 5, 2, 0, 5);

    BOOST_CHECK(num == 2);
}

BOOST_AUTO_TEST_CASE(getArrayXY_multiple_row_success)
{
    /* 3x3 array
     * 0, 1, 2
     * 3, 4, 5
     * 6, 7, 8
     */
    int* arr = new int[9]{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    int num = getArrayXY<int>(arr, 9, 1, 1, 3);

    BOOST_CHECK(num == 4);
}

BOOST_AUTO_TEST_CASE(getArrayXY_out_of_bounds_exception)
{
    int* arr = new int[5]{ 0, 1, 2, 3, 4 };

    // position (6, 0) is outside of the array
    BOOST_CHECK_THROW(getArrayXY<int>(arr, 5, 6, 0, 5), std::out_of_range);
}