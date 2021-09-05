#include <iostream>
#include <ncurses.h>

#include "Page.h"
#include "FileOps.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Enter the path to input and output files." << std::endl;
        exit(1);
    }

    std::string inFilePath = argv[1];
    std::string outFilePath = argv[2];

    limecell::data::Page p;

    if (limecell::fileops::readFile(p, inFilePath) == limecell::fileops::SUCCESS)
    {
        p.print(std::cout);
    }
    else
    {
        std::cout << "Failed to read file." << std::endl;

        exit(1);
    }

    if (limecell::fileops::writeFile(p, outFilePath) != limecell::fileops::SUCCESS)
    {
        std::cout << "Failed to write to file." << std::endl;

        exit(1);
    }

    return 0;
}
