#ifndef _PELLET_H_
#define _PELLET_H_

#include <GL/glut.h>
#include "Point.h"
#define NOT_A_PELLET 0
#define POWER_PELLET 1
#define NORMAL_PELLET 2

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