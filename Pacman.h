#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <GL/glut.h>
#include "Point.h"
#define PAC_UP 1
#define PAC_DOWN 2
#define PAC_LEFT 3
#define PAC_RIGHT 4

class Pacman : public Point {
    private:
        float radius;
        int direction;
        GLUquadricObj *object;
    public:
        Pacman(float valX, float valY, float valRadius);
        void draw();
        void setRadius(float radius);
        float getRadius();
        void setDirection(int direction);
        int getDirection();
        void walk(int canWalk);
};

#endif
