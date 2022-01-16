/**
 * @file Utils.cpp
 * 
 * @author Connor Nolan
 */
#include "Utils.h"

#include <stdexcept>

template <class T>
T getArrayXY(T* array, UINT size, UINT x, UINT y, UINT width)
{
    int arrayPos = (y * width) + x;

    if (arrayPos >= size || arrayPos < 0)
    {
        throw std::out_of_range("getArrayXY(), attempting to access beyond array size.");
    }

    return array[arrayPos];
}

template int getArrayXY(int* array, UINT size, UINT x, UINT y, UINT width);


void printPage(limecell::data::Page* p, std::ostream& stream)
{
    if (p == nullptr)
        return;
    
    for (int i = 0; i <= p->getMaxRow(); i++)
    {
        for (int j = 0; j <= p->getMaxCol(); j++)
        {
            std::string data;
            if (p->getDataAt(j, i, data) == limecell::data::Page::statusCode::NOT_FOUND)
            {
                data = "EMPTY";
            }

            stream << data << ", ";
        }

        stream << std::endl;
    }
}

std::string centerJustify(std::string str, UINT lineCharWidth)
{
    UINT spaceRemaining = lineCharWidth - str.size();

    if (spaceRemaining < 0)
    {
        spaceRemaining = 0;
        str = str.substr(0, lineCharWidth);
    }

    UINT backPadSpace = spaceRemaining / 2;
    UINT frontPadSpace = spaceRemaining - backPadSpace;

    return (std::string(frontPadSpace, ' ') + str + std::string(backPadSpace, ' '));
}

std::string leftJustify(std::string str, UINT lineCharWidth)
{
    UINT spaceRemaining = lineCharWidth - str.size();

    if (spaceRemaining < 0)
    {
        spaceRemaining = 0;
        str = str.substr(0, lineCharWidth);
    }

    return (str + std::string(spaceRemaining, ' '));
}

std::string rightJustify(std::string str, UINT lineCharWidth)
{
    UINT spaceRemaining = lineCharWidth - str.size();

    if (spaceRemaining < 0)
    {
        spaceRemaining = 0;
        str = str.substr(0, lineCharWidth);
    }

    return (std::string(spaceRemaining, ' ') + str);
}