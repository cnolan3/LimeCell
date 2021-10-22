/**
 * @file Page.cpp
 * 
 * @author Connor Nolan
 */
#include "Page.h"

#include <algorithm>
#include <cstring>

/**
 * NOTE: many of the function comments in the header file mention "currently use rows"
 * or "currently used columns", a "currently used row" is a row of cells that
 * has at least one FILLED cell currently inside it, a row that has only empty
 * cells is not considered a "used" row.
 * 
 * ex.
 *       | col 1 | col 2 | col 3 |
 * -------------------------------
 * row 1 | "A"   |       |       |
 * -------------------------------
 * row 2 |       |       |       |
 * -------------------------------
 * row 3 | "C"   |       | "B"   |
 * -------------------------------
 * row 4 |       |       |       |
 * -------------------------------
 * 
 * rows 1 and 3 are considered "currently used" while rows 2 and 4 are not,
 * likewise, column 2 is not currently used.
 */

namespace limecell
{
    namespace data
    {
        Page::Page()
        {

        }

        Page::Page(const Page& p)
        {
            m_pageData = p.m_pageData;
            m_cols = p.m_cols;
            m_rows = p.m_rows;
        }

        Page::statusCode Page::getDataAt(UINT col, UINT row, std::string& data)
        {
            auto found = m_pageData.find(cell(col, row));

            if (found != m_pageData.end())
            {
                data = (*found).second;
                return statusCode::FOUND;
            }

            data = "";
            return statusCode::NOT_FOUND;
        }

        Page::statusCode Page::setDataAt(UINT col, UINT row, std::string data)
        {
            cell tmp(col, row);

            auto found = m_pageData.find(tmp);

            if (found != m_pageData.end())
            {
                if (data == "")
                {
                    // remove the cell from the sheet
                    m_pageData.erase(found);

                    // decrement the number of cells in
                    // this column and row
                    removeCol(col);
                    removeRow(row);

                    return statusCode::CELL_DATA_DELETED;
                }

                // replace the data in the cell
                (*found).second = data;

                return statusCode::CELL_DATA_REPLACED;
            }

            // if input data is not empty, create new cell
            if (data != "")
            {
                // add the new cell to the sheet
                m_pageData[tmp] = data;

                // increment the number of cells in
                // this column and row
                addCol(col);
                addRow(row);

                return statusCode::CELL_DATA_ADDED;
            }

            return statusCode::CELL_EMPTY;
        }

        int Page::getMaxCol()
        {
            if (m_cols.size() > 0)
            {
                // the max col is the last entry into m_cols
                // since it is a sorted set.
                return (*(m_cols.rbegin())).position;
            }

            return -1;
        }

        int Page::getMaxRow()
        {
            if (m_rows.size() > 0)
            {
                // the max row is the last entry into m_rows
                // since it is a sorted set.
                return (*(m_rows.rbegin())).position;
            }

            return -1;
        }

        void Page::removeRow(UINT row)
        {
            auto found = m_rows.find(maxPos(row));

            if (found != m_rows.end())
            {
                (*(*found).quantity)--;

                if ((*(*found).quantity) <= 0)
                {
                    m_rows.erase(found);
                }
            }
        }

        void Page::addRow(UINT row)
        {
            maxPos tmp(row);

            auto found = m_rows.find(tmp);

            if (found != m_rows.end())
            {
                (*(*found).quantity)++;
            }
            else
            {
                m_rows.insert(tmp);
            }
        }

        void Page::removeCol(UINT col)
        {
            auto found = m_cols.find(maxPos(col));

            if (found != m_cols.end())
            {
                (*(*found).quantity)--;

                if ((*(*found).quantity) <= 0)
                {
                    m_cols.erase(found);
                }
            }
        }

        void Page::addCol(UINT col)
        {
            maxPos tmp(col);

            auto found = m_cols.find(tmp);

            if (found != m_cols.end())
            {
                (*(*found).quantity)++;
            }
            else
            {
                m_cols.insert(tmp);
            }
        }

        Page* Page::subPage(UINT startCol, UINT startRow, UINT numCols, UINT numRows)
        {
            Page* ret = new Page;

            for (UINT row = 0; row < numRows; row++)
            {
                for (UINT col = 0; col < numCols; col++)
                {
                    std::string data;
                    this->getDataAt(col + startCol, row + startRow, data);
                    ret->setDataAt(col, row, data);
                }
            }

            return ret;
        }

        void Page::operator=(const Page& p)
        {
            m_pageData = p.m_pageData;
            m_cols = p.m_cols;
            m_rows = p.m_rows;
        }
    };
};