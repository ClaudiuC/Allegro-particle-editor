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

#ifndef PARTICLEEDITOR_H
#define PARTICLEEDITOR_H

#include "..\gui\guimain.h"
#include "particleemitter.h"
#include <math.h>

#define FORCE_VOID          0
#define FORCE_START         1
#define FORCE_AREA_DONE     2
#define FORCE_LOW_AXE_DONE  3
#define FORCE_HIGH_AXE_DONE 4
#define FORCE_DONE          5

typedef struct PARTICLE_REFRESH {
    int r_rand, g_rand, b_rand;
    int r, g, b;
} PARTICLE_REFRESH;

typedef struct EMITTER {
    short pos_x, pos_y;

    PARTICLE settings;
    PARTICLE_REFRESH refresh;
    //FORCE_ALTER *force;
} EMITTER;

typedef struct FORCE_ELEMENT {
    int x, y, w, h;

    int low_axe_x, low_axe_y;
    int high_axe_x, high_axe_y;

    double dx, dy;
    int rx, ry;

    int origin_x, origin_y;
} FORCE_ELEMENT;

typedef struct FORCE_ALTER {
    double dx, dy;
    int rx, ry;
} FORCE_ALTER;

void createParticlesFromEmitter(PARTICLE *p, int em_x, int em_y);
void drawCustomParticle(BITMAP *bmp, PARTICLE p);

class ParticleEditor {
public:
    ParticleEditor();
    ~ParticleEditor();

    void initEditor();
    void resetEmitter();

    void drawGrid(BITMAP *bmp);
    void drawSelector(BITMAP *bmp);

    void getEmitterSettings(int x, int y);
    long int getNewParticleColor(int x, int y);

    void playParticles(BITMAP *bmp);
    void editorEngine();

    void renderEditor(BITMAP *bmp);
    void freeEditor();

    EMITTER getEmitter(int x, int y) {
        return emitter[x][y];
    }

    void printEmitter(BITMAP *bmp, int x, int y);
protected:
private:
    BITMAP *editor;

    EMITTER **emitter;
    FORCE_ELEMENT **force;

    ParticleEmitter particle;

    short emitter_index;

    short forceAddStep;
    int currentForce_x, currentForce_y;
};

#endif // PARTICLEEDITOR_H
