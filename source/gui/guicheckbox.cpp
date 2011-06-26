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
*** \file    guicheckbox.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the checkbox API.
******************************************************************************/

#include "guicheckbox.h"

extern InputMouse mouse;
extern GuiResources resources;

GuiCheckbox::GuiCheckbox() {
    firstCheckbox = lastCheckbox = checkboxAttributes = NULL;
    auto_increment_id = 0;
}

GuiCheckbox::~GuiCheckbox() {
    CHECKBOX_MASK* thisCheckbox = firstCheckbox;
    CHECKBOX_MASK* destroyedCheckbox = NULL;

    while (thisCheckbox != NULL) {
        destroyedCheckbox = thisCheckbox;
        thisCheckbox = thisCheckbox->next;
        delete destroyedCheckbox;
    }
    firstCheckbox = NULL;
    lastCheckbox = NULL;
}

CHECKBOX_MASK *GuiCheckbox::getCheckboxByID(short Checkbox_id) {
    CHECKBOX_MASK* thisCheckbox = firstCheckbox;
    CHECKBOX_MASK* foundCheckbox = NULL;

    while (thisCheckbox != NULL) {
        if (thisCheckbox->ID != Checkbox_id) thisCheckbox = thisCheckbox->next;
        else {
            foundCheckbox = thisCheckbox;
            return foundCheckbox;
        }
    }
    return NULL;
}

void GuiCheckbox::addCheckbox(short x, short y, short w, short h, string label, short groupID, short checked) {
    if (firstCheckbox==NULL) {
        firstCheckbox = new CHECKBOX_MASK;
        lastCheckbox = firstCheckbox;
        lastCheckbox->next = NULL;
        lastCheckbox->previous = NULL;
    } else {
        lastCheckbox->next = new CHECKBOX_MASK;
        lastCheckbox->next->previous = lastCheckbox;
        lastCheckbox = lastCheckbox->next;
        lastCheckbox->next = NULL;
    }
    lastCheckbox->x = x;
    lastCheckbox->y = y;
    lastCheckbox->w = w;
    lastCheckbox->h = h;

    lastCheckbox->label = label;
    lastCheckbox->state = checked;
    lastCheckbox->groupID = groupID;
    lastCheckbox->destroyed=false;
    lastCheckbox->displayed=true;
    lastCheckbox->mouse_in = false;

    lastCheckbox->ID = auto_increment_id;

    auto_increment_id++;

    checkboxAttributes = lastCheckbox;
}

short GuiCheckbox::getLastCheckboxID() {
    return lastCheckbox->ID;
}

void GuiCheckbox::updateCheckboxes() {

    CHECKBOX_MASK* thisCheckbox = firstCheckbox;

    while (thisCheckbox != NULL) {
        if (thisCheckbox->displayed) {
            thisCheckbox->mouse_in = mouse.getMouseFocus(thisCheckbox->x, thisCheckbox->y, thisCheckbox->x + thisCheckbox->w, thisCheckbox->y + thisCheckbox->h);

            if (thisCheckbox->mouse_in) {
                if (mouse.getMouseLeftClick() == 0) {
                    if (thisCheckbox->state == CHECKBOX_UNCHECKED) {
                        thisCheckbox->state = CHECKBOX_CHECKED;
                    } else {
                        thisCheckbox->state = CHECKBOX_UNCHECKED;
                    }
                }
            }
        }

        thisCheckbox = thisCheckbox->next;
    }
}

void GuiCheckbox::drawCheckboxImage(BITMAP *bmp, short checkbox_id) {
    CHECKBOX_MASK *thisCheckbox = getCheckboxByID(checkbox_id);

    /*
    int col;
    if (thisCheckbox->state == CHECKBOX_CHECKED) col = makecol(128, 128, 128);
    else col = makecol(255, 255, 255);

    rect(bmp, thisCheckbox->x, thisCheckbox->y, thisCheckbox->x + thisCheckbox->w, thisCheckbox->y + thisCheckbox->h, makecol(0, 0, 0));
    rectfill(bmp, thisCheckbox->x+1, thisCheckbox->y+1, thisCheckbox->x + thisCheckbox->w - 1, thisCheckbox->y + thisCheckbox->h - 1, makecol(col, col, col));
    */
    if (thisCheckbox->state == CHECKBOX_CHECKED) {
        masked_stretch_blit((BITMAP*)resources.data[CHECKED].dat, bmp, 0, 0, 20, 18, thisCheckbox->x, thisCheckbox->y - thisCheckbox->h/4, thisCheckbox->w, thisCheckbox->h);
    } else masked_stretch_blit((BITMAP*)resources.data[UNCHECKED].dat, bmp, 0, 0, 20, 18, thisCheckbox->x, thisCheckbox->y - thisCheckbox->h/4, thisCheckbox->w, thisCheckbox->h);
    textprintf_ex(bmp, font, thisCheckbox->x - text_length(font, thisCheckbox->label.c_str()) - 5, thisCheckbox->y + text_height(font)/2, makecol(0, 0, 0), -1, "%s", thisCheckbox->label.c_str());

}

void GuiCheckbox::drawCheckboxes(BITMAP *bmp) {

    CHECKBOX_MASK* thisCheckbox = firstCheckbox;
    CHECKBOX_MASK* destroyedCheckbox = NULL;

    while (thisCheckbox != NULL) {
        if (thisCheckbox->destroyed) {
            destroyedCheckbox = thisCheckbox;
            thisCheckbox = thisCheckbox->next;

            if (firstCheckbox == destroyedCheckbox) {
                firstCheckbox = thisCheckbox;
                if (thisCheckbox != NULL) {
                    thisCheckbox->previous = NULL;
                }
            } else {
                destroyedCheckbox->previous->next=thisCheckbox;
                if (thisCheckbox != NULL) {
                    thisCheckbox->previous=destroyedCheckbox->previous;
                }
            }
            if (lastCheckbox == destroyedCheckbox) {
                lastCheckbox = destroyedCheckbox->previous;
            }
            delete destroyedCheckbox;
        } else {
            if (thisCheckbox->displayed) {
                drawCheckboxImage(bmp, thisCheckbox->ID);
            }
            thisCheckbox=thisCheckbox->next;
        }
    }
}
