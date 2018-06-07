#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Maze.cpp"
#include "Ghost.cpp"

typedef struct Pos {
    int x;
    int y;
}Pos;

Pos posBlinky = {225, 285};
Pos posClyde = {285, 335};
Pos posInky = {285, 285};
Pos posPinky = {285, 235};

double rx = 0, ry = 0, rz = 0, rt = 25, lt = 25;

Matrix *Mat;
Pellet *Pel;
Pellet *Powerpel;
Ghost *GhoBlinky;
Ghost *GhoClyde;
Ghost *GhoInky;
Ghost *GhoPinky;
//Pacman *pac;

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-600, 600, -600, 600, -600, 600); //define uma projeção ortogonal
    glPushMatrix();
}

int inside(float value){
    float res = value + 12.5;
    res = res/25;
    return res;
}

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int canIncrease(Matrix *Mat, float x, float y, int direcao){
    int l = inside(x);
    int c = inside(y);
    int v1, v2, v3;
    if(direcao == UP){
        v1 = Mat->getValue(l-1, c+1);
        v2 = Mat->getValue(l, c+1);
        v3 = Mat->getValue(l+1, c+1);
        if( c < inside(y+7.5) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside(x-7.25) )
                return 0;
        }
    }
    if(direcao == DOWN){
        v1 = Mat->getValue(l-1, c-1);
        v2 = Mat->getValue(l, c-1);
        v3 = Mat->getValue(l+1, c-1);
        if( c > inside(y-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside(x-7.25) )
                return 0;
        }
    }
    if(direcao == LEFT){
        v1 = Mat->getValue(l-1, c-1);
        v2 = Mat->getValue(l-1, c);
        v3 = Mat->getValue(l-1, c+1);
        if( l > inside(x-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside(y-7.25) )
                return 0;
        }
    }
    if(direcao == RIGHT){
        v1 = Mat->getValue(l+1, c-1);
        v2 = Mat->getValue(l+1, c);
        v3 = Mat->getValue(l+1, c+1);
        if( l < inside(x+7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside(y-7.25) )
                return 0;
        }
    }
    return 1;
}

void keyboardInt(unsigned char key, int x, int y){
    printf("%lf %lf\n", rt, lt);
    switch(key){
        case 'd':
            /*if(canIncrease(Mat, rt, lt, RIGHT))*/ rt += 2.5;
            break;
        case 'a':
            /*if(canIncrease(Mat, rt, lt, LEFT))*/ rt -= 2.5;
            break;
        case 'w':
            /*if(canIncrease(Mat, rt, lt, UP))*/ lt += 2.5;
            break;
        case 's':
            /*if(canIncrease(Mat, rt, lt, DOWN))*/ lt -= 2.5;
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

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glColor3ub(0,0,255);
    glPopMatrix();
    glPushMatrix();
    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);
    glRotatef(rz - 90, 0, 0, 1);
    glTranslated(-240, -240, 0);
    Mat->draw(Pel, Powerpel);
    Pel->draw(rt, lt);
    GhoClyde->draw(posClyde.x, posClyde.y);
    GhoPinky->draw(posPinky.x, posPinky.y);
    GhoInky->draw(posInky.x, posInky.y);
    GhoBlinky->draw(posBlinky.x, posBlinky.y);
    glutSwapBuffers();
//    pac->draw();
}

int main(int argc, char *argv[]){
    char arq[] = "Matrix.txt";
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(900, 900);
	glutCreateWindow("Pacman - Project");

	Mat = new Matrix(arq);
    Pel = new Pellet(rt,lt, 3);
    Powerpel = new Pellet(rt, lt, 7);
    GhoClyde = new Ghost(posClyde.x, posClyde.y, 255, 165, 0, false); //clyde
    GhoPinky = new Ghost(posPinky.x, posPinky.y, 255, 105, 180, false); //pinky
    GhoInky = new Ghost(posInky.x, posInky.y, 0, 255, 255, false); //inky
    GhoBlinky = new Ghost(posBlinky.x, posBlinky.y, 255, 0, 0, false); //blinky

    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialInt);
    glutKeyboardFunc(keyboardInt);
	init();
	glutMainLoop();
	return 0;
}
