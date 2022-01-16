/*!
 * @file Controller.cpp 
 * 
 * @author Connor Nolan
 */

#include <iostream>

#include "Controller.h"
#include "ControllerCodes.h"
#include "Page.h"
#include "FileOps.h"
#include "View.h"
#include "CLIView.h"

namespace limecell
{
    namespace controller
    {
        UINT runController(bool initFile, std::string filePath, std::string delim)
        {
            data::Page* page = new data::Page();

            if (initFile)
            {
                fileops::statusCode status = fileops::readFile(page, filePath, delim);

                if (status == fileops::FAIL)
                {
                    std::cout << "readfile " << filePath << " failed." << std::endl;
                    exit(1);
                }
            }

            view::View* view = new view::CLIView(5);

            view->updateData(0, 0, 0, page);
            view->refresh();

            std::vector<std::string> cmdResponse;
            while(1)
            {
                cmdResponse = view->getCommand();

                if (cmdResponse.size() == 1 && cmdResponse[0] == cmdcodes::EXIT)
                {
                    break;
                }
            }

            return 0;
        }

        UINT runController()
        {
            return runController(false, "", "");
        }
    };
};