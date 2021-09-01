#include "page.h"

#include <algorithm>

// construct a page
page::page()
{

}

/**
 * get data at a specified cell location.
 * 
 * returns status code FOUND if the cell is found and the data reference
 * is set, returns status NOT_FOUND if the cell is not found, and data
 * reference is set to "". runs in constant time, O(1).
 * 
 * @param col cell column number
 * @param row cell row number
 * @param data reference to data string
 * @return status code
 */
page::statusCode page::getDataAt(int col, int row, std::string& data)
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

/**
 * set the data at a specified cell location.
 * 
 * returns status code CELL_DATA_DELETED and deletes the cell entry if
 * the cell if found and the input data is set to "".
 * returns status code CELL_DATA_REPLACED if the cell is found, the
 * existing data is replaced with the input data.
 * returns status code CELL_DATA_ADDED if the cell was not found, a new
 * cell is created with the input data.
 * runs in constant time, O(1) if data is replaced. if data is added or
 * deleted, runs in logarithmic time, O(logn) + O(logm), where n is the
 * number of currently used rows and m is the number of currently used
 * columns.
 * 
 * @param col cell column number
 * @param row cell row number
 * @param data cell input data
 * @return status code
 */
page::statusCode page::setDataAt(int col, int row, std::string data)
{
    cell tmp(col, row);

    auto found = m_pageData.find(tmp);

    if (found != m_pageData.end())
    {
        if (data == "")
        {
            m_pageData.erase(found);

            removeCol(col);
            removeRow(row);

            return statusCode::CELL_DATA_DELETED;
        }

        (*found).second = data;

        return statusCode::CELL_DATA_REPLACED;
    }

    m_pageData[tmp] = data;

    addCol(col);
    addRow(row);

    return statusCode::CELL_DATA_ADDED;
}

/**
 * gets the current highest column number used in the page.
 * 
 * constant time, O(n).
 * 
 * @return highest col number
 */
int page::getMaxCol()
{
    if (m_cols.size() > 0)
    {
        return (*(m_cols.rbegin())).position;
    }

    return -1;
}

/**
 * gets the current highest row number used in the page
 * 
 * constant time O(n).
 * 
 * @return highest row number
 */
int page::getMaxRow()
{
    if (m_rows.size() > 0)
    {
        return (*(m_rows.rbegin())).position;
    }

    return -1;
}

/**
 * print the page to the stream (only for debug purposes)
 * 
 * @param stream stream to print to
 */
void page::print(std::ostream& stream)
{
    for (int i = 0; i <= getMaxRow(); i++)
    {
        for (int j = 0; j <= getMaxCol(); j++)
        {
            std::string data;
            if (getDataAt(j, i, data) == statusCode::NOT_FOUND)
            {
                data = "EMPTY";
            }

            stream << data << ", ";
        }

        stream << std::endl;
    }
}

/**
 * decrements quantity of cells in a row.
 * 
 * if the row has any cells in it, the quantity value is decremented.
 * if, after being decremented, the quantity is zero, the maxPos entry
 * for the row is deleted. runs in logarithmic time, O(logn), where n
 * is the number of existing maxPos entries (aka, the number of currently
 * used rows).
 * 
 * @param row row number
 */
void page::removeRow(int row)
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

/**
 * increment the quantity of cells in a row.
 * 
 * if the row has any cells in it, the quantity value is incremented.
 * otherwise, a maxPos entry is created for this row. runs in logarithmic
 * time, O(logn), where n is the number of existing maxPos entries (aka,
 * the number of currently used rows).
 * 
 * @param row row number
 */
void page::addRow(int row)
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

/**
 * decrements quantity of cells in a column.
 * 
 * if the column has any cells in it, the quantity value is decremented.
 * if, after being decremented, the quantity is zero, the maxPos entry
 * for the column is deleted. runs in logarithmic time, O(logn), where n
 * is the number of existing maxPos entries (aka, the number of currently
 * used columns).
 * 
 * @param col column number
 */
void page::removeCol(int col)
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

/**
 * increment the quantity of cells in a column.
 * 
 * if the column has any cells in it, the quantity value is incremented.
 * otherwise, a maxPos entry is created for this column. runs in logarithmic
 * time, O(logn), where n is the number of existing maxPos entries (aka,
 * the number of currently used columns).
 * 
 * @param col column number
 */
void page::addCol(int col)
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