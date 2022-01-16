/*!
 * @file Controller.h
 * Controller functions.
 * 
 * @author Connor Nolan
 */

#include <string>

#include "DataTypes.h"

#pragma once

namespace limecell
{
    namespace controller
    {
        /*! \brief start the controller.
         * 
         * Start the controller with input file options.
         * 
         * @param initFile if true, initialize with an existing file, ignore file options if false.
         * @param filePath path to existing file to open.
         * @param delim delimiter of file.
         * @return status code.
         */
        UINT runController(bool initFile, std::string filePath, std::string delim);

        /*! \brief start the controller (without input file options) */
        UINT runController();
    };
};