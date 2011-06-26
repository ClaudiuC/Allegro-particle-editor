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
*** \file    guiframe.cpp
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Source file for the frame API.
******************************************************************************/

#include "guiframe.h"

extern InputMouse mouse;
extern GuiResources resources;

GuiFrame::GuiFrame() {
    firstFrame = lastFrame = frameAttributes = NULL;
    auto_increment_id = 0;
}

GuiFrame::~GuiFrame() {

    FRAME_MASK* thisFrame = firstFrame;
    FRAME_MASK* destroyedFrame = NULL;

    while (thisFrame != NULL) {
        destroyedFrame = thisFrame;
        thisFrame = thisFrame->next;
        delete destroyedFrame;
    }
    firstFrame = NULL;
    lastFrame = NULL;
}

FRAME_MASK *GuiFrame::getFrameByID(short frame_id) {
    FRAME_MASK* thisFrame = firstFrame;
    FRAME_MASK* foundFrame = NULL;

    while (thisFrame != NULL) {
        if (thisFrame->ID != frame_id) thisFrame = thisFrame->next;
        else {
            foundFrame = thisFrame;
            return foundFrame;
        }
    }
    return NULL;
}

void GuiFrame::addFrame(short x, short y, short w, short h, string label) {
    if (firstFrame==NULL) {
        firstFrame = new FRAME_MASK;
        lastFrame = firstFrame;
        lastFrame->next = NULL;
        lastFrame->previous = NULL;
    } else {
        lastFrame->next = new FRAME_MASK;
        lastFrame->next->previous = lastFrame;
        lastFrame = lastFrame->next;
        lastFrame->next = NULL;
    }
    lastFrame->x = x;
    lastFrame->y = y;
    lastFrame->w = w;
    lastFrame->h = h;
    lastFrame->label = label;
    lastFrame->state = FRAME_INACTIVE;

    lastFrame->destroyed=false;
    lastFrame->mouse_in = false;

    lastFrame->ID = auto_increment_id;

    auto_increment_id++;

    frameAttributes = lastFrame;
}

short GuiFrame::getLastFrameID() {
    return lastFrame->ID;
}

short GuiFrame::updateFrames() {
    return 0;
}

void GuiFrame::drawFrameImage(BITMAP *bmp, short frame_id) {
    FRAME_MASK *thisFrame = getFrameByID(frame_id);

    string title;
    if (thisFrame->state == FRAME_ACTIVE) title = thisFrame->label;
    else title = thisFrame->label;

    masked_stretch_blit((BITMAP*)resources.data[TOP].dat, bmp, 0, 0, 116, 4, thisFrame->x, thisFrame->y, thisFrame->w, 4);
    masked_stretch_blit((BITMAP*)resources.data[BOTTOM].dat, bmp, 0, 0, 116, 4, thisFrame->x, thisFrame->y+thisFrame->h-4, thisFrame->w, 4);
    masked_stretch_blit((BITMAP*)resources.data[LEFT].dat, bmp, 0, 0, 4, 120, thisFrame->x, thisFrame->y, 4, thisFrame->h);
    masked_stretch_blit((BITMAP*)resources.data[RIGHT].dat, bmp, 0, 0, 4, 120, thisFrame->x + thisFrame->w-4, thisFrame->y, 4, thisFrame->h);

    masked_blit((BITMAP*)resources.data[UP_LEFT].dat, bmp, 0, 0, thisFrame->x, thisFrame->y, 5, 5);
    masked_blit((BITMAP*)resources.data[UP_RIGHT].dat, bmp, 0, 0, thisFrame->x+thisFrame->w-5, thisFrame->y, 5, 5);
    masked_blit((BITMAP*)resources.data[DOWN_LEFT].dat, bmp, 0, 0, thisFrame->x, thisFrame->y+thisFrame->h-5, 5, 5);
    masked_blit((BITMAP*)resources.data[DOWN_RIGHT].dat, bmp, 0, 0, thisFrame->x+thisFrame->w-5, thisFrame->y+thisFrame->h-5, 5, 5);
    masked_stretch_blit((BITMAP*)resources.data[BAR].dat, bmp, 0, 0, 285, 14, thisFrame->x+4, thisFrame->y+4, thisFrame->w-8, 16);
    /*
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(bmp, thisFrame->x+4, thisFrame->y+20, thisFrame->w-8, thisFrame->y+thisFrame->h-5, makecol(180,180,180));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
    */
    textprintf_ex(bmp, font, thisFrame->x+10, thisFrame->y+8, makecol(255, 255, 255), -1, "%s", title.c_str());
}

void GuiFrame::drawHorizontalSeparator(BITMAP* bmp, short x, short x2, short y) {
    masked_stretch_blit((BITMAP*)resources.data[BOTTOM].dat, bmp, 0, 0, 116, 4, x, y, x2-x, 4);
}

void GuiFrame::drawVerticalSeparator(BITMAP* bmp, short x, short y, short y2) {
    masked_stretch_blit((BITMAP*)resources.data[LEFT].dat, bmp, 0, 0, 4, 120, x, y, 4, y2-y);
}

void GuiFrame::drawFrames(BITMAP *bmp) {

    FRAME_MASK* thisFrame = firstFrame;
    FRAME_MASK* destroyedFrame = NULL;

    while (thisFrame != NULL) {
        if (thisFrame->destroyed) {
            destroyedFrame = thisFrame;
            thisFrame = thisFrame->next;

            if (firstFrame == destroyedFrame) {
                firstFrame = thisFrame;
                if (thisFrame != NULL) {
                    thisFrame->previous = NULL;
                }
            } else {
                destroyedFrame->previous->next=thisFrame;
                if (thisFrame != NULL) {
                    thisFrame->previous=destroyedFrame->previous;
                }
            }
            if (lastFrame == destroyedFrame) {
                lastFrame = destroyedFrame->previous;
            }
            delete destroyedFrame;
        } else {
            if (thisFrame->state != FRAME_HIDDEN) {
                drawFrameImage(bmp, thisFrame->ID);
            }
            thisFrame=thisFrame->next;
        }
    }
}
