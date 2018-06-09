
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Pacman.h"

Pacman::Pacman(float valX, float valY) {
    x = valX;
    y = valY;
    object = gluNewQuadric();
}

float Pacman::getX() {
    return x;
}

float Pacman::getY() {
    return y;
}

void Pacman::setX(float valX) {
    x = valX;
}

void Pacman::setY(float valY) {
    y = valY;
}

void Pacman::draw(float valX, float valY){
    glPushMatrix();
        setX(valX);
        setY(valY);
        glTranslatef(x, y, 0);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        glPushMatrix();
            glColor3ub(255, 255, 0);
            double clip[2][4] = {{ 5.0, 0.0, 0.0, 1.0 }, { -5.0, 0.0, 0.0, 1.0 }};
            glEnable(GL_CLIP_PLANE0);
                glPushMatrix();
                            glRotatef(25, 0, 0, 1);
                    glRotatef(-45, 0.0, 0.0, 1.0);
                    glClipPlane(GL_CLIP_PLANE0, clip[1]);
                    glPushMatrix();
                        gluSphere(object, 80, 50, 10);
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                            glRotatef(25, 0, 0, 1);
                    glRotatef(45, 0.0, 0.0, 1.0);
                    glClipPlane(GL_CLIP_PLANE0, clip[1]);
                    glPushMatrix();
                        gluSphere(object, 80, 50, 10);
                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glDisable(GL_CLIP_PLANE0);
            glColor3ub(0, 0, 0);
            glPushMatrix();
                glRotatef(20, 0.0, 0.0, 1.0);
                glRotatef(20, 0.0, 1.0, 0.0);
                glTranslatef(4.6, 4.6, 4.6);
                gluSphere(object, 20, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glRotatef(20, 0.0, 0.0, 1.0);
                glRotatef(70, 0.0, 1.0, 0.0);
                glTranslatef(4.6, 4.6, 4.6);
                gluSphere(object, 20, 50, 10);
            glPopMatrix();
        glPopMatrix();
        glDisable(GL_CLIP_PLANE0);

    glPopMatrix();
}
