#ifndef _MAZE_H_
#define _MAZE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <malloc.h>
#include "Pellet.h"
#include "Pacman.h"
#define MAZE_UP 1
#define MAZE_DOWN 2
#define MAZE_LEFT 3
#define MAZE_RIGHT 4

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
    void pelletCollision(Pacman *Pac);
    bool canIncrease(Pacman *Pac, int direcao);
    void show();
    void draw();
};


#endif