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

#include "CLIView.h"
#include "Utils.h"
#include "ControllerCodes.h"

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

        std::vector<std::string> CLIView::getCommand()
        {
            std::vector<std::string> ret;

            std::cout << "limecell > ";

            std::string input;
            std::cin >> input;

            if (input == "print" || input == "p")
            {
                setViewSizes();
                printView();
            }
            else if (input == "exit" || input == "end" || input == "quit" || input == "q")
            {
                ret.push_back(controller::cmdcodes::EXIT);
                std::cout << "Goodbye!" << std::endl;
            }
            else
            {
                std::cout << "Invalid input" << std::endl;
            }

            return ret;
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
    };
};