/*!
 * @file ControllerCmds.h
 * Controller command object definitions.
 * 
 * @author Connor Nolan
 */

#include <string>
#include <vector>

#include "Page.h"

#pragma once

namespace limecell
{
    namespace controller
    {
        namespace cmd
        {
            enum cmdCode
            {
                EXIT,
            };

            class Command
            {
            public:
                Command();
                Command(std::vector<std::string> args);

                virtual UINT run(data::Page* data) = 0;
            private:

                std::vector<std::string> args;

            };

            Command* cmdFactory(cmdCode code, std::vector<std::string> args);

            class Exit : public Command
            {
            public:
                Exit();

                UINT run(data::Page* data);
            };
        };
    };
};