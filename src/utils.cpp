#include "utils.h"

#include <stdexcept>

template <class T>
T getArrayXY(T* array, int size, int x, int y, int width)
{
    int arrayPos = (y * width) + x;

    if (arrayPos >= size || arrayPos < 0)
    {
        throw std::out_of_range("getArrayXY(), attempting to access beyond array size.");
    }

    return array[arrayPos];
}

template int getArrayXY(int* array, int size, int x, int y, int width);