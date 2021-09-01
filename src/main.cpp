#include <iostream>
#include <ncurses.h>
#include <set>
#include <string>
#include "page.h"

int main(int argc, char *argv[])
{
    page p;

    p.setDataAt(0, 0, "first");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(1, 1, "second");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(1, 1, "third");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(2, 0, "fourth");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(1, 1, "");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(0, 0, "");

    p.print(std::cout);
    std::cout << std::endl;

    p.setDataAt(4, 5, "fifth");

    p.print(std::cout);
    std::cout << std::endl;

    return 0;
}
