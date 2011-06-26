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
*** \file    guitextfield.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the text field API.
***
*** This code provides the API used to manage GUI text fields using a doubly linked
*** list.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef GUITEXTFIELD_H
#define GUITEXTFIELD_H

#include <allegro.h>

#include <string>
#include "..\input\inputmouse.h"
#include "guiData.h"
#include "guiresources.h"

using namespace std;

#define FIELD_ACTIVE   0
#define FIELD_INACTIVE 1
#define FIELD_LOCKED   2
#define FIELD_HIDDEN   3

typedef struct FIELD_MASK {
    short x, y;
    short w, h;

    string label;
    bool destroyed;
    bool displayed;

    string  edittext;
    string::iterator iter;
    int     caret;
    bool    insert;

    short state;
    short ID;

    bool mouse_in;

    FIELD_MASK *next;
    FIELD_MASK *previous;
} FIELD_MASK;

class GuiField {
public:
    GuiField();
    ~GuiField();

    void addField(short x, short y, short w, short h, string label);
    short getLastFieldID();
    FIELD_MASK* getFieldByID(short field_id);
    string updateFields();
    void drawFieldImage(BITMAP *bmp, short field_id);
    void drawFields(BITMAP *bmp);

    void setAllFieldDefault(string text) {
        FIELD_MASK *thisField = firstField;

        while (thisField != NULL) {
            thisField->edittext = text;
            thisField->iter = thisField->edittext.end();
            thisField->caret = thisField->edittext.length();

            thisField = thisField->next;
        }
    }
    void setFieldDefault(short ID, string text) {
        getFieldByID(ID)->edittext = text;
    }
    short getActiveField() {
        FIELD_MASK *thisField = firstField;

        while (thisField != NULL) {
            if (thisField->state == FIELD_ACTIVE) return thisField->ID;
            thisField = thisField->next;
        }
        return -1;
    }
    void hideAllFields() {
        FIELD_MASK *thisField = firstField;

        while (thisField != NULL) {
            thisField->displayed = false;
            thisField = thisField->next;
        }
    }
    void showField(short ID) {
        getFieldByID(ID)->displayed = true;
    }
    void hideField(short ID) {
        getFieldByID(ID)->displayed = false;
    }
    void setFieldText(short field_id, string text) {
        getFieldByID(field_id)->edittext = text;
        getFieldByID(field_id)->iter = getFieldByID(field_id)->edittext.end();
        getFieldByID(field_id)->caret = 8*text.length();
        // getFieldByID(field_id)->state = FIELD_ACTIVE;
    }
    void clearFieldText(short field_id) {
        getFieldByID(field_id)->edittext = "";
        getFieldByID(field_id)->iter = getFieldByID(field_id)->edittext.begin();
        getFieldByID(field_id)->caret = 0;
        // getFieldByID(field_id)->state = FIELD_ACTIVE;
    }
    string getFieldText(short field_id) {
        return getFieldByID(field_id)->edittext;
    }
    short getFieldPosX(short field_id)   {
        return getFieldByID(field_id)->x;
    }
    short getFieldPosY(short field_id)   {
        return getFieldByID(field_id)->y;
    }
    short getFieldSizeW(short field_id)  {
        return getFieldByID(field_id)->w;
    }
    short getFieldSizeH(short field_id)  {
        return getFieldByID(field_id)->h;
    }

    string getFieldLabel(short field_id) {
        return getFieldByID(field_id)->label;
    }
    short getFieldState(short field_id)  {
        return getFieldByID(field_id)->state;
    }
    short getFieldID(short field_id)     {
        return getFieldByID(field_id)->ID;
    }

    bool getFieldMouseIn(short field_id) {
        return getFieldByID(field_id)->mouse_in;
    }
protected:
private:
    FIELD_MASK *fieldAttributes;
    FIELD_MASK *firstField;
    FIELD_MASK *lastField;

    short auto_increment_id;
};

#endif // GUITEXTFIELD_H
