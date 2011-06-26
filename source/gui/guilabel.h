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
*** \file    guilabel.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the label API.
***
*** This code provides the API used to manage GUI labels using a doubly linked
*** list.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef GUILABEL_H
#define GUILABEL_H

#include <allegro.h>

#include <string>

using namespace std;

typedef struct LABEL_MASK {
    short x, y;
    short w, h;

    string label;
    bool displayed;
    bool destroyed;
    int color;

    short ID;

    LABEL_MASK *next;
    LABEL_MASK *previous;
} LABEL_MASK;

class GuiLabel {
public:
    GuiLabel();
    ~GuiLabel();

    LABEL_MASK *getLabelByID(short label_id);
    void addLabel(short x, short y, int color, string label);

    short getLastLabelID();
    short updateLabels();
    void drawLabelImage(BITMAP *bmp, short label_id);
    void drawLabels(BITMAP *bmp);

    void setLabelText(short label_id, string label) {
        getLabelByID(label_id)->label = label;
    }
    void hideAllLabels() {
        LABEL_MASK *thisLabel = firstLabel;

        while (thisLabel != NULL) {
            thisLabel->displayed = false;
            thisLabel = thisLabel->next;
        }
    }
    void showLabel(short ID) {
        getLabelByID(ID)->displayed = true;
    }
    void hideLabel(short ID) {
        getLabelByID(ID)->displayed = false;
    }
    short getLabelPosX(short label_id)   {
        return getLabelByID(label_id)->x;
    }
    short getLabelPosY(short label_id)   {
        return getLabelByID(label_id)->y;
    }
    short getLabelSizeW(short label_id)  {
        return getLabelByID(label_id)->w;
    }
    short getLabelSizeH(short label_id)  {
        return getLabelByID(label_id)->h;
    }

    string getLabelText(short label_id) {
        return getLabelByID(label_id)->label;
    }
    short getLabelID(short label_id)     {
        return getLabelByID(label_id)->ID;
    }
private:
    LABEL_MASK *labelAttributes;

    LABEL_MASK *firstLabel;
    LABEL_MASK *lastLabel;

    short auto_increment_id;
};

#endif // GUILABEL_H
