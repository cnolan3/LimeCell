# src Structure

(generally ordered by appearance in program flow)

- **main.cpp**

    Main entrypoint to the program. Takes input and starts the controller.
    
- **Controller.cpp/Controller.h**

    Contains the main loop of the program. Initializes the correct view
    type and data in the model. Interprets commands from the view and modifies
    data in the model if necessary.
    
- **ControllerCmds.cpp/ControllerCmds.h**

    Defines the comands that the view can use to communicate with the controller,
    how the syntax is structured and what action they take when sent. Designed
    agnostic across view types, so that the view type can be easily interchanged.
    
- **view.cpp/view.h**

    Base class for the view structure. Defines data and functions common to
    all view types (cli, ncurses, etc.)
    
- **CLIView.cpp/CLIView.h**

    Defines the behavior of the CLI view, runs a custom interactive terminal
    interface to take commands, and prints the output of those commands to
    the terminal.
    
- **Page.cpp/Page.h**

    Defines the main data structure representing a spreadsheet page. This is
    the main backend structure of the model.
    
- **FileOps.cpp/FileOps.h**

    Utility functions for accessing and modifiying files on disk. Most functions
    here are used to read a file into a Page (Page.h) structure.
    
- **Utils.cpp/Utils.h**

    Various utility functions for working with specific data structures or
    structuring output format, for example.
    
- **DataTypes.h**

    Defines the basic data types used across this project.
