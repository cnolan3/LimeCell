/**
 * @file View.cpp
 * 
 * @author Connor Nolan
 */

#include "View.h"

namespace limecell
{
    namespace view
    {
        View::View()
        {
            
        }

        View::~View()
        {

        }

        void View::updateData(UINT layer, UINT newFirstCol, UINT newFirstRow, data::Page* newData)
        {
            m_firstCol = newFirstCol;
            m_firstRow = newFirstRow;

            if (m_layers.size() > layer)
            {
                delete m_layers[layer];
                m_layers[layer] = newData->subPage(m_firstCol, m_firstRow, m_numCols, m_numRows);
            }
            else
            {
                m_layers.push_back(newData->subPage(m_firstCol, m_firstRow, m_numCols, m_numRows));
            }
        }

        void View::updateData(UINT layer, data::Page* newData)
        {
            return View::updateData(layer, m_firstCol, m_firstRow, newData);
        }

        UINT View::getNumCols()
        {
            return m_numCols;
        }

        UINT View::getNumRows()
        {
            return m_numRows;
        }
    };
};