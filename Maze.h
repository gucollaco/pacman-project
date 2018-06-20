#ifndef _MAZE_H_
#define _MAZE_H_

#include "Pellet.h"
#include "Color.h"
#define MAZE_UP 1
#define MAZE_DOWN 3
#define MAZE_LEFT 2
#define MAZE_RIGHT 4

#define MATRIX_COMMON_PELLET 0
#define MATRIX_TURNING_PELLET 1
#define MATRIX_POWER_PELLET '2'
#define MATRIX_TOP_WALL '3'
#define MATRIX_BOTTOM_WALL '4'
#define MATRIX_LEFT_WALL '5'
#define MATRIX_RIGHT_WALL '6'
#define MATRIX_TELLEPORT_TILE '7'
#define MATRIX_TURNING_POINT '8'
#define MATRIX_BLANK_SPACE '9'
#define MATRIX_TOP_LEFT_WALL 'a'
#define MATRIX_TOP_RIGHT_WALL 'b'
#define MATRIX_BOTTOM_LEFT_WALL 'c'
#define MATRIX_BOTTOM_RIGHT_WALL 'd'
#define MATRIX_INNER_TOP_LEFT_WALL 'e'
#define MATRIX_INNER_TOP_RIGHT_WALL 'f'
#define MATRIX_INNER_BOTTOM_LEFT_WALL 'g'
#define MATRIX_INNER_BOTTOM_RIGHT_WALL 'h'

#define WALL_COLOR BLUE
#define PELLET_COLOR SAND
#define POWER_PELLET_COLOR BROWN_BEIGE

class Maze{
private:
    int **value;     // S�o atributos
    int pellets;
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
    int getNumberOfPellets();
    void show();
    void draw();
};

#endif