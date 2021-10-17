/*!
 * @file FileOps.cpp 
 * 
 * @author Connor Nolan
 */
#include "FileOps.h"

#include <boost/regex.hpp>

namespace limecell
{
    namespace fileops
    {
        statusCode readFile(data::Page* page, std::string filePath, std::string delim)
        {
            // modified from https://bravenewmethod.com/2016/09/17/quick-and-robust-c-csv-reader-with-boost/
            const boost::regex fieldsRegex(delim);

            std::ifstream inFile(filePath);

            if (!inFile.is_open())
            {
                return statusCode::FAIL;
            }

            int row = 0;
            for (std::string line; std::getline(inFile, line); )
            { 
                boost::sregex_token_iterator fields(line.begin(), line.end(), fieldsRegex, -1);
                boost::sregex_token_iterator end;

                int col = 0;
                while(fields != end)
                {
                    std::string token = fields->str();
                    ++fields;
                    page->setDataAt(col, row, token);
                    col++;
                }

                row++;
            }

            inFile.close();

            return statusCode::SUCCESS;
        }

        statusCode writeFile(data::Page* page, std::string filePath, std::string delim)
        {
            std::ofstream outFile(filePath, std::ostream::trunc);

            if (!outFile.is_open())
            {
                return statusCode::FAIL;
            }

            for (int row = 0; row <= page->getMaxRow(); row++)
            {
                std::string line;
                for (int col = 0; col <= page->getMaxCol(); col++)
                {
                    std::string field;
                    page->getDataAt(col, row, field);
                    line = line + field + delim;
                }

                outFile << line << std::endl;
            }

            outFile.close();

            return statusCode::SUCCESS;
        }
    }
}