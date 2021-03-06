/*!
 * @file CLIView.h
 * Class for displaying on the command line.
 * 
 * @author Connor Nolan
 */

#ifndef __CLIVIEW_H__
#define __CLIVIEW_H__

#include <string>

#include "Page.h"
#include "DataTypes.h"
#include "View.h"

namespace limecell
{
    namespace view
    {
        class CLIView : public View
        {
        public:
            /*! \brief constructs a CLIView object */
            CLIView();

            /*! \brief constructs a CLIView object with set sizes
             * 
             * @param minColCharWidth minimum column width in characters.
             */
            CLIView(UINT minColCharWidth);

            /*! \brief destructs the CLIView object */
            ~CLIView();

            /*! \brief redraw the CLIView to the screen */
            void refresh();

            /*! \brief gets the next command from the veiw.
             *
             * Blocks and waits until a command is specified by the user.
             * Returns a vector of strings representing a command and its
             * arguments.
             * 
             * @return vector of strings
             */
            controller::cmd::Command* getCommand();

        protected:

            /*! \brief set the view width, height and column/row numbers */
            void setViewSizes();

            /*! \brief print the view to the command line. */
            void printView();

            /*! \brief print help info. */
            void printHelp();
        };
    };
};

#endif