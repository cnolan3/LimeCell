/*!
 * @file utils.h 
 * 
 * @author Connor Nolan
 */

#pragma once

/*! \brief access a 1D array using 2D coordinates
 * 
 * @param array the 1D array to access
 * @param size total size of the array
 * @param x column coordinate
 * @param y row coordinate
 * @param width intended with of a single row of the '2D' array
 */
template <class T>
extern T getArrayXY(T* array, int size, int x, int y, int width);