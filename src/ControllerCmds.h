/*!
 * @file ControllerCmds.h
 * Controller command object definitions.
 * 
 * @author Connor Nolan
 */

#ifndef __CONTROLLERCMDS_H__
#define __CONTROLLERCMDS_H__

#include <string>
#include <vector>

#include "Page.h"
#include "View.h"

namespace limecell
{
    namespace controller
    {
        namespace cmd
        {
            enum cmdCode
            {
                EXIT,
            };

            /*! \brief Command base class.
             * 
             * The command structure that the view uses to
             * communicate with the controller.
             */
            class Command
            {
            public:
                /*! \brief Command default constructor. */
                Command();

                /*! \brief construct a Command with arguments.
                 *
                 * @param args vector of string arguments.
                 */
                Command(std::vector<std::string> args);

                /*! \brief return the list of command arguments.
                 *
                 * @return a vector of string arguments
                 */
                std::vector<std::string> getArgs();

                /*! \brief run the command
                 *
                 * Runs the command, which can make changes to the
                 * Page data or View that is given to it, or both.
                 * It is assumed that if this function returns anything
                 * other than 0 then the program will exit. Each subclass
                 * must implement it's own command logic by overwriting
                 * this function.
                 * 
                 * @param data the Page data to modify.
                 * @param view the View to modify.
                 * @return status number
                 */
                virtual UINT run(data::Page* data, view::View* view) = 0;
            protected:

                //! argument list
                std::vector<std::string> args;

            };

            /*! \brief program exit command.
             *
             * When the run() function of this command is run, it
             * will return 1, which instructs the controller to
             * exit the program.
             */
            class Exit : public Command
            {
            public:
                /*! \brief default constructor */
                Exit();

                /*! \brief Runs the exit command.
                 *
                 * @param data Page data (unused)
                 * @param view View (unused)
                 * @return 1
                 */
                UINT run(data::Page* data, view::View* view);
            };

            /*! \brief Open file command
             *
             * Opens the file at the specified file path and
             * imports its data into a Page data structure,
             * then refreshes the View.
             */
            class OpenFile : public Command
            {
            public:
                /*! \brief constructor
                 *
                 * @param filePath path to the file to be opened.
                 */
                OpenFile(std::string filePath);

                /*! \brief run the open file command.
                 *
                 * @param data Page data to import into.
                 * @param view View to refresh.
                 * @return 0
                 */
                UINT run(data::Page* data, view::View* view);
            
            private:

                //! filepath to open
                std::string m_filePath;
            };

            /*! \brief command to close the currently open file.
             *
             * Deletes the current Page data and creates an
             * empty Page. Refreshes the View.
             */
            class CloseFile : public Command
            {
            public:
                /*! \brief default constructor */
                CloseFile();

                /*! \brief runs the close file command
                 *
                 * @param data Page data to reset.
                 * @param view view to refresh.
                 * @return 0
                 */
                UINT run(data::Page* data, view::View* view);
            };

            /*! \brief command to set data of a cell
             *
             * Sets the data in a single designated cell.
             */
            class SetCell : public Command
            {
            public:
                /*! \brief constructor
                 *
                 * @param layer layer of cell to edit.
                 * @param col column of cell to edit.
                 * @param row row of cell to edit.
                 * @param cellData data to insert into the cell.
                 */
                SetCell(UINT layer, UINT col, UINT row, std::string cellData);

                /*! \brief run the set cell command.
                 *
                 * @param data Page data to edit.
                 * @param view view to refresh.
                 * @return 0
                 */
                UINT run(data::Page* data, view::View* view);

            private:
                //! layer of cell
                UINT m_layer;
                //! column of cell
                UINT m_col;
                //! row of cell
                UINT m_row;
                //! data to insert
                std::string m_cellData;
            };

        };
    };
};

#endif