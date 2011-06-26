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
*** \file    guibutton.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the button API.
******************************************************************************/

#include "guibutton.h"

extern InputMouse mouse;
extern GuiResources resources;

GuiButton::GuiButton() {
    firstButton = lastButton = buttonAttributes = NULL;
    auto_increment_id = 0;
}

GuiButton::~GuiButton() {
    BUTTON_MASK *thisButton = firstButton;
    BUTTON_MASK *destroyedButton = NULL;

    while (thisButton != NULL) {
        destroyedButton = thisButton;
        thisButton = thisButton->next;
        delete destroyedButton;
    }
    firstButton = NULL;
    lastButton = NULL;
}

BUTTON_MASK *GuiButton::getButtonByID(short button_id) {

    BUTTON_MASK *thisButton = firstButton;
    BUTTON_MASK *foundButton = NULL;

    while (thisButton != NULL) {
        if (thisButton->ID != button_id) thisButton = thisButton->next;
        else {
            foundButton = thisButton;
            return foundButton;
        }
    }
    return NULL;
}

void GuiButton::addButton(short x, short y, string label) {
    if (firstButton==NULL) {
        firstButton = new BUTTON_MASK;
        lastButton = firstButton;
        lastButton->next = NULL;
        lastButton->previous = NULL;
    } else {
        lastButton->next = new BUTTON_MASK;
        lastButton->next->previous = lastButton;
        lastButton = lastButton->next;
        lastButton->next = NULL;
    }

    lastButton->x = x;
    lastButton->y = y;

    lastButton->w = text_length(font, label.c_str())+10;
    lastButton->h = text_height(font)+10;
    lastButton->label = label;
    lastButton->state = MOUSE_OUT;
    lastButton->displayed = true;
    lastButton->mouse_in = false;
    lastButton->destroyed=false;
    lastButton->ID = auto_increment_id;

    auto_increment_id++;

    buttonAttributes = lastButton;
}

short GuiButton::getLastButtonID() {
    return lastButton->ID;
}

short GuiButton::updateButtons() {
    BUTTON_MASK *thisButton = firstButton;

    while (thisButton != NULL) {
        if (thisButton->displayed) {
            thisButton->mouse_in = mouse.getMouseFocus(thisButton->x, thisButton->y, thisButton->x + thisButton->w, thisButton->y + thisButton->h);
            if (thisButton->mouse_in) {
                if (!mouse_b & 1 && thisButton->state != MOUSE_CLICK) thisButton->state = MOUSE_ON;
                if (mouse_b & 1 && thisButton->state != MOUSE_CLICK) thisButton->state = MOUSE_ON;

                if (mouse.getMouseLeftClick() == 0) {
                    thisButton->state = MOUSE_CLICK;
                    return thisButton->ID;
                } else {
                    if (!mouse_b & 1) thisButton->state = MOUSE_ON;
                }
            } else thisButton->state = MOUSE_OUT;

        }

        thisButton = thisButton->next;
    }

    if (thisButton != NULL) return thisButton->ID;
    else return -1;
}

void GuiButton::drawButtonImage(BITMAP *bmp, short button_id) {
    BUTTON_MASK *thisButton = getButtonByID(button_id);

    short button_img = BUTTON_NORM;
    int temp_col2 = 150;
    if (thisButton->state == MOUSE_CLICK) {
        temp_col2 = 255;
        button_img = BUTTON_DOWN;
    }

    if (thisButton->state == MOUSE_ON) {
        temp_col2 = 255;
    }

    masked_stretch_blit((BITMAP*)resources.data[button_img].dat, bmp, 0, 0, 55, 18, thisButton->x, thisButton->y, thisButton->w, thisButton->h);
    textprintf_ex(bmp, font, thisButton->x+5, thisButton->y+5, makecol(temp_col2, temp_col2, temp_col2), -1, "%s", thisButton->label.c_str());
}

void GuiButton::drawButtons(BITMAP *bmp) {

    BUTTON_MASK *thisButton = firstButton;
    BUTTON_MASK *destroyedButton = NULL;

    while (thisButton != NULL) {
        if (thisButton->destroyed) {
            destroyedButton = thisButton;
            thisButton = thisButton->next;

            if (firstButton == destroyedButton) {
                firstButton = thisButton;
                if (thisButton != NULL) {
                    thisButton->previous = NULL;
                }
            } else {
                destroyedButton->previous->next=thisButton;
                if (thisButton != NULL) {
                    thisButton->previous=destroyedButton->previous;
                }
            }
            if (lastButton == destroyedButton) {
                lastButton = destroyedButton->previous;
            }
            delete destroyedButton;
        } else {
            if (thisButton->displayed) {
                drawButtonImage(bmp, thisButton->ID);
            }
            thisButton=thisButton->next;
        }
    }
}
