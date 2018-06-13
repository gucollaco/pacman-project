#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/glut.h>
#include "Point.h"

class Ghost : public Point{
private:
    int r, g, b;
    bool isReversed;
    GLUquadricObj *object;
public:
    Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
    void draw();
};

#endif