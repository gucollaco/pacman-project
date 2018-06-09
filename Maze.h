#ifndef _MAZE_H_
#define _MAZE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <malloc.h>
#include "Pellet.h"


class Maze{
private:
    int **value;     // S�o atributos
    int lin, col;
    Pellet *normal, *power;
public:
    Maze(char *path);
    Maze(int lines, int columns);
    void alloc(int lines, int columns);
    void setValue(int line, int column, int value);
    int getValue(int line, int column);
    void setPellets(Pellet *normal, Pellet *power);
    void colisaoPellet(float x, float y, float r);
    void show();
    void draw();
};

#endif