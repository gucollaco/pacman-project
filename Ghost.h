#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/glut.h>
#include "Point.h"
#include <random>
#include <ctime>
#define GHOST_UP 1
#define GHOST_DOWN 2
#define GHOST_LEFT 3
#define GHOST_RIGHT 4

class Ghost : public Point{
private:
    int r, g, b;
    int direction;
    bool isReversed;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
    GLUquadricObj *object;
public:
    Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
    void draw();
    bool walk(int canWalk);
    int getDirection();
    void setDirection(int direction);
};

#endif