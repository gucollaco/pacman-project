#ifndef _MAZE_H_
#define _MAZE_H_

#include "Pellet.h"
#define MAZE_UP 1
#define MAZE_DOWN 3
#define MAZE_LEFT 2
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
    int pelletCollision(float x, float y, int r);
    bool canIncrease(float x, float y, int direcao);
    void show();
    void draw();
};

#endif