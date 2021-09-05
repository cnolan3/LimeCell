#include <fstream>
#include <string>

#include "Page.h"

#pragma once

namespace limecell
{
    namespace fileops
    {
        enum statusCode
        {
            SUCCESS,
            FAIL
        };

        statusCode readFile(data::Page& page, std::string filePath);
        statusCode writeFile(data::Page& page, std::string filepath);
    };
};