#include <stdio.h>
#include <math.h>
#include <ctime>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Maze.cpp"
#include "Ghost.cpp"
#include "Point.cpp"
#include "Pacman.cpp"
#include "Pellet.cpp"

int vida = 3;
double rx = 0, ry = 0, rz = 0;
float zoom = 100;
time_t tempo = 0;

Maze *Labyrinth;
Pellet *NormalPellet;
Pellet *PowerPellet;
Ghost *GhoBlinky;
Ghost *GhoClyde;
Ghost *GhoInky;
Ghost *GhoPinky;
Pacman *Pac;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 3.0f, 7.0f, 7.0f, 0.0f };

void output(GLfloat x, GLfloat y, const char* text)
{
    glPushMatrix();
    glRasterPos2f(x, y);
    for(const char* p = text; *p; p++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
    }
    glPopMatrix();
}

void initPacman(){
    char arq[] = "Matrix.txt";
    NormalPellet = new Pellet(3.0);
    PowerPellet = new Pellet(6.0);
    Labyrinth = new Maze(arq);
    Labyrinth->show();
    Labyrinth->setPellets(NormalPellet, PowerPellet);
    GhoClyde = new Ghost(5*25, 25, 255, 165, 0, false); //clyde
    GhoPinky = new Ghost(11*25, 13*25, 255, 105, 180, false); //pinky
    GhoInky = new Ghost(11*25, 11*25, 0, 255, 255, false); //inky
    GhoBlinky = new Ghost(11*25, 9*25, 255, 0, 0, false); //blinky
    Pac = new Pacman(25*23, 25*13.5, 16);
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
    Pac->walk(Labyrinth);
    GhoBlinky->walk(Labyrinth);
    GhoClyde->walk(Labyrinth);
    GhoPinky->walk(Labyrinth);
    GhoInky->walk(Labyrinth);
    glutPostRedisplay();
    glutTimerFunc(200, timerFunc, value);
}

void displayFunc() {
    int test;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glColor3ub(0,0,255);
    glPopMatrix();
    glPushMatrix();
    int Number = 123;       // number to be converted to a string
    std::string Result;          // string which will contain the result
    std::ostringstream convert, convert2;   // stream used for the conversion
    convert << "PELLETS: " << Labyrinth->getNumberOfPellets();      // insert the textual representation of 'Number' in the characters in the stream
    convert2 << "LIFE: " << vida;
    Result = convert.str(); 
    output(-180, -180, Result.c_str());
    Result = convert2.str(); 
    output(150,-180, Result.c_str());
    glRotatef(-50, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);
    glRotatef(20, 0, 0, 1);
    //glTranslated(-240, -240, 0);
    
    glTranslated(-Pac->getX(), -Pac->getY(), 0);
    if( POWER_PELLET == Labyrinth->pelletCollision(Pac->getX(), Pac->getY(), Pac->getRadius())){
        GhoBlinky->setReversed(true);
        GhoClyde->setReversed(true);
        GhoInky->setReversed(true);
        GhoPinky->setReversed(true);
        tempo = time(NULL) + 5;
    }
    if(tempo != 0 && tempo < time(NULL)){
        GhoBlinky->setReversed(false);
        GhoClyde->setReversed(false);
        GhoInky->setReversed(false);
        GhoPinky->setReversed(false);
        tempo = 0;
    }
    test = GhoBlinky->collision(Pac->getX(), Pac->getY(), 16);
    if(test == 2){
        Pac->reset();
        vida--;
    } 
    test = GhoClyde->collision(Pac->getX(), Pac->getY(), 16);
    if(test == 2){
        Pac->reset();
        vida--;
    }
    test = GhoInky->collision(Pac->getX(), Pac->getY(), 16);
    if(test == 2){
        Pac->reset();
        vida--;
    }
    test = GhoPinky->collision(Pac->getX(), Pac->getY(), 16);
    if(test == 2){
        Pac->reset();
        vida--;
    }
    if(Labyrinth->getNumberOfPellets() < 1){
        glPopMatrix();
        glPushMatrix();
        char msg[] = "YOU WIN";
        output(0,0, msg);
    }
    else if(vida < 1){
        char msg[] = "YOU LOSE";
        glPopMatrix();
        glPushMatrix();
        output(0,0, msg);
    }
    else{
        
        Pac->draw();
        Labyrinth->draw();
        GhoClyde->draw();
        GhoPinky->draw();
        GhoInky->draw();
        GhoBlinky->draw();
    }
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
