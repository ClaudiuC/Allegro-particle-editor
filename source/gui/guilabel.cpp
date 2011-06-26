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
*** \file    guilabel.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the label API.
******************************************************************************/

#include "guilabel.h"

GuiLabel::GuiLabel() {
    firstLabel = lastLabel = labelAttributes = NULL;
    auto_increment_id = 0;
}

GuiLabel::~GuiLabel() {
    LABEL_MASK *thisLabel = firstLabel;
    LABEL_MASK *destroyedLabel = NULL;

    while (thisLabel != NULL) {
        destroyedLabel = thisLabel;
        thisLabel = thisLabel->next;
        delete destroyedLabel;
    }
    firstLabel = NULL;
    lastLabel = NULL;
}

LABEL_MASK *GuiLabel::getLabelByID(short label_id) {

    LABEL_MASK *thisLabel = firstLabel;
    LABEL_MASK *foundLabel = NULL;

    while (thisLabel != NULL) {
        if (thisLabel->ID != label_id) thisLabel = thisLabel->next;
        else {
            foundLabel = thisLabel;
            return foundLabel;
        }
    }
    return NULL;
}

void GuiLabel::addLabel(short x, short y, int color, string label) {
    if (firstLabel==NULL) {
        firstLabel = new LABEL_MASK;
        lastLabel = firstLabel;
        lastLabel->next = NULL;
        lastLabel->previous = NULL;
    } else {
        lastLabel->next = new LABEL_MASK;
        lastLabel->next->previous = lastLabel;
        lastLabel = lastLabel->next;
        lastLabel->next = NULL;
    }

    lastLabel->x = x;
    lastLabel->y = y;
    lastLabel->w = text_length(font, label.c_str())+10;
    lastLabel->h = text_height(font)+10;
    lastLabel->color = color;
    lastLabel->label = label;
    lastLabel->displayed = true;
    lastLabel->destroyed=false;
    lastLabel->ID = auto_increment_id;

    auto_increment_id++;

    labelAttributes = lastLabel;
}

short GuiLabel::getLastLabelID() {
    return lastLabel->ID;
}

void GuiLabel::drawLabelImage(BITMAP *bmp, short Label_id) {
    LABEL_MASK *thisLabel = getLabelByID(Label_id);

    textprintf_ex(bmp, font, thisLabel->x+5, thisLabel->y+5, thisLabel->color, -1, "%s", thisLabel->label.c_str());
}

void GuiLabel::drawLabels(BITMAP *bmp) {

    LABEL_MASK *thisLabel = firstLabel;
    LABEL_MASK *destroyedLabel = NULL;

    while (thisLabel != NULL) {
        if (thisLabel->destroyed) {
            destroyedLabel = thisLabel;
            thisLabel = thisLabel->next;

            if (firstLabel == destroyedLabel) {
                firstLabel = thisLabel;
                if (thisLabel != NULL) {
                    thisLabel->previous = NULL;
                }
            } else {
                destroyedLabel->previous->next=thisLabel;
                if (thisLabel != NULL) {
                    thisLabel->previous=destroyedLabel->previous;
                }
            }
            if (lastLabel == destroyedLabel) {
                lastLabel = destroyedLabel->previous;
            }
            delete destroyedLabel;
        } else {
            if (thisLabel->displayed) {
                drawLabelImage(bmp, thisLabel->ID);
            }
            thisLabel=thisLabel->next;
        }
    }
}
