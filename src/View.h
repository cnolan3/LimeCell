/*!
 * @file View.h
 * Base class for program views.
 * 
 * @author Connor Nolan
 */

#include <string>

#include "Page.h"

typedef unsigned int UINT;

namespace limecell
{
    namespace view
    {
        class View
        {
        public:
            View();

            View(UINT maxCharWidth, UINT maxCharHeight, UINT minColCharWidth);

            ~View();

            /*! \brief redraw the view to the screen */
            virtual void refresh() = 0;

            /*! \brief gets the next command from the veiw.
             *
             * Blocks and waits until a command is specified by the user.
             * Returns a vector of strings representing a command and its
             * arguments.
             * 
             * @return vector of strings
             */
            virtual std::vector<std::string> getCommand() = 0;

            /*! \brief update the displayed data
             *
             * @param newFirstCol set the first column number to this value
             * @param newFirstRow set the first row number to this value
             * @param newData new page subset to display
             */
            virtual void updateData(UINT newFirstCol, UINT newFirstRow, data::Page* newData);

            /*! \brief get the number of columns
             * 
             * @return number of columns
             */
            virtual UINT getNumCols();

            /*! /brief get the number of rows
             * 
             * @return number of rows
             */
            virtual UINT getNumRows();

        protected:
            //! max width of the view in characters
            UINT maxCharWidth;
            //! max height of the view in characters
            UINT maxCharHeight;

            //! number of columns in current view
            UINT numCols;
            //! number of row in current view
            UINT numRows;

            //! current first column
            UINT firstCol;
            //! current first row
            UINT firstRow;

            //! currently selected column
            UINT selectedCol;
            //! currently selected row
            UINT selectedRow;

            //! array of column character widths
            UINT* colCharWidths;

            //! array of current cell data
            std::string* viewData;
        };
    };
};