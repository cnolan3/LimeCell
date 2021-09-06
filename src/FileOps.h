/*!
 * @file FileOps.h
 *
 * @author Connor Nolan
 */
#include <fstream>
#include <string>

#include "Page.h"

#pragma once

namespace limecell
{
    namespace fileops
    {
        /*! \brief enum for fileops status codes */
        enum statusCode
        {
            SUCCESS,
            FAIL
        };

        /*! \brief read csv file contents into a page object
         * 
         * @param page page to store data
         * @param filePath path to input file
         * @param delim delimeter for the file
         * @return a fileops status code
         */
        statusCode readFile(data::Page& page, std::string filePath, std::string delim = ",");

        /*! \brief write a page object to a file
         * 
         * @param page page data to write
         * @param filePath path to output file
         * @param delim delimimeter for the file
         * @return a fileops status code
         */
        statusCode writeFile(data::Page& page, std::string filePath, std::string delim = ",");
    };
};