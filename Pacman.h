#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Point.h"

class Pacman : public Point {
    private:
        float radius;
        GLUquadricObj *object;
    public:
        Pacman(float valX, float valY, float valRadius);
        void draw();
        void setRadius(float radius);
        float getRadius();
};

#endif
