#include <stdio.h>
#include <math.h>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"

int inside2(float value){
    return static_cast<int>((value + 12.5) / 25);
}

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

    Point posBlinky = Point(25, 285);
    Point posClyde = Point(285, 335);
    Point posInky = Point(285, 285);
    Point posPinky = Point(285, 235);

    NormalPellet = new Pellet(3.0);
    PowerPellet = new Pellet(7.0);

    Labyrinth = new Maze(arq);
    Labyrinth->setPellets(NormalPellet, PowerPellet);

    GhoClyde = new Ghost(posClyde, Color(LIGHT_PINK), false); //clyde
    GhoPinky = new Ghost(posPinky, Color(ORANGE), false); //pinky
    GhoInky = new Ghost(posInky, Color(CYAN), false); //inky
    GhoBlinky = new Ghost(posBlinky, Color(RED), false); //blinky*/
=======
    GhoClyde = new Ghost(225, 285, 255, 165, 0, false); //clyde
    GhoPinky = new Ghost(285, 335, 255, 105, 180, false); //pinky
    GhoInky = new Ghost(285, 285, 0, 255, 255, false); //inky
    GhoBlinky = new Ghost(285, 235, 255, 0, 0, false); //blinky
    Pac = new Pacman(350, 170);
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
            /*if(canIncrease(Mat, posPac.x, posPac.y, RIGHT))*/ Pac->setX(Pac->getX()+2.5);
            break;
        case 'a':
            /*if(canIncrease(Mat, posPac.x, posPac.y, LEFT))*/ Pac->setX(Pac->getX()-2.5);
            break;
        case 'w':
            /*if(canIncrease(Mat, posPac.x, posPac.y, UP))*/ Pac->setY(Pac->getY()+2.5);
            break;
        case 's':
            /*if(canIncrease(Mat, posPac.x, posPac.y, DOWN))*/ Pac->setY(Pac->getY()-2.5);
            break;
    }
    printf("%lf %lf\n", Pac->getX(), Pac->getY());
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

    glColor(BLUE);
    glPopMatrix();
    glPushMatrix();
    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);
    glRotatef(rz, 0, 0, 1);
    glTranslated(-240, -240, 0);

    Labyrinth->colisaoPellet(pontoTeste.x, pontoTeste.y, 3);
    PowerPellet->setPoint(pontoTeste.x, pontoTeste.y);

    glColor(RED);
    PowerPellet->draw();
    Labyrinth->colisaoPellet(Pac->getX(), Pac->getY(), 8);
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
