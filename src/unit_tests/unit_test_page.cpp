/*!
 * @file unit_test_page.cpp
 * unit tests for Page class
 * 
 * @author Connor Nolan
 */
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

BOOST_AUTO_TEST_CASE(cell_data_deleted)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    status = p.setDataAt(0, 0, "");

    BOOST_CHECK(status == data::Page::statusCode::CELL_DATA_DELETED);
}

BOOST_AUTO_TEST_CASE(cell_data_replaced)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    status = p.setDataAt(0, 0, "second");

    BOOST_CHECK(status == data::Page::statusCode::CELL_DATA_REPLACED);
}

BOOST_AUTO_TEST_CASE(get_data_found_single)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");

    std::string data;
    status = p.getDataAt(0, 0, data);

    BOOST_CHECK(status == data::Page::statusCode::FOUND);
    BOOST_CHECK(data == "first");
}

BOOST_AUTO_TEST_CASE(get_data_found_multiple)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    p.setDataAt(1, 1, "second");
    p.setDataAt(3, 8, "third");

    std::string data;
    status = p.getDataAt(0, 0, data);

    BOOST_CHECK(status == data::Page::statusCode::FOUND);
    BOOST_CHECK(data == "first");

    status = p.getDataAt(1, 1, data);

    BOOST_CHECK(status == data::Page::statusCode::FOUND);
    BOOST_CHECK(data == "second");

    status = p.getDataAt(3, 8, data);

    BOOST_CHECK(status == data::Page::statusCode::FOUND);
    BOOST_CHECK(data == "third");
}


BOOST_AUTO_TEST_CASE(get_data_not_found)
{
    data::Page p;

    data::Page::statusCode status;

    std::string data;
    status = p.getDataAt(0, 0, data);

    BOOST_CHECK(status == data::Page::statusCode::NOT_FOUND);
    BOOST_CHECK(data == "");
}

BOOST_AUTO_TEST_CASE(get_data_not_found_after_sets)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    p.setDataAt(1, 1, "second");
    p.setDataAt(3, 8, "third");

    std::string data;
    status = p.getDataAt(2, 0, data);

    BOOST_CHECK(status == data::Page::statusCode::NOT_FOUND);
    BOOST_CHECK(data == "");
}

BOOST_AUTO_TEST_CASE(get_data_after_delete)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    p.setDataAt(1, 1, "second");
    p.setDataAt(1, 1, "");

    std::string data;
    status = p.getDataAt(1, 1, data);

    BOOST_CHECK(status == data::Page::statusCode::NOT_FOUND);
    BOOST_CHECK(data == "");
}

BOOST_AUTO_TEST_CASE(get_data_after_replace)
{
    data::Page p;

    data::Page::statusCode status;

    p.setDataAt(0, 0, "first");
    p.setDataAt(1, 1, "second");
    p.setDataAt(1, 1, "third");

    std::string data;
    status = p.getDataAt(1, 1, data);

    BOOST_CHECK(status == data::Page::statusCode::FOUND);
    BOOST_CHECK(data == "third");
}

BOOST_AUTO_TEST_CASE(get_max_row_col_empty)
{
    data::Page p;

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == -1);
    BOOST_CHECK(maxCol == -1);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_single)
{
    data::Page p;

    p.setDataAt(3, 4, "first");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == 4);
    BOOST_CHECK(maxCol == 3);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_multiple)
{
    data::Page p;

    p.setDataAt(1, 1, "first");
    p.setDataAt(3, 4, "second");
    p.setDataAt(5, 3, "third");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == 4);
    BOOST_CHECK(maxCol == 5);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_empty_after_delete)
{
    data::Page p;

    p.setDataAt(1, 1, "first");
    p.setDataAt(1, 1, "");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == -1);
    BOOST_CHECK(maxCol == -1);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_end_delete)
{
    data::Page p;

    p.setDataAt(1, 1, "first");
    p.setDataAt(2, 2, "second");
    p.setDataAt(3, 3, "third");
    p.setDataAt(3, 3, "");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == 2);
    BOOST_CHECK(maxCol == 2);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_middle_delete)
{
    data::Page p;

    p.setDataAt(1, 1, "first");
    p.setDataAt(2, 2, "second");
    p.setDataAt(3, 3, "third");
    p.setDataAt(2, 2, "");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == 3);
    BOOST_CHECK(maxCol == 3);
}

BOOST_AUTO_TEST_CASE(get_max_row_col_middle_then_end_delete)
{
    data::Page p;

    p.setDataAt(1, 1, "first");
    p.setDataAt(2, 2, "second");
    p.setDataAt(3, 3, "third");
    p.setDataAt(2, 2, "");
    p.setDataAt(3, 3, "");

    int maxRow = p.getMaxRow();
    int maxCol = p.getMaxCol();

    BOOST_CHECK(maxRow == 1);
    BOOST_CHECK(maxCol == 1);
}

BOOST_AUTO_TEST_CASE(set_empty_cell_with_empty_data)
{
    data::Page p;

    data::Page::statusCode status;

    status = p.setDataAt(0, 0, "");

    BOOST_CHECK(status == data::Page::statusCode::CELL_EMPTY);
}

BOOST_AUTO_TEST_CASE(get_subset)
{
    data::Page p1;
    
    p1.setDataAt(0, 0, "first");
    p1.setDataAt(1, 1, "second");
    p1.setDataAt(3, 1, "third");
    p1.setDataAt(4, 4, "fourth");

    data::Page* p2 = p1.subPage(1, 1, 3, 3);

    std::string data;
    p2->getDataAt(0, 0, data);
    BOOST_CHECK(data == "second");

    p2->getDataAt(1, 1, data);
    BOOST_CHECK(data == "");

    p2->getDataAt(2, 0, data);
    BOOST_CHECK(data == "third");

    p2->getDataAt(3, 3, data);
    BOOST_CHECK(data == "");

    p2->getDataAt(4, 4, data);
    BOOST_CHECK(data == "");
}