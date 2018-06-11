#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Point.h"

class Pacman : public Point {
    private:
        GLUquadricObj *object;
    public:
        Pacman(float valX, float valY);
        void draw();
};

#endif
