/*!
 * @file unit_test_fileops.cpp
 * unit tests for file operation functions
 * 
 * @author Connor Nolan
 */
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

#include "../FileOps.h"

bool getMockDataPath(std::string mockFile, boost::filesystem::path& dataPath)
{
    const std::string fullMockPath = "/src/unit_tests/mock_data/" + mockFile;

    dataPath = boost::filesystem::canonical(boost::filesystem::current_path());

    dataPath += boost::filesystem::path(fullMockPath);

    return boost::filesystem::exists(dataPath);
}

BOOST_AUTO_TEST_SUITE(fileops_test_suite)

BOOST_AUTO_TEST_CASE(readFile_read_data_success)
{
    int dataWidth = 3;
    int dataHeight = 3;
    std::string expectedData[9] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    boost::filesystem::path dataPath;
    
    BOOST_REQUIRE(getMockDataPath("test_data_1.txt", dataPath));

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

            BOOST_CHECK_EQUAL(expected, actual);
        }
    }
}

BOOST_AUTO_TEST_CASE(writeFile_success)
{
    limecell::data::Page* p = new limecell::data::Page();

    p->setDataAt(0, 0, "1");
    p->setDataAt(1, 0, "2");
    p->setDataAt(2, 0, "3");
    p->setDataAt(0, 1, "4");
    p->setDataAt(1, 1, "5");
    p->setDataAt(2, 1, "6");
    p->setDataAt(0, 2, "7");
    p->setDataAt(1, 2, "8");
    p->setDataAt(2, 2, "9");

    boost::filesystem::path tmpDataPath;
    getMockDataPath("tmp_page_out.txt", tmpDataPath);

    boost::filesystem::path mockDataPath;
    BOOST_REQUIRE(getMockDataPath("test_data_1.txt", mockDataPath));

    limecell::fileops::writeFile(p, tmpDataPath.string());

    BOOST_REQUIRE(boost::filesystem::exists(tmpDataPath.string()));

    std::ifstream tmpFile(tmpDataPath.string());
    std::ifstream mockFile(mockDataPath.string());

    std::string tmpLine;
    std::string mockLine;
    while(std::getline(tmpFile, tmpLine) && std::getline(mockFile, mockLine))
    {
        BOOST_CHECK_EQUAL(tmpLine, mockLine);
    }

    tmpFile.close();
    mockFile.close();

    boost::filesystem::remove(tmpDataPath);
}

BOOST_AUTO_TEST_SUITE_END()