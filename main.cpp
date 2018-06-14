#include <stdio.h>
#include <math.h>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Maze.cpp"
#include "Ghost.cpp"
#include "Point.cpp"
#include "Pacman.cpp"
#include "Pellet.cpp"

double rx = 0, ry = 0, rz = 0;

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
    NormalPellet = new Pellet(3.0);
    PowerPellet = new Pellet(7.0);
    Labyrinth = new Maze(arq);
    Labyrinth->setPellets(NormalPellet, PowerPellet);
    GhoClyde = new Ghost(9*25, 11*25, 255, 165, 0, false); //clyde
    GhoPinky = new Ghost(11*25, 13.5*25, 255, 105, 180, false); //pinky
    GhoInky = new Ghost(11*25, 11.5*25, 0, 255, 255, false); //inky
    GhoBlinky = new Ghost(11*25, 9.5*25, 255, 0, 0, false); //blinky
    Pac = new Pacman(25, 25, 8);
}

void init() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix � a de proje��o
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-600, 600, -600, 600, -600, 600); //define uma proje��o ortogonal
    glPushMatrix();
}

void keyboardInt(unsigned char key, int x, int y){
    switch(key){
        case 'd':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_RIGHT)){
                    Pac->setDirection(MAZE_RIGHT);
                //Pac->walk();
            } 
            break;
        case 'a':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_LEFT)){
                    Pac->setDirection(MAZE_LEFT);
                //Pac->walk();
            } 
            break;
        case 'w':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_UP)){
                    Pac->setDirection(MAZE_UP);
                //Pac->walk();
            }
            break;
        case 's':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_DOWN)){
                    Pac->setDirection(MAZE_DOWN);
                //Pac->walk();
            } 
            break;
    }
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

void timerFunc(int value){
    bool canWalk = Labyrinth->canIncrease(Pac->getX(), Pac->getY(), Pac->getDirection());
    Pac->walk(canWalk);
    canWalk = Labyrinth->canIncrease(GhoClyde->getX(), GhoClyde->getY(), GhoClyde->getDirection());
    while(!GhoClyde->walk(canWalk)){
        canWalk = Labyrinth->canIncrease(GhoClyde->getX(), GhoClyde->getY(), GhoClyde->getDirection());
    }
    glutPostRedisplay();
    glutTimerFunc(200, timerFunc, value);
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
    Labyrinth->pelletCollision(Pac);
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
    glutTimerFunc(200, timerFunc, 0);
	init();
	glutMainLoop();
	return 0;
}
