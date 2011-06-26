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

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <math.h>
#include <allegro.h>
#include <iostream>

using namespace std;

#define RAIN_PARTICLE  0
#define SNOW_PARTICLE1 1
#define SNOW_PARTICLE2 2
#define SMOKE_PARTICLE 3
#define SOME_PARTICLE  4

typedef struct FORCE {
    double dx, dy;
    int x, y, w, h;
    int rx, ry;

    bool done;
} FORCE;

typedef struct PARTICLE {
    double x,y,             //!< Position on screen
    dx,dy,                  //!< Speed and direction of movement
    rx,ry,                  //!< Movement randomness
    tx,ty;                  //!< Last particle position
    int color,              //!< Particle color
    type;                   //!< Particle type
    double life;            //!< Particle life
    double speed;

    FORCE force;
    PARTICLE *next;  //!< Pointer to the next particle, a simple linked list should do
    PARTICLE *previous;  //!< Pointer to the next particle, a simple linked list should do
} PARTICLE;

class ParticleEmitter {
    friend class EditorMain;
public:
    ParticleEmitter();
    ~ParticleEmitter();

    void createParticles(double x, double y, double dx, double dy, double rx, double ry, double life, int color, double speed, short type);
    void createParticles(double x, double y, short type, void(*proc)(PARTICLE *p));
    void createParticles(double x, double y, short type, int em_x, int em_y, void(*proc)(PARTICLE *p, int em_x, int em_y));

    void addForce(int x, int y, int w, int h, double dx, double dy, int rx, int ry);
    short updateParticles();

    void drawParticle(BITMAP *bmp, PARTICLE *p);
    void drawParticles(BITMAP *bmp);

    void drawParticles(BITMAP *bmp, void(*proc)(BITMAP *bmp, PARTICLE p));
    void clearParticles();

    int getParticleCount() {
        return particle_index;
    }
protected:
private:
    PARTICLE *particles;
    PARTICLE *firstParticle;
    PARTICLE *lastParticle;

    struct FORCE force;

    short particle_index;
    short force_index;
};

#endif // PARTICLEEMITTER_H
