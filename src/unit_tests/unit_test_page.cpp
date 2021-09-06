/*!
 * @file unit_test_page.cpp
 * unit tests for Page class
 * 
 * @author Connor Nolan
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "PageTest"
#include <boost/test/unit_test.hpp>

#include "../Page.h"

using namespace limecell;

BOOST_AUTO_TEST_CASE(cell_data_added)
{
    data::Page p;

    data::Page::statusCode status;

    status = p.setDataAt(0, 0, "first");

    BOOST_CHECK(status == data::Page::statusCode::CELL_DATA_ADDED);
}