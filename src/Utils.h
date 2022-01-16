/*!
 * @file utils.h 
 * Collection of useful utility functions.
 * 
 * @author Connor Nolan
 */

#pragma once

#include <ostream>

#include "Page.h"
#include "DataTypes.h"

/*! \brief access a 1D array using 2D coordinates.
 * 
 * @param array the 1D array to access
 * @param size total size of the array
 * @param x column coordinate
 * @param y row coordinate
 * @param width intended with of a single row of the '2D' array
 * @return data stored at (x, y) simulated coordinates
 */
template <class T>
extern T getArrayXY(T* array, UINT size, UINT x, UINT y, UINT width);

/*! \brief print the contents of a page object to a stream.
 *
 * @param p pointer to a page object
 * @param stream reference to the stream to print to
 */
void printPage(limecell::data::Page* p, std::ostream& stream);

/*! \brief create a center justified string.
 *
 * Center justify string str by padding each side with whitespace
 * according to the column width given. If the input string is
 * larger than the line width, will cut off the excess from the
 * end of the string.
 * 
 * @param str string to justify
 * @param lineCharWidth character width of the column
 * @return center justified string
 */
std::string centerJustify(std::string str, UINT lineCharWidth);

/*! \brief create a left justified string.
 *
 * Left justify string str by padding each side with whitespace
 * according to the lineumn width given. If the input string is
 * larger than the line width, will cut off the excess from the
 * end of the string.
 * 
 * @param str string to justify
 * @param lineCharWidth character width of the lineumn
 * @return left justified string
 */
std::string leftJustify(std::string str, UINT lineCharWidth);

/*! \brief create a right justified string.
 *
 * Right justify string str by padding each side with whitespace
 * according to the lineumn width given. If the input string is
 * larger than the line width, will cut off the excess from the
 * end of the string.
 * 
 * @param str string to justify
 * @param lineCharWidth character width of the lineumn
 * @return right justified string
 */
std::string rightJustify(std::string str, UINT lineCharWidth);
