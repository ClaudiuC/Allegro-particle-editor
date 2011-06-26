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
*** \file    guitextfield.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the text field API.
******************************************************************************/

#include "guitextfield.h"

extern InputMouse mouse;
extern GuiResources resources;

GuiField::GuiField() {
    firstField = lastField = fieldAttributes = NULL;
    auto_increment_id = 0;
}

GuiField::~GuiField() {
    FIELD_MASK* thisField = firstField;
    FIELD_MASK* destroyedField = NULL;

    while (thisField != NULL) {
        destroyedField = thisField;
        thisField = thisField->next;
        delete destroyedField;
    }
    firstField = NULL;
    lastField = NULL;
}

FIELD_MASK *GuiField::getFieldByID(short field_id) {
    FIELD_MASK* thisField = firstField;
    FIELD_MASK* foundField = NULL;

    while (thisField != NULL) {
        if (thisField->ID != field_id) thisField = thisField->next;
        else {
            foundField = thisField;
            return foundField;
        }
    }
    return NULL;
}

void GuiField::addField(short x, short y, short w, short h, string label) {
    if (firstField==NULL) {
        firstField = new FIELD_MASK;
        lastField = firstField;
        lastField->next = NULL;
        lastField->previous = NULL;
    } else {
        lastField->next = new FIELD_MASK;
        lastField->next->previous = lastField;
        lastField = lastField->next;
        lastField->next = NULL;
    }
    lastField->x = x;
    lastField->y = y;
    lastField->w = w;
    lastField->h = h;
    lastField->label = label;
    lastField->state = FIELD_INACTIVE;

    lastField->edittext = "";
    lastField->iter = lastField->edittext.begin();
    lastField->caret = 0;
    lastField->insert = true;

    lastField->destroyed=false;
    lastField->displayed=true;
    lastField->mouse_in = false;

    lastField->ID = auto_increment_id;

    auto_increment_id++;

    fieldAttributes = lastField;
}

short GuiField::getLastFieldID() {
    return lastField->ID;
}

string GuiField::updateFields() {
    FIELD_MASK *thisField = firstField;

    while (thisField != NULL) {
        if (thisField->displayed) {
            thisField->mouse_in = mouse.getMouseFocus(thisField->x, thisField->y, thisField->x + thisField->w, thisField->y + thisField->h);
            if (thisField->mouse_in) {
                if (mouse.getMouseLeftClick() == 0) {
                    thisField->state = FIELD_ACTIVE;
                    if (thisField->edittext == "0") {
                        clearFieldText(thisField->ID);
                    }
                }
            }

            else {
                if (mouse_b & 1) thisField->state = FIELD_INACTIVE;
            }

            if (thisField->state == FIELD_ACTIVE) {
                if (keypressed() && thisField->displayed && thisField->state == FIELD_ACTIVE) {
                    int  newkey   = readkey();
                    char ASCII    = newkey & 0xff;
                    char scancode = newkey >> 8;

                    if (ASCII >= 32 && ASCII <= 126) {
                        if (thisField->caret < thisField->w/8) {
                            if (thisField->insert || thisField->iter == thisField->edittext.end())
                                thisField->iter = thisField->edittext.insert(thisField->iter, ASCII);
                            else
                                thisField->edittext.replace(thisField->caret, 1, 1, ASCII);

                            thisField->caret++;
                            thisField->iter++;
                        }
                    } else
                        switch (scancode) {
                        case KEY_DEL:
                            if (thisField->iter != thisField->edittext.end()) thisField->iter = thisField->edittext.erase(thisField->iter);
                            break;

                        case KEY_BACKSPACE:
                            if (thisField->iter != thisField->edittext.begin()) {
                                thisField->caret--;
                                thisField->iter--;
                                thisField->iter = thisField->edittext.erase(thisField->iter);
                            }
                            break;

                        case KEY_RIGHT:
                            if (thisField->iter != thisField->edittext.end())   thisField->caret++, thisField->iter++;
                            break;

                        case KEY_LEFT:
                            if (thisField->iter != thisField->edittext.begin()) thisField->caret--, thisField->iter--;
                            break;

                        case KEY_INSERT:
                            thisField->insert = !thisField->insert;
                            break;
                        case KEY_ENTER:
                            return thisField->edittext;

                        case KEY_TAB:
                            if (thisField->next != NULL && thisField->next->displayed == true) {
                                thisField->state = FIELD_INACTIVE;
                                thisField->next->state = FIELD_ACTIVE;
                                if (thisField->next->edittext == "0") {
                                    clearFieldText(thisField->next->ID);
                                }
                            } else {
                                thisField->state = FIELD_INACTIVE;
                                firstField->state = FIELD_ACTIVE;
                                if (firstField->edittext == "0") {
                                    clearFieldText(firstField->ID);
                                }
                            }
                            break;
                        default:

                            break;
                        }
                }
            }
        }
        thisField = thisField->next;
    }

    return "";
}

void GuiField::drawFieldImage(BITMAP *bmp, short field_id) {
    FIELD_MASK *thisField = getFieldByID(field_id);

    textprintf_ex(bmp, font, thisField->x-text_length(font, thisField->label.c_str())-5, thisField->y, makecol(180,180,180), -1, "%s", thisField->label.c_str());
    // rect(bmp, thisField->x-5, thisField->y-5, thisField->x + thisField->w+5, thisField->y + thisField->h+5, makecol(0, 0, 0));
    masked_stretch_blit((BITMAP*)resources.data[TEXT].dat, bmp, 0, 0, 100, 18, thisField->x-5, thisField->y - 5, thisField->w+10, thisField->h + 10);
    if (thisField->state==FIELD_ACTIVE) {
        if (thisField->insert) {
            vline(bmp, thisField->caret*8+thisField->x, thisField->y, thisField->y + thisField->h, makecol(180,180,180));
        } else {
            hline(bmp, thisField->caret*8+thisField->x, thisField->y+thisField->h, thisField->caret*8+thisField->x+text_length(font, "_"), makecol(180,180,180));
        }
    }
    textprintf_ex(bmp, font, thisField->x, thisField->y, makecol(180,180,180), -1, "%s", thisField->edittext.c_str());
}

void GuiField::drawFields(BITMAP *bmp) {

    FIELD_MASK* thisField = firstField;
    FIELD_MASK* destroyedField = NULL;

    while (thisField != NULL) {
        if (thisField->destroyed) {
            destroyedField = thisField;
            thisField = thisField->next;

            if (firstField == destroyedField) {
                firstField = thisField;
                if (thisField != NULL) {
                    thisField->previous = NULL;
                }
            } else {
                destroyedField->previous->next=thisField;
                if (thisField != NULL) {
                    thisField->previous=destroyedField->previous;
                }
            }
            if (lastField == destroyedField) {
                lastField = destroyedField->previous;
            }
            delete destroyedField;
        } else {
            if (thisField->displayed) {
                drawFieldImage(bmp, thisField->ID);
            }
            thisField=thisField->next;
        }
    }
}
