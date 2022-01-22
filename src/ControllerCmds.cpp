/*!
 * @file ControllerCmds.cpp
 * 
 * @author Connor Nolan
 */

#include <iostream>

#include "ControllerCmds.h"
#include "FileOps.h"

namespace limecell
{
    namespace controller
    {
        namespace cmd
        {
            Command::Command()
            {

            }

            Command::Command(std::vector<std::string> args) : args(args)
            {
                
            }

            Exit::Exit() : Command()
            {

            }

            UINT Exit::run(data::Page* data, view::View* view)
            {
                return 1;
            }

            OpenFile::OpenFile(std::string filePath) : Command()
            {
                this->args.push_back(filePath);
            }

            UINT OpenFile::run(data::Page* data, view::View* view)
            {
                std::string filePath = this->args[0];

                fileops::statusCode fileStat = fileops::readFile(data, filePath);

                if (fileStat == fileops::FAIL)
                {
                    std::cout << "open file command failed." << std::endl;
                    return 0;
                }

                view->updateData(0, 0, 0, data);
                view->refresh();

                return 0;
            }

            CloseFile::CloseFile() : Command()
            {

            }

            UINT CloseFile::run(data::Page* data, view::View* view)
            {
                delete data;
                data = new data::Page;

                view->updateData(0, 0, 0, data);
                view->refresh();

                return 0;
            }

        };
    };
};