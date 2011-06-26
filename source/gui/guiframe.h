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
*** \file    guiframe.h
*** \author  Gilcescu-Ceia Claudiu, hazardous.dev@gmail.com
*** \brief   Header file for the frame API.
***
*** This code provides the API used to manage GUI frames using a doubly linked
*** list.
***
*** \note This code uses the following libraries:
***   -# Allegro 4.2.2, http://www.allegro.cc/
******************************************************************************/

#ifndef GUIFRAME_H
#define GUIFRAME_H

#include <string>
#include "guiresources.h"
#include "..\input\inputmouse.h"

using namespace std;

#define FRAME_INACTIVE 0
#define FRAME_ACTIVE   1
#define FRAME_HIDDEN   2

typedef struct FRAME_MASK {
    short x, y;
    short w, h;

    string label;
    bool destroyed;

    short state;
    short ID;

    bool mouse_in;

    FRAME_MASK *next;
    FRAME_MASK *previous;
} FRAME_MASK;

class GuiFrame {
public:
    GuiFrame();
    ~GuiFrame();

    void addFrame(short x, short y, short w, short h, string label);
    short getLastFrameID();
    FRAME_MASK* getFrameByID(short frame_id);
    short updateFrames();
    void drawFrameImage(BITMAP *bmp, short frame_id);
    void drawFrames(BITMAP *bmp);

    void drawHorizontalSeparator(BITMAP* bmp, short x, short x2, short y);
    void drawVerticalSeparator(BITMAP* bmp, short x, short y, short y2);
    void setFrameLabel(short frame_id, string newlabel) {
        getFrameByID(frame_id)->label = newlabel;
    }
    void appendFrameVars(short frame_id, string vars) {
        getFrameByID(frame_id)->label += vars;
    }
    short getFramePosX(short frame_id)   {
        return getFrameByID(frame_id)->x;
    }
    short getFramePosY(short frame_id)   {
        return getFrameByID(frame_id)->y;
    }
    short getFrameSizeW(short frame_id)  {
        return getFrameByID(frame_id)->w;
    }
    short getFrameSizeH(short frame_id)  {
        return getFrameByID(frame_id)->h;
    }

    string getFrameLabel(short frame_id) {
        return getFrameByID(frame_id)->label;
    }
    short getFrameState(short frame_id)  {
        return getFrameByID(frame_id)->state;
    }
    short getFrameID(short frame_id)     {
        return getFrameByID(frame_id)->ID;
    }

    bool getFrameMouseIn(short frame_id) {
        return getFrameByID(frame_id)->mouse_in;
    }
protected:
private:
    FRAME_MASK *frameAttributes;
    FRAME_MASK *firstFrame;
    FRAME_MASK *lastFrame;

    short auto_increment_id;
};

#endif // GUIFRAME_H
