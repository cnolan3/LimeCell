#include <iostream>
//#include <ncurses.h>

#include "Controller.h"

int main(int argc, char *argv[])
{
//    if (argc < 2)
//    {
//        std::cout << "Enter the path to input file." << std::endl;
//        exit(1);
//    }

    if (argc > 1)
    {
        std::string inFilePath = argv[1];

        limecell::controller::runController(true, inFilePath, ",");
    }
    else
    {
        limecell::controller::runController();
    }

    return 0;
}
