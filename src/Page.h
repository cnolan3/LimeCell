/**
 * container for csv data in memory.
 * 
 * Author: Connor Nolan
 */

#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <ostream>

#pragma once

namespace limecell
{
    namespace data
    {
        /**
         * cell structure
         * 
         * represents the position of a cell
         */
        struct cell
        {
            int col;
            int row;

            cell(int col, int row) { this->col = col; this->row = row; }

            bool operator==(const cell& c) const { return (this->col == c.col) && (this->row == c.row); }
        };

        /**
         * hash function for cells
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

        /**
         * hash table linking cells to their data
         */
        typedef std::unordered_map<cell, std::string, cellHash> sheet;

        /**
         * structure representing the quantity of cells along one axis
         */
        struct maxPos
        {
            int position; // row or column number
            int* quantity;

            maxPos(int position) { this->position = position; this->quantity = new int(1); }

            bool operator==(const maxPos& m) const { return this->position == m.position; }
            bool operator<(const maxPos& m) const { return this->position < m.position; }
        };

        /**
         * sorted list of cell positions along one axis
         */
        typedef std::set<maxPos> posList;

        /**
         * class containing all page data
         */
        class Page
        {
        public:

            Page();
            ~Page() = default;

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

            statusCode setDataAt(int col, int row, std::string data);
            statusCode getDataAt(int col, int row, std::string& data);

            int getMaxCol();
            int getMaxRow();

            void print(std::ostream& stream);

        private: 

            void removeRow(int row);
            void addRow(int row);

            void removeCol(int col);
            void addCol(int col);

            // page data
            sheet m_pageData;

            // list of used columns
            posList m_cols;
            // list of used rows
            posList m_rows;
        };
    };
};