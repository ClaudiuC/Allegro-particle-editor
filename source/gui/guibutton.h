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
*** \file    guibutton.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the button API.
***
*** This code provides the API used to manage GUI buttons using a doubly linked
*** list.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef GUIBUTTON_H_INCLUDED
#define GUIBUTTON_H_INCLUDED

#include <string>
#include "..\input\inputmouse.h"
#include "guiData.h"
#include "guiresources.h"

using namespace std;

#define MOUSE_OUT      0
#define MOUSE_ON       1
#define MOUSE_CLICK    2

typedef struct BUTTON_MASK {
    short x, y;
    short w, h;

    string label;
    bool displayed;
    bool destroyed;

    short state;
    short ID;

    bool mouse_in;


    BUTTON_MASK *next;
    BUTTON_MASK *previous;
} BUTTON_MASK;

class GuiButton {
public:
    GuiButton();
    ~GuiButton();

    BUTTON_MASK *getButtonByID(short button_id);
    void addButton(short x, short y, string label);

    short getLastButtonID();
    short updateButtons();
    void drawButtonImage(BITMAP *bmp, short button_id);
    void drawButtons(BITMAP *bmp);

    void setButtonLabel(short button_id, string label) {
        getButtonByID(button_id)->label = label;
    }
    void hideAllButtons() {
        BUTTON_MASK *thisButton = firstButton;

        while (thisButton != NULL) {
            thisButton->displayed = false;
            thisButton = thisButton->next;
        }
    }
    void showButton(short button_id) {
        getButtonByID(button_id)->displayed = true;
    }
    void hideButton(short button_id) {
        getButtonByID(button_id)->displayed = false;
    }
    void setButtonActive(short button_id) {
        getButtonByID(button_id)->state = MOUSE_ON;
    }
    short getButtonPosX(short button_id)   {
        return getButtonByID(button_id)->x;
    }
    short getButtonPosY(short button_id)   {
        return getButtonByID(button_id)->y;
    }
    short getButtonSizeW(short button_id)  {
        return getButtonByID(button_id)->w;
    }
    short getButtonSizeH(short button_id)  {
        return getButtonByID(button_id)->h;
    }

    string getButtonLabel(short button_id) {
        return getButtonByID(button_id)->label;
    }
    short getButtonState(short button_id)  {
        return getButtonByID(button_id)->state;
    }
    short getButtonID(short button_id)     {
        return getButtonByID(button_id)->ID;
    }

    bool getButtonMouseIn(short button_id) {
        return getButtonByID(button_id)->mouse_in;
    }
private:

    BUTTON_MASK *buttonAttributes;

    BUTTON_MASK *firstButton;
    BUTTON_MASK *lastButton;

    short auto_increment_id;
};

#endif // GUIBUTTON_H_INCLUDED
