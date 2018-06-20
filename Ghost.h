#ifndef _GHOST_H_
#define _GHOST_H_

#include <GL/glut.h>
#include "Point.h"
#include "Color.h"

#include "Maze.h"
#include <random>
#include <ctime>
#define GHOST_UP MAZE_UP
#define GHOST_LEFT MAZE_LEFT
#define GHOST_DOWN MAZE_DOWN
#define GHOST_RIGHT MAZE_RIGHT

class Ghost : public Point{
private:
    Color color;
    int direction;

    bool isReversed;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> dist;
    GLUquadricObj *object;
public:
    Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
    Ghost(int valX, int valY, Color valColor, bool rev);
    Ghost(Point valPosition, int valR, int valG, int valB, bool rev);
    Ghost(Point valPosition, Color valColor, bool rev);

    void draw();
    bool walk(Maze *maze);
    int getDirection();
    bool getReversed();
    void setReversed(bool reversed);
    void setDirection(int direction);
    int collision(float x, float y, float r);
};

std::mt19937 Ghost::mt = std::mt19937(time(NULL));
std::uniform_int_distribution<int> Ghost::dist = std::uniform_int_distribution<int>(1, 4);
#endif