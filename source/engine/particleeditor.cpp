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

#include "particleeditor.h"

extern GuiMain gui;
extern InputMouse mouse;
extern ParticleEditor editor;

ParticleEditor::ParticleEditor() {
    forceAddStep = FORCE_VOID;
    currentForce_x = currentForce_y = -1;
}

ParticleEditor::~ParticleEditor() {
    delete[] emitter;
    delete[] force;
}

void ParticleEditor::initEditor() {
    editor = create_bitmap(768, SCREEN_H);
    clear_to_color(editor, makecol(0,0,0));

    emitter = new EMITTER*[((768-gui.gridDensity)/gui.gridDensity)];
    for (short x = 0; x < ((768)/gui.gridDensity); x++) {
        emitter[x] = new EMITTER[((SCREEN_H)/gui.gridDensity)];
    }
    for (short x = 0; x < (768)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {
            emitter[x][y].pos_x = -1;
            emitter[x][y].pos_y = -1;
            //emitter[x][y].force = new FORCE_ALTER;
        }
    }

    emitter_index=0;

    force = new FORCE_ELEMENT*[((768-gui.gridDensity)/gui.gridDensity)];
    for (short x = 0; x < ((768)/gui.gridDensity); x++) {
        force[x] = new FORCE_ELEMENT[((SCREEN_H)/gui.gridDensity)];
    }

    for (short x = 0; x < (768)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {
            force[x][y].x = -1;
            force[x][y].dx = -1;
            force[x][y].rx = -1;

            force[x][y].y = -1;
            force[x][y].dy = -1;
            force[x][y].ry = -1;

            force[x][y].w = -1;
            force[x][y].h = -1;

            force[x][y].origin_x = -1;
            force[x][y].origin_y = -1;

            force[x][y].low_axe_x = -1;
            force[x][y].low_axe_y = -1;

            force[x][y].high_axe_x = -1;
            force[x][y].high_axe_y = -1;
        }
    }
}

void ParticleEditor::resetEmitter() {
    if (emitter) delete[] emitter;
    if (force) delete[] force;

    emitter = new EMITTER*[((768)/gui.gridDensity)];
    for (short x = 0; x < ((768)/gui.gridDensity); x++) {
        emitter[x] = new EMITTER[((SCREEN_H)/gui.gridDensity)];
    }

    emitter_index = 0;
    for (short x = 0; x < (768)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {
            emitter[x][y].pos_x = -1;
            emitter[x][y].pos_y = -1;
        }
    }

    force = new FORCE_ELEMENT*[((768-gui.gridDensity)/gui.gridDensity)];
    for (short x = 0; x < ((768)/gui.gridDensity); x++) {
        force[x] = new FORCE_ELEMENT[((SCREEN_H)/gui.gridDensity)];
    }

    for (short x = 0; x < (768)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {
            force[x][y].x = -1;
            force[x][y].dx = -1;
            force[x][y].rx = -1;

            force[x][y].y = -1;
            force[x][y].dy = -1;
            force[x][y].ry = -1;

            force[x][y].w = -1;
            force[x][y].h = -1;

            force[x][y].origin_x = -1;
            force[x][y].origin_y = -1;

            force[x][y].low_axe_x = -1;
            force[x][y].low_axe_y = -1;

            force[x][y].high_axe_x = -1;
            force[x][y].high_axe_y = -1;
        }
    }
}

void ParticleEditor::drawSelector(BITMAP *bmp) {
    if (gui.gui_x > -1 && gui.gui_y > -1) {
        if (gui.getBrush() == BRUSH_PARTICLE) {
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            circlefill(bmp, gui.gui_x-1, gui.gui_y, 4, makecol(255,0,0));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
            circle(bmp, gui.gui_x-1, gui.gui_y, 4, makecol(255,0,0));
        }
        if (gui.getBrush() == BRUSH_FORCE) {
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            circlefill(bmp, gui.gui_x-1, gui.gui_y, 4, makecol(0,255,0));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
            circle(bmp, gui.gui_x-1, gui.gui_y, 4, makecol(0,255,0));
        }
        if (gui.getBrush() == BRUSH_NONE) {
            mouse.setCursor(CURSOR);
        }
    }
}

void ParticleEditor::drawGrid(BITMAP *bmp) {

    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_trans_blender(128, 128, 128, 128);

    for (short x = gui.gridDensity; x < 768; x++) {
        for (short y = gui.gridDensity; y < SCREEN_H-gui.gridDensity; ) {
            if (x+gui.gridDensity <= 768 && y > 32) {
                rect (bmp, x, y, x+gui.gridDensity, y+gui.gridDensity, makecol(128, 128, 128));
            }
            y += gui.gridDensity;
        }
        x += gui.gridDensity;
    }

    for (short x = 0; x < (768)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {
            if (emitter[x][y].pos_x > 0 && emitter[x][y].pos_y > 0) {
                circlefill(bmp, emitter[x][y].pos_x, emitter[x][y].pos_y, 4, makecol(0,0,255));
            }
            if (force[x][y].x > 0 && force[x][y].y > 0) {
                rectfill(bmp, force[x][y].x-3, force[x][y].y-3, force[x][y].x+3, force[x][y].y+3, makecol(0,255,0));
            }
            if (force[x][y].w > 0 && force[x][y].h > 0) {
                rectfill(bmp, force[x][y].x-3+force[x][y].w, force[x][y].y-3+force[x][y].h, force[x][y].x+3+force[x][y].w, force[x][y].y+3+force[x][y].h, makecol(0,255,0));

                rectfill(bmp, force[x][y].x-3+force[x][y].w, force[x][y].y-3, force[x][y].x+3+force[x][y].w, force[x][y].y+3, makecol(0,255,0));
                rectfill(bmp, force[x][y].x-3, force[x][y].y-3+force[x][y].h, force[x][y].x+3, force[x][y].y+3+force[x][y].h, makecol(0,255,0));

                rect(bmp, force[x][y].x, force[x][y].y, force[x][y].x+force[x][y].w, force[x][y].y+force[x][y].h, makecol(0,255,0));
            }

            if (force[x][y].origin_x > 0 && force[x][y].origin_y > 0) {
                circlefill(bmp, force[x][y].origin_x, force[x][y].origin_y, 4, makecol(0, 255, 0));
            }

            if (force[x][y].low_axe_x > 0 && force[x][y].low_axe_y > 0) {
                rectfill(bmp, force[x][y].low_axe_x-2, force[x][y].low_axe_y-2, force[x][y].low_axe_x+2, force[x][y].low_axe_y+2, makecol(0,255,0));
                line(bmp, force[x][y].low_axe_x, force[x][y].low_axe_y, force[x][y].origin_x, force[x][y].origin_y, makecol(0, 255, 0));
            }

            if (force[x][y].high_axe_x > 0 && force[x][y].high_axe_y > 0) {
                rectfill(bmp, force[x][y].high_axe_x-2, force[x][y].high_axe_y-2, force[x][y].high_axe_x+2, force[x][y].high_axe_y+2, makecol(0,255,0));
                line(bmp, force[x][y].high_axe_x, force[x][y].high_axe_y, force[x][y].origin_x, force[x][y].origin_y, makecol(0, 255, 0));
                // low angle
                float low_angle = asin(sin(abs(force[x][y].low_axe_y - force[x][y].origin_y)/sqrt(abs(force[x][y].low_axe_y - force[x][y].origin_y)^2+abs(force[x][y].low_axe_x-force[x][y].origin_x)^2)))*(256/360);
                // high angle
                float high_angle = asin(sin(abs(force[x][y].high_axe_y - force[x][y].origin_y)/sqrt(abs(force[x][y].high_axe_y - force[x][y].origin_y)^2+abs(force[x][y].high_axe_x-force[x][y].origin_x)^2)))*(256/360);

                arc(bmp, force[x][y].origin_x, force[x][y].origin_y, ftofix(low_angle), ftofix(high_angle), force[x][y].w/2, makecol(0,255,0));
            }



        }
    }

    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
}

void createParticlesFromEmitter(PARTICLE *p, int em_x, int em_y) {
    p->color = editor.getNewParticleColor(em_x, em_y);

    p->dx = editor.getEmitter(em_x, em_y).settings.dx;
    p->dy = editor.getEmitter(em_x, em_y).settings.dy;

    p->rx = editor.getEmitter(em_x, em_y).settings.rx;
    p->ry = editor.getEmitter(em_x, em_y).settings.ry;

    if (p->rx < 1) p->rx = 0;
    if (p->ry < 1) p->ry = 0;

    p->speed = editor.getEmitter(em_x, em_y).settings.speed;
    if (p->speed < 0) {
        p->speed = 1;
        gui.externChangeFieldText(PARTICLE_SPEED, "1");
    }

    p->life = editor.getEmitter(em_x, em_y).settings.life;
    if (p->life < 0) {
        p->life = 100;
        gui.externChangeFieldText(PARTICLE_LIFE, "100");
    }
}

void drawCustomParticle(BITMAP *bmp, PARTICLE p) {
    circlefill(bmp, (int)p.x, (int)p.y, 1, p.color);
    //line(bmp, (int)p.x, (int)p.y, (int)p.tx, (int)p.ty, p.color);
    /*
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    short aux = 0;

    if (p.life < 200) aux = 1;
    if (p.life < 100) aux = 2;
    if (p.life < 50) aux = 3;

    set_trans_blender(p.color, p.color, p.color, 10-aux);
    circlefill(bmp, (int)p.x, (int)p.y, 1, p.color);


    set_trans_blender(p.color, p.color, p.color, 8-aux);

    circlefill(bmp, (int)p.x, (int)p.y, 2, p.color);


    set_trans_blender(p.color, p.color, p.color, 7-aux);

    circlefill(bmp, (int)p.x, (int)p.y, 12-aux*3, p.color);


    set_trans_blender(p.color, p.color, p.color, 6-aux);

    circlefill(bmp, (int)p.x, (int)p.y, 15-aux*3, p.color);


    set_trans_blender(p.color, p.color, p.color, 5-aux);

    circlefill(bmp, (int)p.x, (int)p.y, 18-aux*3, p.color);

    set_trans_blender(p.color, p.color, p.color, 4-aux);
    circlefill(bmp, (int)p.x, (int)p.y, 20-aux*3, p.color);

    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
    */
}


void ParticleEditor::playParticles(BITMAP *bmp) {
    bool play = false;

    for (short x = 0; x < (768-gui.gridDensity)/gui.gridDensity; x++) {
        for (short y = 0; y < (SCREEN_H)/gui.gridDensity; y++) {

            if (emitter[x][y].pos_y > 0 && emitter[x][y].pos_x > 0) {
                particle.createParticles(emitter[x][y].pos_x, emitter[x][y].pos_y, 3, x, y, &createParticlesFromEmitter);
                play = true;
            }

            if (force[x][y].x > 0 && force[x][y].y > 0) {
                int w, h;

                if (force[x][y].low_axe_x > force[x][y].high_axe_x) {
                    w = force[x][y].low_axe_x;
                } else w = force[x][y].high_axe_x;

                if (force[x][y].low_axe_y > force[x][y].high_axe_y) {
                    h = force[x][y].low_axe_y;
                } else h = force[x][y].high_axe_y;

                particle.addForce(force[x][y].origin_x, force[x][y].origin_y, w, h, force[x][y].dx, force[x][y].dy, force[x][y].rx, force[x][y].ry);
            }

        }
    }
    if (play) {
        particle.updateParticles();
        particle.drawParticles(bmp, &drawCustomParticle);
    } else particle.clearParticles();
}

void ParticleEditor::printEmitter(BITMAP *bmp, int x, int y) {
    cout << "Color" << emitter[x][y].settings.color << endl;
    cout << "DX" << emitter[x][y].settings.dx << endl;
    cout << "DY" << emitter[x][y].settings.dy << endl;
    cout << "RX" << emitter[x][y].settings.rx << endl;
    cout << "RY" << emitter[x][y].settings.ry << endl;
    cout << "Life" << emitter[x][y].settings.life << endl;
    cout << "Speed" << emitter[x][y].settings.speed << endl;
}

void ParticleEditor::getEmitterSettings(int x, int y) {

    int r_rand = (int)gui.returnParticleSettings().r.rand;
    if (r_rand == 0) r_rand = 1;

    int g_rand = (int)gui.returnParticleSettings().g.rand;
    if (g_rand == 0) g_rand = 1;

    int b_rand = (int)gui.returnParticleSettings().b.rand;
    if (b_rand == 0) b_rand = 1;

    int r, g, b;
    if (gui.returnParticleSettings().r.constant < 256 && gui.returnParticleSettings().r.constant > -1 &&
            gui.returnParticleSettings().g.constant < 256 && gui.returnParticleSettings().g.constant > -1 &&
            gui.returnParticleSettings().b.constant < 256 && gui.returnParticleSettings().b.constant > -1) {
        r = (int)gui.returnParticleSettings().r.constant;
        g = (int)gui.returnParticleSettings().g.constant;
        b = (int)gui.returnParticleSettings().b.constant;

    } else {
        r = g = b = 0;
    }

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    double rx = gui.returnParticleSettings().rx;
    if (rx < 1) rx = 0;

    double ry = gui.returnParticleSettings().ry;
    if (ry < 1) ry = 0;


    double dx_rand = gui.returnParticleSettings().dx.rand;
    if (dx_rand < 1) dx_rand = 1;

    double dy_rand = gui.returnParticleSettings().dy.rand;
    if (dy_rand < 1) dy_rand = 1;

    double life_rand = gui.returnParticleSettings().life.rand;
    if (life_rand < 1) life_rand = 1;

    double life = gui.returnParticleSettings().life.constant;
    if (life < 1) {
        life = 100;
        gui.externChangeFieldText(PARTICLE_LIFE, "100");
    }

    double speed = gui.returnParticleSettings().speed;
    if (speed < 1) speed = 1;

    emitter[x][y].refresh.r_rand = r_rand;
    emitter[x][y].refresh.g_rand = g_rand;
    emitter[x][y].refresh.b_rand = b_rand;

    emitter[x][y].refresh.r = r;
    emitter[x][y].refresh.g = g;
    emitter[x][y].refresh.b = b;

    emitter[x][y].settings.color = makecol(r+rand()%r_rand,g+rand()%r_rand,b+rand()%r_rand);
    emitter[x][y].settings.dx = gui.returnParticleSettings().dx.constant + rand()%(int)dx_rand;
    emitter[x][y].settings.dy = gui.returnParticleSettings().dy.constant + rand()%(int)dy_rand;
    emitter[x][y].settings.rx = rx;
    emitter[x][y].settings.ry = ry;
    emitter[x][y].settings.life = life + rand()%(int)life_rand;
    emitter[x][y].settings.speed = speed;

}

long int ParticleEditor::getNewParticleColor(int x, int y) {
    return makecol(emitter[x][y].refresh.r+rand()%emitter[x][y].refresh.r_rand,
                   emitter[x][y].refresh.g+rand()%emitter[x][y].refresh.g_rand,
                   emitter[x][y].refresh.b+rand()%emitter[x][y].refresh.b_rand);
}

void ParticleEditor::editorEngine() {
    drawGrid(editor);
    drawSelector(editor);

    int x = gui.gui_x/gui.gridDensity;
    int y = gui.gui_y/gui.gridDensity;

    if (gui.getMouseFrame() == FRAME_WORKSPACE && gui.getBrush() == BRUSH_PARTICLE) {
        if (mouse.getMouseLeftClick() == 1) {
            if (emitter[x][y].pos_x == -1 &&
                    emitter[x][y].pos_y == -1) {

                emitter[x][y].pos_x = gui.gui_x;
                emitter[x][y].pos_y = gui.gui_y;

                gui.fillParticleStruct();
                getEmitterSettings(x, y);

                printEmitter(editor, x, y);
                emitter_index++;
            } else {
                emitter[x][y].pos_x = -1;
                emitter[x][y].pos_y = -1;

                emitter_index--;
            }
        }
    }

    //if (emitter_index == 0) particle.clearParticles();

    if (gui.getMouseFrame() == FRAME_WORKSPACE && gui.getBrush() == BRUSH_FORCE) {
        if (mouse.getMouseLeftClick() == 1) {
            if (force[x][y].x == gui.gui_x && force[x][y].y == gui.gui_y) {
                forceAddStep = FORCE_VOID;

                if (currentForce_x != -1) x = currentForce_x;
                if (currentForce_y != -1) y = currentForce_y;

                currentForce_x = -1;
                currentForce_y = -1;

                force[x][y].x = -1;
                force[x][y].dx = -1;
                force[x][y].rx = -1;

                force[x][y].y = -1;
                force[x][y].dy = -1;
                force[x][y].ry = -1;

                force[x][y].w = -1;
                force[x][y].h = -1;

                force[x][y].origin_x = -1;
                force[x][y].origin_y = -1;

                force[x][y].low_axe_x = -1;
                force[x][y].low_axe_y = -1;

                force[x][y].high_axe_x = -1;
                force[x][y].high_axe_y = -1;
            } else {
                switch (forceAddStep) {
                case FORCE_VOID: {
                    currentForce_x = x;
                    currentForce_y = y;

                    force[x][y].x = gui.gui_x;
                    force[x][y].y = gui.gui_y;
                    forceAddStep++;
                    break;
                }
                case FORCE_START: {
                    if (gui.gui_x > force[currentForce_x][currentForce_y].x && gui.gui_y > force[currentForce_x][currentForce_y].y) {
                        force[currentForce_x][currentForce_y].w = abs(force[currentForce_x][currentForce_y].x-gui.gui_x);
                        force[currentForce_x][currentForce_y].h = abs(force[currentForce_x][currentForce_y].y-gui.gui_y);

                        force[currentForce_x][currentForce_y].origin_x = force[currentForce_x][currentForce_y].x+force[currentForce_x][currentForce_y].w/2;
                        force[currentForce_x][currentForce_y].origin_y = force[currentForce_x][currentForce_y].y+force[currentForce_x][currentForce_y].h/2;
                        forceAddStep++;
                    }
                    break;
                }
                case FORCE_AREA_DONE: {
                    force[currentForce_x][currentForce_y].low_axe_x = gui.gui_x;
                    force[currentForce_x][currentForce_y].low_axe_y = gui.gui_y;
                    forceAddStep++;
                    break;
                }
                case FORCE_LOW_AXE_DONE: {
                    if (gui.gui_y != force[currentForce_x][currentForce_y].low_axe_y && gui.gui_x != force[currentForce_x][currentForce_y].low_axe_y) {
                        force[currentForce_x][currentForce_y].high_axe_x = gui.gui_x;
                        force[currentForce_x][currentForce_y].high_axe_y = gui.gui_y;

                        double hypotenuse;
                        hypotenuse = sqrt(abs(force[currentForce_x][currentForce_y].low_axe_y - force[currentForce_x][currentForce_y].high_axe_y)^2+
                                          abs(force[currentForce_x][currentForce_y].low_axe_x-force[currentForce_x][currentForce_y].high_axe_x)^2);
                        double axe_mid = hypotenuse/2;

                        force[currentForce_x][currentForce_x].dx = axe_mid/gui.gridDensity;
                        force[currentForce_x][currentForce_x].dy = axe_mid/gui.gridDensity;

                        force[currentForce_x][currentForce_x].rx = 20; //abs(force[currentForce_x][currentForce_y].low_axe_x-force[currentForce_x][currentForce_y].high_axe_x);
                        force[currentForce_x][currentForce_x].ry = 25; //abs(force[currentForce_x][currentForce_y].low_axe_y-force[currentForce_x][currentForce_y].high_axe_y);

                        forceAddStep = FORCE_VOID;
                        currentForce_x = -1;
                        currentForce_y = -1;
                    }
                    break;
                }
                }
            }
        }
    }

    //if (gui.getPanelState() == STATE_SIMULATE) {
    playParticles(editor);
    //}

    if (key[KEY_F5]) {
        for (short x = 0; x < (768-gui.gridDensity)/gui.gridDensity; x++) {
            for (short y = 0; y < (SCREEN_H-gui.gridDensity*2)/gui.gridDensity; y++) {
                std::cout << "emitter"<<x * y << " = " << emitter[x][y].pos_y <<endl;
            }
        }

    }
}

void ParticleEditor::renderEditor(BITMAP *bmp) {
    masked_blit(editor, bmp, 0, 0, 0, 0, 768, SCREEN_H);
    clear_to_color(editor, makecol(0,0,0));
}

void ParticleEditor::freeEditor() {
    destroy_bitmap(editor);
}
