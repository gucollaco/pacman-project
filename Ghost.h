#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/glut.h>
#include "Point.h"
#include <random>
#include <ctime>
#define GHOST_UP 1
#define GHOST_LEFT 2
#define GHOST_DOWN 3
#define GHOST_RIGHT 4

class Ghost : public Point{
private:
    int r, g, b;
    int direction;
    bool isReversed;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> dist;
    GLUquadricObj *object;
public:
    Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
    void draw();
    bool walk(int canWalk);
    int getDirection();
    bool getReversed();
    void setReversed(bool reversed);
    void setDirection(int direction);
    int collision(float x, float y, float r);
};

std::mt19937 Ghost::mt = std::mt19937(time(NULL));
std::uniform_int_distribution<int> Ghost::dist = std::uniform_int_distribution<int>(1, 4);
#endif