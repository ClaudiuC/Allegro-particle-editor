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

#ifndef GUIMAIN_H
#define GUIMAIN_H


#include "..\input\inputmouse.h"
#include "..\utils\dataformat.h"
#include "..\engine\particleeditor.h"
#include "guibutton.h"
#include "guiframe.h"
#include "guicheckbox.h"
#include "guitextfield.h"
#include "guiresources.h"
#include "guilabel.h"
#include "fields.h"
#include "labels.h"


#define STATE_PARTICLE_EDIT    0
#define STATE_FORCE_EDIT       1
#define STATE_PARTICLE_PLACE   2
#define STATE_FORCE_PLACE      3
#define STATE_SIMULATE         4

#define BRUSH_NONE          -1
#define BRUSH_PARTICLE      0
#define BRUSH_FORCE         1

#define FRAME_MENU        9
#define FRAME_SIDEBAR     10
#define FRAME_WORKSPACE   11


typedef struct RAND_VALUE {
    double constant;
    double rand;
} RAND_VALUE;

typedef struct PARTICLE_SETTINGS {
    RAND_VALUE dx, dy;
    double rx, ry;
    RAND_VALUE life;
    double speed;
    RAND_VALUE r, g, b;
} PARTICLE_SETTINGS;

class GuiMain {
    friend class ParticleEditor;
public:
    GuiMain();
    ~GuiMain();

    void loadInterface();
    void updateInterface();
    void drawInterface(BITMAP *bmp);

    void fillParticleStruct();
    void sendParticleStruct(PARTICLE_SETTINGS *p);

    RAND_VALUE fillValue(string constant, string rand);

    void emptyParticleStruct();

    PARTICLE_SETTINGS returnEmptyParticle();

    PARTICLE_SETTINGS returnParticleSettings() {
        return particleSettings;
    }

    short getPanelState() {
        return panelState;
    }
    short getMouseFrame() {
        return mouse_frame;
    }
    int getMouseX() {
        return gui_x;
    }
    int getMouseY() {
        return gui_y;
    }

    bool isFieldActive() {
        if (field.getActiveField() == -1) return false;
        else return true;
    }

    bool getGrid() {
        return grid;
    }
    bool getPreview() {
        return preview;
    }

    short getBrush() {
        return brush;
    }
    void setBrush(short type) {
        brush = type;
    }

    bool getQuit() {
        return quit;
    }
    void externChangeFieldText(short id, string s) {
        field.setFieldText(id, s);
    }
    void clearInterface();
protected:
private:
    short panelState;
    bool grid, quit;
    short brush;
    bool preview;

    short gridDensity;

    short frameMain,
    frameSidebar,

    buttonParticles,
    buttonForces,
    buttonPlaceElement,
    buttonPreview,

    checkboxGrid,

    fieldSettings[30],
    statsLabels[15],

    labelParticles,
    labelForce,

    fieldSave,
    fieldLoad,
    fieldCreate,

    buttonSave,
    buttonLoad,
    buttonCreate;

    short mouse_frame;
    int gui_x, gui_y;

    GuiButton button;
    GuiFrame frame;
    GuiCheckbox checkbox;
    GuiField field;
    GuiLabel label;

    PARTICLE_SETTINGS particleSettings;
};
#endif // GUIMAIN_H
