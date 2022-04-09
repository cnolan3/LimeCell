/*!
 * @file View.h
 * Base class for program views.
 * 
 * @author Connor Nolan
 */

#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>

#include "Page.h"
#include "DataTypes.h"

namespace limecell
{
    // forward declare the command class
    namespace controller
    {
        namespace cmd
        {
            class Command;
        };
    };

    namespace view
    {
        class View
        {
        public:
            /*! \brief constructs a view object */
            View();

            /*! \brief destructs the view object */
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
            virtual controller::cmd::Command* getCommand() = 0;

            /*! \brief update the displayed data
             *
             * Will update the selected layer with the data in newData,
             * will copy the data directly into the layer if the layer
             * already exists, and will create a new layer with this data
             * if it does not already exist. Also updates the number ID of
             * the leftmost column and topmost row.
             *
             * @param layer layer number to insert data into
             * @param newFirstCol set the first column number to this value
             * @param newFirstRow set the first row number to this value
             * @param newData new page subset to display
             */
            virtual void updateData(UINT layer, UINT newFirstCol, UINT newFirstRow, data::Page* newData);

            /*! \brief update the displayed data without changing cell locations
             *
             * @param layer layer number to insert data into
             * @param newData new page subset to display
             */
            virtual void updateData(UINT layer, data::Page* newData);

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
            UINT m_maxCharWidth;
            //! max height of the view in characters
            UINT m_maxCharHeight;
            //! minimum width of columns in characters
            UINT m_minColCharWidth;

            //! number of columns in current view
            UINT m_numCols;
            //! number of row in current view
            UINT m_numRows;

            //! current first column
            UINT m_firstCol;
            //! current first row
            UINT m_firstRow;

            //! currently selected column
            UINT m_selectedCol;
            //! currently selected row
            UINT m_selectedRow;

            //! array of column character widths
            UINT* m_colCharWidths;

            //! vector of view data layers
            /*!
             * Vector of data layers that will be printed
             * to the screen. Every layer has the same height
             * and width, and the view should provide some
             * method of switching between which layer is
             * being displayed.
             * NOTE: View layers are not currently very
             * useful, but in the future will be used to
             * facilitate Excel style functions and other
             * advanced features by putting function data
             * into the base data and interpreting that data
             * in another layer.
             */
            std::vector<limecell::data::Page*> m_layers;
        };
    };
};

#endif