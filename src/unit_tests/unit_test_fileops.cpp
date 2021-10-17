/*!
 * @file unit_test_fileops.cpp
 * unit tests for file operation functions
 * 
 * @author Connor Nolan
 */
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "../FileOps.h"

BOOST_AUTO_TEST_CASE(readFile_read_data_success)
{
    int dataWidth = 3;
    int dataHeight = 3;
    std::string expectedData[9] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    boost::filesystem::path dataPath = boost::filesystem::canonical(boost::filesystem::current_path());

    dataPath += boost::filesystem::path("/src/unit_tests/mock_data/test_data_1.txt");

    limecell::data::Page* p = new limecell::data::Page();

    limecell::fileops::readFile(p, dataPath.string());

    BOOST_CHECK_MESSAGE(p->getMaxCol() == 2, "Incorrect number of columns in page.");
    BOOST_CHECK_MESSAGE(p->getMaxRow() == 2, "Incorrect number of rows in page.");

    for (int y = 0; y < dataHeight; y++)
    {
        for (int x = 0; x < dataWidth; x++)
        {
            std::string expected = expectedData[(y * dataWidth) + x];

            std::string actual;
            p->getDataAt(x, y, actual);

            BOOST_CHECK_EQUAL(expected, actual);        }
    }
}