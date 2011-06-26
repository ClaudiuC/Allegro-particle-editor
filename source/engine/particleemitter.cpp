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

#include "particleemitter.h"

extern volatile int particle_timer;

ParticleEmitter::ParticleEmitter() {

    firstParticle = lastParticle = particles = NULL;
    particle_index = 0;
    force_index = 0;
}

ParticleEmitter::~ParticleEmitter() {
    PARTICLE *thisParticle = firstParticle;
    PARTICLE *destroyedParticle = NULL;

    while (thisParticle != NULL) {
        destroyedParticle = thisParticle;
        thisParticle = thisParticle->next;
        delete destroyedParticle;
    }
    firstParticle = NULL;
    lastParticle = NULL;
}

void ParticleEmitter::createParticles(double x, double y, double dx, double dy, double rx, double ry, double life, int color, double speed, short type) {
    if (firstParticle==NULL) {
        firstParticle = new PARTICLE;
        lastParticle = firstParticle;
        lastParticle->next = NULL;
        lastParticle->previous = NULL;
    } else {
        lastParticle->next = new PARTICLE;
        lastParticle->next->previous = lastParticle;
        lastParticle = lastParticle->next;
        lastParticle->next = NULL;
    }


    lastParticle->x = x;
    lastParticle->y = y;


    lastParticle->dx = dx;
    lastParticle->dy = dy;

    lastParticle->rx = rx;
    lastParticle->ry = ry;

    lastParticle->life = life;

    lastParticle->color = color;

    lastParticle->speed = speed;
    lastParticle->type = type;

    particle_index++;

    particles = lastParticle;

}


void ParticleEmitter::createParticles(double x, double y, short type, void(*proc)(PARTICLE *p)) {
    if (firstParticle==NULL) {
        firstParticle = new PARTICLE;
        lastParticle = firstParticle;
        lastParticle->next = NULL;
        lastParticle->previous = NULL;
    } else {
        lastParticle->next = new PARTICLE;
        lastParticle->next->previous = lastParticle;
        lastParticle = lastParticle->next;
        lastParticle->next = NULL;
    }


    lastParticle->x = x;
    lastParticle->y = y;

    particle_index++;

    lastParticle->type = type;
    proc(lastParticle);
    particles = lastParticle;
}

void ParticleEmitter::createParticles(double x, double y, short type, int em_x, int em_y, void(*proc)(PARTICLE *p, int em_x, int em_y)) {
    if (firstParticle==NULL) {
        firstParticle = new PARTICLE;
        lastParticle = firstParticle;
        lastParticle->next = NULL;
        lastParticle->previous = NULL;
    } else {
        lastParticle->next = new PARTICLE;
        lastParticle->next->previous = lastParticle;
        lastParticle = lastParticle->next;
        lastParticle->next = NULL;
    }


    lastParticle->x = x;
    lastParticle->y = y;

    lastParticle->force.x = lastParticle->force.y = lastParticle->force.w = lastParticle->force.h = 0;
    lastParticle->force.dx = lastParticle->force.dy = lastParticle->force.ry = lastParticle->force.rx = 0;

    particle_index++;

    lastParticle->type = type;
    proc(lastParticle, em_x, em_y);
    particles = lastParticle;
}

void ParticleEmitter::addForce(int x, int y, int w, int h, double dx, double dy, int rx, int ry) {
    PARTICLE *thisParticle = firstParticle;

    while (thisParticle != NULL) {

        thisParticle->force.x = x;
        thisParticle->force.y = y;

        thisParticle->force.w = w;
        thisParticle->force.h = h;

        thisParticle->force.dx = dx;
        thisParticle->force.dy = dy;

        thisParticle->force.rx = rx;
        thisParticle->force.ry = ry;

        thisParticle = thisParticle->next;
    }
    // return 0;
}

short ParticleEmitter::updateParticles() {
    PARTICLE *thisParticle = firstParticle;

    while (thisParticle != NULL) {

        thisParticle->tx = thisParticle->x;
        thisParticle->ty = thisParticle->y;

        thisParticle->x += thisParticle->dx;
        thisParticle->y += thisParticle->dy;

        if (thisParticle->rx>0) thisParticle->x += rand() % (int)(thisParticle->rx*2) - thisParticle->rx;
        if (thisParticle->ry>0) thisParticle->y += rand() % (int)(thisParticle->ry*2) - thisParticle->ry;

        if (thisParticle->x > thisParticle->force.x && thisParticle->x < thisParticle->force.x+thisParticle->force.w &&
                thisParticle->y > thisParticle->force.y && thisParticle->y < thisParticle->force.y+thisParticle->force.h) {

            thisParticle->dx = thisParticle->force.dx;
            thisParticle->dy = thisParticle->force.dy;

            thisParticle->rx = thisParticle->force.rx;
            thisParticle->ry = thisParticle->force.ry;
        }
        if (thisParticle->life > thisParticle->speed) thisParticle->life -= thisParticle->speed;
        else thisParticle->life = 0;

        thisParticle = thisParticle->next;
    }
    return 0;
}

void ParticleEmitter::drawParticle(BITMAP *bmp, PARTICLE *p) {
    switch (p->type) {
    case RAIN_PARTICLE:
        line(bmp, (int)p->x, (int)p->y, (int)p->tx, (int)p->ty, p->color);
        break;

    case SNOW_PARTICLE1:
        putpixel(bmp, (int)p->x, (int)p->y, p->color);
        break;

    case SNOW_PARTICLE2:
        putpixel(bmp, (int)p->x, (int)p->y, p->color);
        putpixel(bmp, (int)p->x-1, (int)p->y, p->color);
        putpixel(bmp, (int)p->x+1, (int)p->y, p->color);
        putpixel(bmp, (int)p->x, (int)p->y-1, p->color);
        putpixel(bmp, (int)p->x, (int)p->y+1, p->color);
        break;

    case SMOKE_PARTICLE: {

        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        short aux = 0;

        if (p->life < 40) aux = 1;
        if (p->life < 20) aux = 2;
        if (p->life < 5) aux = 3;

        set_trans_blender(p->color, p->color, p->color, 10-aux);
        circlefill(bmp, (int)p->x, (int)p->y, 1, p->color);


        set_trans_blender(p->color, p->color, p->color, 8-aux);

        circlefill(bmp, (int)p->x, (int)p->y, 2, p->color);


        set_trans_blender(p->color, p->color, p->color, 6-aux);

        circlefill(bmp, (int)p->x, (int)p->y, 12, p->color);


        set_trans_blender(p->color, p->color, p->color, 5-aux);

        circlefill(bmp, (int)p->x, (int)p->y, 15, p->color);


        set_trans_blender(p->color, p->color, p->color, 4-aux);

        circlefill(bmp, (int)p->x, (int)p->y, 18, p->color);

        set_trans_blender(p->color, p->color, p->color, 3-aux);
        circlefill(bmp, (int)p->x, (int)p->y, 20, p->color);

        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
        set_trans_blender(128, 128, 128, 128);

        break;
    }
    }
}

void ParticleEmitter::drawParticles(BITMAP *bmp, void(*proc)(BITMAP *bmp, PARTICLE p)) {
    PARTICLE *thisParticle = lastParticle;
    PARTICLE *destroyedParticle = NULL;

    while (thisParticle != NULL) {
        if (thisParticle->life <= 0) {
            destroyedParticle = thisParticle;
            thisParticle = thisParticle->next;

            if (firstParticle == destroyedParticle) {
                firstParticle = thisParticle;
                if (thisParticle != NULL) {
                    thisParticle->previous = NULL;
                }
            } else {
                destroyedParticle->previous->next=thisParticle;
                if (thisParticle != NULL) {
                    thisParticle->previous=destroyedParticle->previous;
                }
            }
            if (lastParticle == destroyedParticle) {
                lastParticle = destroyedParticle->previous;
            }
            delete destroyedParticle;
            particle_index--;
        } else {
            proc(bmp, *thisParticle);
        }
        thisParticle=thisParticle->previous;
    }
}

void ParticleEmitter::drawParticles(BITMAP *bmp) {

    PARTICLE *thisParticle = lastParticle;
    PARTICLE *destroyedParticle = NULL;

    while (thisParticle != NULL) {
        if (thisParticle->life <= 0) {
            destroyedParticle = thisParticle;
            thisParticle = thisParticle->next;

            if (firstParticle == destroyedParticle) {
                firstParticle = thisParticle;
                if (thisParticle != NULL) {
                    thisParticle->previous = NULL;
                }
            } else {
                destroyedParticle->previous->next=thisParticle;
                if (thisParticle != NULL) {
                    thisParticle->previous=destroyedParticle->previous;
                }
            }
            if (lastParticle == destroyedParticle) {
                lastParticle = destroyedParticle->previous;
            }
            delete destroyedParticle;
            particle_index--;
        } else {
            drawParticle(bmp, thisParticle);
        }
        thisParticle=thisParticle->previous;
    }
}

void ParticleEmitter::clearParticles() {

    PARTICLE *thisParticle = firstParticle;

    while (thisParticle != NULL) {
        thisParticle->life = 0;

        thisParticle=thisParticle->next;

    }
}
