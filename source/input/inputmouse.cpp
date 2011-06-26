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
*** \file    inputmouse.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the mouse API.
******************************************************************************/

#include "inputmouse.h"

InputMouse::InputMouse() {
    previous_mouse_b = delta_mouse_b = 0;
    pointer = CURSOR;
}

InputMouse::~InputMouse() {
}

short InputMouse::initMouse() {
    cursor = load_datafile("Data\\Gui\\cursorData.dat");

    if (!cursor) {
        return -1;
    } else return 0;
}

short InputMouse::getMouseLeftClick() {

    delta_mouse_b = mouse_b ^ previous_mouse_b;
    previous_mouse_b = mouse_b;
    short returnValue = -1;

    if (delta_mouse_b & 1) {
        if (mouse_b & 1) {
            returnValue = 0;
        } else {
            returnValue = 1;
        }
    }
    return returnValue;
}

short InputMouse::getMouseRightClick() {

    previous_mouse_b = mouse_b;
    delta_mouse_b = mouse_b ^ previous_mouse_b;
    short returnValue = -1;

    if (delta_mouse_b & 2) {
        if (mouse_b & 2) {
            returnValue = 0;
        } else {
            returnValue = 2;
        }
    }
    return returnValue;
}

bool InputMouse::getMouseFocus(short x1, short y1, short x2, short y2) {

    if ((mouse_x > x1) && (mouse_x < x2) &&
            (mouse_y > y1) && (mouse_y < y2)) {
        return true;
    }
    return false;

}

void InputMouse::drawCursor(BITMAP *bmp, short type) {
    if (type > -1) {
        masked_blit((BITMAP*)cursor[type].dat, bmp, 0, 0, mouse_x, mouse_y, 16, 16);
    } else {
        show_mouse(bmp);
    }
}

void InputMouse::draw(BITMAP *bmp) {
    if (pointer > -1) {
        masked_blit((BITMAP*)cursor[pointer].dat, bmp, 0, 0, mouse_x, mouse_y, 16, 16);
    } else {
        show_mouse(bmp);
    }
}

void InputMouse::setCursor(short type) {
    pointer = type;
}


void InputMouse::freeMouse() {
    unload_datafile(cursor);
}
