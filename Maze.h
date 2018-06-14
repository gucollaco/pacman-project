#ifndef _MAZE_H_
#define _MAZE_H_

#include "Pellet.h"
#include "Pacman.h"
#define MAZE_UP PAC_UP
#define MAZE_DOWN PAC_DOWN
#define MAZE_LEFT PAC_LEFT
#define MAZE_RIGHT PAC_RIGHT

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
    bool canIncrease(float x, float y, int direcao);
    void show();
    void draw();
};

#endif