#ifndef _PELLET_H_
#define _PELLET_H_

#include <GL/glut.h>
#include "Point.h"

class Pellet : public Point{
private:
    float radius;
    GLUquadricObj *object;
public:
    Pellet(float valRadius);
    float getRadius();
    void setRadius(float valRadius);
    void draw();
};

#endif