#include <stdio.h>
#include <math.h>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"

typedef struct Pos {
    float x;
    float y;
}Pos;

int inside2(float value){
    return static_cast<int>((value + 12.5) / 25);
}

double rx = 0, ry = 0, rz = 0;

Pos pontoTeste = {350, 285};

Maze *Labyrinth;
Pellet *NormalPellet;
Pellet *PowerPellet;
Ghost *GhoBlinky;
Ghost *GhoClyde;
Ghost *GhoInky;
Ghost *GhoPinky;
Pacman *Pac;

void initPacman(){
    char arq[] = "Matrix.txt";
    Pos posBlinky = {225, 285};
    Pos posClyde = {285, 335};
    Pos posInky = {285, 285};
    Pos posPinky = {285, 235};
    NormalPellet = new Pellet(3.0);
    PowerPellet = new Pellet(7.0);
    Labyrinth = new Maze(arq);
    Labyrinth->setPellets(NormalPellet, PowerPellet);
    GhoClyde = new Ghost(posClyde.x, posClyde.y, 255, 165, 0, false); //clyde
    GhoPinky = new Ghost(posPinky.x, posPinky.y, 255, 105, 180, false); //pinky
    GhoInky = new Ghost(posInky.x, posInky.y, 0, 255, 255, false); //inky
    GhoBlinky = new Ghost(posBlinky.x, posBlinky.y, 255, 0, 0, false); //blinky*/
    Pac = new Pacman(350, 170);
}

void init(){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix � a de proje��o
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-600, 600, -600, 600, -600, 600); //define uma proje��o ortogonal
    glPushMatrix();
}

/*int inside(float value){
    float res = value + 12.5;
    res = res/25;
    return res;
}*/

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int canIncrease(Maze *maze, float x, float y, int direcao){
    int l = inside2(x);
    int c = inside2(y);
    int v1, v2, v3;
    if(direcao == UP){
        v1 = maze->getValue(l-1, c+1);
        v2 = maze->getValue(l, c+1);
        v3 = maze->getValue(l+1, c+1);
        if( c < inside2(y+7.5) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside2(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside2(x-7.25) )
                return 0;
        }
    }
    if(direcao == DOWN){
        v1 = maze->getValue(l-1, c-1);
        v2 = maze->getValue(l, c-1);
        v3 = maze->getValue(l+1, c-1);
        if( c > inside2(y-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside2(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside2(x-7.25) )
                return 0;
        }
    }
    if(direcao == LEFT){
        v1 = maze->getValue(l-1, c-1);
        v2 = maze->getValue(l-1, c);
        v3 = maze->getValue(l-1, c+1);
        if( l > inside2(x-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside2(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside2(y-7.25) )
                return 0;
        }
    }
    if(direcao == RIGHT){
        v1 = maze->getValue(l+1, c-1);
        v2 = maze->getValue(l+1, c);
        v3 = maze->getValue(l+1, c+1);
        if( l < inside2(x+7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside2(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside2(y-7.25) )
                return 0;
        }
    }
    return 1;
}

void keyboardInt(unsigned char key, int x, int y){
    switch(key){
        case 'd':
            /*if(canIncrease(Mat, posPac.x, posPac.y, RIGHT))*/ pontoTeste.x += 2.5;
            break;
        case 'a':
            /*if(canIncrease(Mat, posPac.x, posPac.y, LEFT))*/ pontoTeste.x -= 2.5;
            break;
        case 'w':
            /*if(canIncrease(Mat, posPac.x, posPac.y, UP))*/ pontoTeste.y += 2.5;
            break;
        case 's':
            /*if(canIncrease(Mat, posPac.x, posPac.y, DOWN))*/ pontoTeste.y -= 2.5;
            break;
    }
    printf("%lf %lf\n", pontoTeste.x, pontoTeste.y);
    glutPostRedisplay();
}

void specialInt(int key, int x, int y){
	switch(key){
        case GLUT_KEY_UP:
            rx += 10;
            break;
        case GLUT_KEY_DOWN:
            rx -= 10;
            break;
        case GLUT_KEY_LEFT:
            rz -= 10;
            break;
        case GLUT_KEY_RIGHT:
            rz += 10;
            break;
    }
    glutPostRedisplay();
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glColor3ub(0,0,255);
    glPopMatrix();
    glPushMatrix();
    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);
    glRotatef(rz, 0, 0, 1);
    glTranslated(-240, -240, 0);
    Labyrinth->colisaoPellet(pontoTeste.x, pontoTeste.y, 8);
    Pac->setPoint(pontoTeste.x, pontoTeste.y);
    Pac->draw();

    Labyrinth->draw();
    GhoClyde->draw();
    GhoPinky->draw();
    GhoInky->draw();
    GhoBlinky->draw();

    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(700, 600);
	glutCreateWindow("Pacman - Project");

    initPacman();
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialInt);
    glutKeyboardFunc(keyboardInt);
	init();
	glutMainLoop();
	return 0;
}
