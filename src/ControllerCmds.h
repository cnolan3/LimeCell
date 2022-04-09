/*!
 * @file ControllerCmds.h
 * Controller command object definitions.
 * 
 * @author Connor Nolan
 */

#ifndef __CONTROLLERCMDS_H__
#define __CONTROLLERCMDS_H__

#include <string>
#include <vector>

#include "Page.h"
#include "View.h"

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

                std::vector<std::string> getArgs();

                virtual UINT run(data::Page* data, view::View* view) = 0;
            protected:

                std::vector<std::string> args;

            };

            class Exit : public Command
            {
            public:
                Exit();

                UINT run(data::Page* data, view::View* view);
            };

            class OpenFile : public Command
            {
            public:
                OpenFile(std::string filePath);

                UINT run(data::Page* data, view::View* view);
            
            private:
                std::string m_filePath;
            };

            class CloseFile : public Command
            {
            public:
                CloseFile();

                UINT run(data::Page* data, view::View* view);
            };

            class SetCell : public Command
            {
            public:
                SetCell(UINT layer, UINT col, UINT row, std::string cellData);

                UINT run(data::Page* data, view::View* view);

            private:
                UINT m_layer;
                UINT m_col;
                UINT m_row;
                std::string m_cellData;
            };

        };
    };
};

#endif