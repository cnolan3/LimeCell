/*!
 * @file Page.h
 * container for csv data in memory.
 * 
 * @author Connor Nolan
 */

#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <ostream>

#include "DataTypes.h"

#pragma once

namespace limecell
{
    namespace data
    {
        /*! \brief cell structure
         * 
         * represents the position of a cell
         */
        struct cell
        {
            //! column number
            UINT col;
            //! row number
            UINT row;

            cell(UINT col, UINT row) { this->col = col; this->row = row; }

            bool operator==(const cell& c) const { return (this->col == c.col) && (this->row == c.row); }
        };

        /*! \brief hash function for cells
         * 
         * uses the cell column number and row number to create the hash.
         */
        struct cellHash
        {
            size_t operator()(const cell& c) const
            {
                return (std::hash<int>()(c.col)) ^ (std::hash<int>()(c.row));
            }
        };

        /*! \brief hash table linking cells to their data */
        typedef std::unordered_map<cell, std::string, cellHash> sheet;

        /*! \brief structure representing the quantity of cells along one axis */
        struct maxPos
        {
            //! row or column number
            UINT position;
            //! quantity of cells in that row or column
            UINT* quantity;

            maxPos(UINT position) { this->position = position; this->quantity = new UINT(1); }

            bool operator==(const maxPos& m) const { return this->position == m.position; }
            bool operator<(const maxPos& m) const { return this->position < m.position; }
        };

        /*! \brief sorted list of cell positions along one axis */
        typedef std::set<maxPos> posList;

        /*! \brief class containing all page data */
        class Page
        {
        public:

            Page();
            ~Page() = default;

            /*! \brief enum of page class status codes */
            enum statusCode
            {
                CELL_EMPTY,
                CELL_FILLED,
                CELL_DATA_ADDED,
                CELL_DATA_REPLACED,
                CELL_DATA_DELETED,
                NOT_FOUND,
                FOUND,
            };

            /*! \brief get data at a specified cell location.
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
            statusCode getDataAt(UINT col, UINT row, std::string& data); 

            /*! \brief set the data at a specified cell location.
             * 
             * returns status code CELL_DATA_DELETED and deletes the cell entry if
             * the cell if found and the input data is set to "".
             * returns status code CELL_DATA_REPLACED if the cell is found, the
             * existing data is replaced with the input data.
             * returns status code CELL_DATA_ADDED if the cell was not found and
             * the input data is not empty, a new cell is created with the input data.
             * returns status code CELL_EMPTY if the cell was not found and the
             * input data is empty, cell is not created.
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
            statusCode setDataAt(UINT col, UINT row, std::string data); 

            /*! \brief gets the current highest column number used in the page.
             *
             * Returns the index of the highest column in the page, returns -1 if
             * there are now columns in the page.
             * 
             * constant time, O(n).
             * 
             * @return highest col number
             */
            int getMaxCol();

            /*! \brief gets the current highest row number used in the page.
             *
             * Returns the index of the highest row in the page, returns -1 if
             * there are no rows in the page.
             * 
             * constant time O(n).
             * 
             * @return highest row number
             */
            int getMaxRow();

            /*! \brief return a new page containing a subset of this page
             *
             * @param startCol column to start subset from
             * @param startRow row to start subset from
             * @param numCols number of columns to include
             * @param numRows number of rows to include
             * @return sub page
             */
            Page* subPage(UINT startCol, UINT startRow, UINT numCols, UINT numRows);

        private: 

            /*! \brief decrements quantity of cells in a row.
             * 
             * if the row has any cells in it, the quantity value is decremented.
             * if, after being decremented, the quantity is zero, the maxPos entry
             * for the row is deleted. runs in logarithmic time, O(logn), where n
             * is the number of existing maxPos entries (aka, the number of currently
             * used rows).
             * 
             * @param row row number
             */
            void removeRow(UINT row);

            /*! \brief increment the quantity of cells in a row.
             * 
             * if the row has any cells in it, the quantity value is incremented.
             * otherwise, a maxPos entry is created for this row. runs in logarithmic
             * time, O(logn), where n is the number of existing maxPos entries (aka,
             * the number of currently used rows).
             * 
             * @param row row number
             */
            void addRow(UINT row);

            /*! \brief decrements quantity of cells in a column. 
             * 
             * if the column has any cells in it, the quantity value is decremented.
             * if, after being decremented, the quantity is zero, the maxPos entry
             * for the column is deleted. runs in logarithmic time, O(logn), where n
             * is the number of existing maxPos entries (aka, the number of currently
             * used columns).
             * 
             * @param col column number
             */
            void removeCol(UINT col);

            /*! \brief increment the quantity of cells in a column.
             *  
             * if the column has any cells in it, the quantity value is incremented.
             * otherwise, a maxPos entry is created for this column. runs in logarithmic
             * time, O(logn), where n is the number of existing maxPos entries (aka,
             * the number of currently used columns).
             * 
             * @param col column number
             */
            void addCol(UINT col);

            //! page data
            sheet m_pageData;

            //! list of used columns
            posList m_cols;
            //! list of used rows
            posList m_rows;
        };
    };
};