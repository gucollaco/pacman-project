#include <stdio.h>
#include <math.h>
#include <list>
#include <ctime>
#include <sstream>
#include <windows.h>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Random.h"
#include "glh.h"
#include "Maze.cpp"
#include "Ghost.cpp"
#include "Point.cpp"
#include "Pacman.cpp"
#include "Pellet.cpp"
#include "glh.cpp"
#include "Random.cpp"
#include "Color.cpp"

int vida = 3;
double rx = 0, ry = 0, rz = 0;
float zoom = 120;
time_t tempo = 0;
Maze *Labyrinth;

Pellet *NormalPellet;
Pellet *PowerPellet;

Ghost *GhoBlinky;
Ghost *GhoClyde;
Ghost *GhoInky;
Ghost *GhoPinky;

std::list<Ghost*> Ghosts;
Pacman *Pac;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 3.0f, 7.0f, 7.0f, 0.0f };

const int FRAME_RATE = 50;

void initPacman(){
    char arq[] = "Matrix.txt";

    NormalPellet = new Pellet(3.0);
    PowerPellet = new Pellet(6.0);

    Labyrinth = new Maze(arq);
    Labyrinth->show();
    Labyrinth->setPellets(NormalPellet, PowerPellet);

    GhoClyde = new Ghost(5*25, 1*25, Color(LIGHT_PINK), false); //clyde
    GhoPinky = new Ghost(11*25, 13*25, Color(ORANGE), false); //pinky
    GhoInky = new Ghost(11*25, 11*25, Color(CYAN), false); //inky
    GhoBlinky = new Ghost(11*25, 11*25, Color(RED), false); //blinky

    Ghosts.push_back(GhoClyde);
    Ghosts.push_back(GhoPinky);
    Ghosts.push_back(GhoInky);
    Ghosts.push_back(GhoBlinky);

    Pac = new Pacman(23*25, 13.5*25, 16);

    Pac->setSpeed(6.25);
    for(Ghost* g : Ghosts) g->setSpeed(6.25);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix � a de proje��o
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom); //define uma proje��o ortogonal
    glPushMatrix();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    Random::seed(1);
}

bool key_pressed(int key) {
   return (GetAsyncKeyState(key) & 0x8000 != 0);
}

#define VK_KEY_A 0x41
#define VK_KEY_D 0x44
#define VK_KEY_S 0x53
#define VK_KEY_W 0x57

void testKeys(){
    if(key_pressed(VK_KEY_D)){
        if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_RIGHT)){
            Pac->setDirection(MAZE_RIGHT);
        } 
    }
    if(key_pressed(VK_KEY_A)){
        if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_LEFT)){
            Pac->setDirection(MAZE_LEFT);
        }
    }
    if(key_pressed(VK_KEY_W)){
        if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_UP)){
            Pac->setDirection(MAZE_UP);
        }
    }
    if(key_pressed(VK_KEY_S)){
        if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_DOWN)){
            Pac->setDirection(MAZE_DOWN);
        }
    }
}

void keyboardInt(unsigned char key, int x, int y){
    switch(key){
        case 'D':
        case 'd':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_RIGHT)){
                Pac->setDirection(MAZE_RIGHT);
            } 
            break;
        case 'A':
        case 'a':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_LEFT)){
                Pac->setDirection(MAZE_LEFT);
            }
            break;
        case 'W':
        case 'w':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_UP)){
                Pac->setDirection(MAZE_UP);
            }
            break;
        case 'S':
        case 's':
            if(Labyrinth->canIncrease(Pac->getX(), Pac->getY(), MAZE_DOWN)){
                Pac->setDirection(MAZE_DOWN);
            } 
            break;
        case 'Q':
        case 'q':
            vida = 0;
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
    testKeys();
    Pac->walk(Labyrinth);
    for(Ghost* g : Ghosts) g->walk(Labyrinth);
    testKeys();
    glutPostRedisplay();
    glutTimerFunc(FRAME_RATE, timerFunc, value);
}

void displayFunc() {
    int test;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    glRotatef(-50, 1, 0, 0);
    //glRotatef(ry, 0, 1, 0);
    //glRotatef(20, 0, 0, 1);
    //glTranslated(-240, -240, 0);
    
    glTranslated(-Pac->getX(), -Pac->getY(), 0);
    if( POWER_PELLET == Labyrinth->pelletCollision(Pac->getX(), Pac->getY(), Pac->getRadius())){
        for(Ghost* g : Ghosts) g->setReversed(true);
        tempo = time(NULL) + 5;
    }

    if(tempo != 0 && tempo < time(NULL)){
        for(Ghost* g : Ghosts) g->setReversed(false);
        tempo = 0;
    }


    for(Ghost* g : Ghosts) {
        if (g->collision(Pac->getX(), Pac->getY(), 16) == 2){
            Pac->reset();
            vida--;
            break;
        }
    }

    if(Labyrinth->getNumberOfPellets() < 1 or vida < 1) {
        glPopMatrix();
        glPushMatrix();

        glColor(WHITE);
        if (Labyrinth->getNumberOfPellets() < 1)
            glText("YOU WIN", 0, 0);
        else if (vida < 1)
            glText("YOU LOSE", 0, 0);
    }else{
        Pac->draw();
        Labyrinth->draw();
        for(Ghost* g : Ghosts)
            g->draw();
    }
    glPopMatrix();
    glPushMatrix();
    glColor(RED);
    glText(format("PELLETS: %d", Labyrinth->getNumberOfPellets()), 80, -115);
    glText(format("LIFE: %d", vida), -115, -115);

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
    glutTimerFunc(FRAME_RATE, timerFunc, 0);
	init();
	glutMainLoop();
	return 0;
}
