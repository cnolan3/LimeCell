/**
 * @file View.cpp
 * 
 * @author Connor Nolan
 */

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "CLIView.h"
#include "Utils.h"
#include "ControllerCmds.h"

namespace limecell
{
    namespace view
    {
        int idColCharWidth = 6;

        CLIView::CLIView() :
            View()
        {
            
        }

        CLIView::CLIView(UINT minColCharWidth) : 
            View()
        {
            m_minColCharWidth = minColCharWidth;

            setViewSizes();
        }

        CLIView::~CLIView()
        {

        }

        void CLIView::refresh()
        {

        }

        controller::cmd::Command* CLIView::getCommand()
        {
            std::cout << "limecell > ";

            std::string input;
            std::getline(std::cin, input);
            std::cin.clear();

            std::vector<std::string> cmdVect;
            boost::algorithm::split(cmdVect, input, boost::is_any_of(" "));

            if (cmdVect.size() == 1)
            {
                if (cmdVect[0] == "print" || cmdVect[0] == "p")
                {
                    setViewSizes();
                    printView();
                    return nullptr;
                }
                else if (cmdVect[0] == "exit" || cmdVect[0] == "end" || cmdVect[0] == "quit" || cmdVect[0] == "q")
                {
                    std::cout << "Goodbye!" << std::endl;
                    return new controller::cmd::Exit(); 
                }
                else if (cmdVect[0] == "help" || cmdVect[0] == "h")
                {
                    printHelp();
                    return nullptr;
                }
                else if (cmdVect[0] == "close")
                {
                    return new controller::cmd::CloseFile();
//                    std::cout << "Are you sure? all your hard unsaved work will be lost." << std::endl;
//                    std::string sure;
//                    std::cin >> sure;
//                    std::cin.clear();
//
//                    if (sure == "yes" || sure == "YES" || sure == "y" || sure == "Y")
//                    {
//                        return new controller::cmd::CloseFile();
//                    }
//                    else
//                    {
//                        std::cout << "Good choice" << std::endl;
//                        return nullptr;
//                    }
                }
            }
            else if (cmdVect.size() == 2)
            {
                if (cmdVect[0] == "open")
                {
                    return new controller::cmd::OpenFile(cmdVect[1]);
                }
            }
            else if (cmdVect.size() == 4)
            {
                if (cmdVect[0] == "set")
                {
                    return new controller::cmd::SetCell(0, std::stoi(cmdVect[1]), std::stoi(cmdVect[2]), cmdVect[3]);
                }
            }

            std::cout << "Invalid input" << std::endl;

            return nullptr;
        }

        void CLIView::setViewSizes()
        {
            // modified from https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

            m_maxCharWidth = w.ws_col;
            m_maxCharHeight = w.ws_row - 1;

            m_numCols = (m_maxCharWidth - (idColCharWidth + 1)) / (m_minColCharWidth + 1);
            m_numRows = m_maxCharHeight - 1;
        }

        void CLIView::printView()
        {
            UINT selectedLayer = 0;
            data::Page* layer = m_layers[selectedLayer];

            std::cout << std::string(idColCharWidth + 1, ' ');

            for (int col = 0; col < m_numCols; col++)
            {
                std::cout << centerJustify(std::to_string(m_firstCol + col), m_minColCharWidth) << " ";
            }

            std::cout << std::endl;

            for (int row = 0; row < m_numRows; row++)
            {
                std::cout << centerJustify(std::to_string(m_firstRow + row), idColCharWidth) << "|";

                for (int col = 0; col < m_numCols; col++)
                {
                    std::string data;
                    layer->getDataAt(col, row, data);

                    std::cout << rightJustify(data, m_minColCharWidth) << "|";
                }
                
                std::cout << std::endl;
            }
        }

        void CLIView::printHelp()
        {
            std::cout << "print | p : Print the contents of the currently open file." << std::endl;
            std::cout << "quit | q | exit | end : Exit limecell." << std::endl;
            std::cout << "help | h : Show help info (but you already knew that)." << std::endl;
            std::cout << "open <filepath> : opens file at <filepath>." << std::endl;
            std::cout << "close : closes the currently open file without saving changes." << std::endl;
            std::cout << "set <colnum> <rownum> <data> : sets the data in the cell at (<colnum>, <rownum>) to <data>." << std::endl;
        }
    };
};