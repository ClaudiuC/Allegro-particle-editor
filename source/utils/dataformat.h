///////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2009 by Hazardous Gaming
//                         All Rights Reserved
//
// This code is licensed under the MIT License. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.opensource.org/licenses/mit-license.php for details.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
*** \file    dataformat.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the DataFormat class
***
*** This code does various datatype conversions not included in the standard
*** libraries. Esspecially usefull to work around the GuiTextField objects
*** which return strings.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef DATAFORMAT_H
#define DATAFORMAT_H

#include <string>
#include <sstream>

using namespace std;


/** \class DataFormat dataformat.h "src\utils\dataformat.h"
*** \brief A class that provides a couple of methods that do datatype conversions
***        not included in the standard libraries (might also be just wrapper
***        functions used for the sake of simplicity).
**/
class DataFormat {
public:
    DataFormat();
    ~DataFormat();

    /** \name isInt()
    *** \brief Check wheter a passed string is an integer and also assigns the value
    ***        to a specified variable if true.
    *** \param string The string to be checked
    *** \param &i The variable to assign the value to, must be an integer
    *** \return True if it's an int, false otherwise
    **/
    bool isInt(const string s, int &i);

    /** \name stoi()
    *** \brief Converts a string to an integer. Wrapper for the atoi() function
    *** \param s The string to be converted
    *** \return The converted integer
    **/
    int stoi(string s);

    double stod(string s);
protected:
private:
};

#endif // DATAFORMAT_H
