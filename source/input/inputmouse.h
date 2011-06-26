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
*** \file    inputmouse.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the InputMouse class
***
*** This code provides a few useful mouse-related methods
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef INPUTMOUSE_H
#define INPUTMOUSE_H

#include <allegro.h>
#include <iostream>
#include "..\gui\cursorData.h"

#define DEFAULT -1

/** \class InputMouse inputmouse.h "src\input\inputmouse.h"
*** \brief This class provides a few useful mouse methods
**/
class InputMouse {
public:
    InputMouse();
    ~InputMouse();

    /** \name initMouse()
    *** \brief Load the mouse pointer GFX resources
    ***/
    short initMouse();

    /** \name Mouse input methods
    *** \brief A couple of functions that do proper left/right mouse-click
    ***        detection using a XOR operation.
    *** \return 0 if button clicked, 1 if button released, -1 if no input
    ***         was detected
    **/
    //@{
    short getMouseLeftClick();
    short getMouseRightClick();
    //@}

    /** \name getMouse
    *** \brief Check if the mouse hovers over a passed area
    *** \param x1 First corner X axis coordinate
    *** \param y1 First corner Y axis coordinate
    *** \param x2 First corner X axis coordinate
    *** \param y2 First corner Y axis coordinate
    *** \return True if the mouse hovers over the defined area,
    ***         false otherwise
    **/
    bool getMouseFocus(short x1, short y1, short x2, short y2);

    /** \name drawCursor()
    *** \brief Displays a custom cursor instead of the default Allefgro cursor
    *** \param type Defines what cursor to be displayed, if set to DEFAULT it
    ***        switches back to the Allegro cursor
    *** \param bmp The BITMAP to blit the pointer to
    **/
    void drawCursor(BITMAP *bmp, short type);

    /** \name draw()
    *** \brief Displays the current pointer
    *** \param bmp The BITMAP to draw on
    **/
    void draw(BITMAP *bmp);

    /** \name setCursor()
    *** \brief Sets the current cursor
    *** \param type Defines what cursor to be displayed, if set to DEFAULT it
    ***        switches back to the Allegro cursor
    **/
    void setCursor(short type);

    /** \name freeMouse()
    *** \brief Releases memory occupied by the cursor GFX
    **/
    void freeMouse();
private:
    //! These variables are used to determine mouse left/right clicks
    int previous_mouse_b, delta_mouse_b;

    DATAFILE *cursor;
    short pointer;
};

#endif // INPUTMOUSE_H
