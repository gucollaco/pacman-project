#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Point.h"
#include "Color.h"

class Ghost : public Point{
private:
    Color color;
    bool isReversed;
    GLUquadricObj *object;
public:
    Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
    Ghost(int valX, int valY, Color valColor, bool rev);
    Ghost(Point valPosition, int valR, int valG, int valB, bool rev);
    Ghost(Point valPosition, Color valColor, bool rev);

    void draw();
};

#endif