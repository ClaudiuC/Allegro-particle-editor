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
*** \file    guicheckbox.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the checkbox API.
***
*** This code provides the API used to manage GUI checkboxes using a doubly linked
*** list.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef GUICHECKBOX_H
#define GUICHECKBOX_H

#include <string>
#include "..\input\inputmouse.h"
#include "guiresources.h"
#include "guiData.h"

using namespace std;

#define CHECKBOX_CHECKED     0
#define CHECKBOX_UNCHECKED   1
#define CHECKBOX_HIDDEN      2

#define CHECKBOX_SIZE 25

typedef struct CHECKBOX_MASK {
    short x, y;
    short w, h;

    string label;
    bool destroyed;
    bool displayed;

    short state;
    short ID;
    short groupID;

    bool mouse_in;

    CHECKBOX_MASK *next;
    CHECKBOX_MASK *previous;
} CHECKBOX_MASK;

class GuiCheckbox {
public:
    GuiCheckbox();
    ~GuiCheckbox();

    CHECKBOX_MASK* getCheckboxByID(short checkbox_id);
    void addCheckbox(short x, short y, short w, short h, string label, short groupID, short checked);
    short getLastCheckboxID();
    void updateCheckboxes();
    void drawCheckboxImage(BITMAP *bmp, short checkbox_id);
    void drawCheckboxes(BITMAP *bmp);

    void hideAllCheckboxes() {
        CHECKBOX_MASK *thisCheckbox = firstCheckbox;

        while (thisCheckbox != NULL) {
            thisCheckbox->displayed = false;
            thisCheckbox = thisCheckbox->next;
        }
    }
    void showCheckbox(short ID) {
        getCheckboxByID(ID)->displayed = true;
    }
    void hideChecbox(short ID) {
        getCheckboxByID(ID)->displayed = false;
    }
    void setCheckboxState(short ID, short state) {
        getCheckboxByID(ID)->state = state;
    }
    short getCheckboxPosX(short checkbox_id)   {
        return getCheckboxByID(checkbox_id)->x;
    }
    short getCheckboxPosY(short checkbox_id)   {
        return getCheckboxByID(checkbox_id)->y;
    }
    short getCheckboxSizeW(short checkbox_id)   {
        return getCheckboxByID(checkbox_id)->w;
    }
    short getCheckboxSizeH(short checkbox_id)   {
        return getCheckboxByID(checkbox_id)->h;
    }
    string getCheckboxLabel(short checkbox_id) {
        return getCheckboxByID(checkbox_id)->label;
    }
    bool getCheckboxState(short checkbox_id)  {
        switch (getCheckboxByID(checkbox_id)->state) {
        case CHECKBOX_CHECKED:
            return true;
        case CHECKBOX_UNCHECKED:
            return false;
        default:
            return false;
        }
    }
    short getCheckboxID(short checkbox_id)     {
        return getCheckboxByID(checkbox_id)->ID;
    }
    short getCheckboxGroupID(short checkbox_id)     {
        return getCheckboxByID(checkbox_id)->ID;
    }

    bool getCheckboxMouseIn(short checkbox_id) {
        return getCheckboxByID(checkbox_id)->mouse_in;
    }
protected:
private:
    CHECKBOX_MASK *checkboxAttributes;
    CHECKBOX_MASK *firstCheckbox;
    CHECKBOX_MASK *lastCheckbox;

    short auto_increment_id;
};

#endif // GUICHECKBOX_H
