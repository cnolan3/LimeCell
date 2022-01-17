/*!
 * @file ControllerCmds.cpp
 * 
 * @author Connor Nolan
 */

#include <iostream>

#include "ControllerCmds.h"

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

            Command* cmdFactory(cmdCode code, std::vector<std::string> args)
            {
                if (code == cmdCode::EXIT)
                    return new Exit();

                std::cout << "Invalid Controller Command" << std::endl;
                exit(1);
            }

            Exit::Exit() : Command()
            {

            }

            UINT Exit::run(data::Page* data)
            {
                return 1;
            }
        };
    };
};