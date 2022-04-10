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

            Exit::Exit()
            {

            }

            UINT Exit::run(data::Page* data, view::View* view)
            {
                return 1;
            }

            OpenFile::OpenFile(std::string filePath) :
                m_filePath(filePath)
            {

            }

            UINT OpenFile::run(data::Page* data, view::View* view)
            {
                fileops::statusCode fileStat = fileops::readFile(data, m_filePath);

                if (fileStat == fileops::FAIL)
                {
                    std::cerr << "open file command failed." << std::endl;
                    return 0;
                }

                view->updateData(0, 0, 0, data);
                view->refresh();

                return 0;
            }

            CloseFile::CloseFile()
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

            SetCell::SetCell(UINT layer, UINT col, UINT row, std::string cellData) :
                m_layer(layer), m_col(col), m_row(row), m_cellData(cellData)
            {

            }

            UINT SetCell::run(data::Page* data, view::View* view)
            {
                data::Page::statusCode dataStat = data->setDataAt(m_col, m_row, m_cellData);

                view->updateData(m_layer, data);
                view->refresh();

                return 0;
            }

            ClearCell::ClearCell(UINT layer, UINT col, UINT row) :
                m_layer(layer), m_col(col), m_row(row)
            {

            }

            UINT ClearCell::run(data::Page* data, view::View* view)
            {
                data::Page::statusCode dataStat = data->setDataAt(m_col, m_row, "");

                view->updateData(m_layer, data);
                view->refresh();

                return 0;
            }
        };
    };
};