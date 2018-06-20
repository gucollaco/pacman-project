#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Point.h"
#include "Maze.h"
#define PAC_UP MAZE_UP
#define PAC_LEFT MAZE_LEFT
#define PAC_DOWN MAZE_DOWN
#define PAC_RIGHT MAZE_RIGHT

class Pacman : public Point {
    private:
        float radius;
        int direction;
        float animation;
        float inc;
        GLUquadricObj *object;
    public:
        Pacman(float valX, float valY, float valRadius);
        void draw();
        void setRadius(float radius);
        float getRadius();
        void setDirection(int direction);
        int getDirection();
        void walk(Maze *maze);
};

#endif
