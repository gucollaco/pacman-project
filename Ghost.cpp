#include <GL/glut.h>
#include "Point.cpp"

class Ghost : public Point{
    private:
        int r, g, b;
        bool isReversed;
        GLUquadricObj *object;
    public:
        Ghost(int valX, int valY, int valR, int valG, int valB, bool rev);
        void draw();
};

Ghost::Ghost(int valX, int valY, int valR, int valG, int valB, bool rev) : Point(valX, valY) {
    this->r = valR;
    this->g = valG;
    this->b = valB;
    this->isReversed = rev;
    this->object = gluNewQuadric();
}

void Ghost::draw() {
    glPushMatrix();
        glTranslatef(this->getX(), this->getY(), 0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
//                if(angY == 0 || angY == 180) {
//                    glTranslatef(transl, 0.0, 0.0);
//                } else if(angY == 90 || angY == 270) {
//                    glTranslatef(0.0, 0.0, transl);
//                }
//                glRotatef(angX, 1.0, 0.0, 0.0);
//                glRotatef(angY, 0.0, 1.0, 0.0);
        glPushMatrix();
            glTranslatef(0.0, 2.0, 0.0);
            //ghost body
            glColor3ub(this->r, this->g, this->b);
            glPushMatrix();
                glRotatef(90.0, 1.0, 0.0, 0.0);
                gluSphere(this->object, 8, 50, 10);
                gluCylinder(this->object, 8, 8, 12, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -12.0, 0.0);
                glRotatef(90.0, 1.0, 0.0, 0.0);
                gluDisk(this->object, 0, 8, 50, 10);
            glPopMatrix();

            //ghost eyes - white part
            glColor3ub(255, 255, 255);
            glPushMatrix();
                glRotatef(20, 0.0, 1.0, 0.0);
                glTranslatef(4.0, 4.0, 4.0);
                gluSphere(this->object, 2, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glRotatef(70, 0.0, 1.0, 0.0);
                glTranslatef(4.0, 4.0, 4.0);
                gluSphere(this->object, 2, 50, 10);
            glPopMatrix();

            if(!isReversed) {
                //ghost eyes - black part
                glColor3ub(0, 0, 0);
                glPushMatrix();
                    glColor3ub(0, 0, 0);
                    glRotatef(20, 0.0, 1.0, 0.0);
                    glTranslatef(4.8, 4.8, 4.8);
                    gluSphere(object, 1, 50, 10);
                glPopMatrix();
                glPushMatrix();
                    glRotatef(70, 0.0, 1.0, 0.0);
                    glTranslatef(4.8, 4.8, 4.8);
                    gluSphere(this->object, 1, 50, 10);
                glPopMatrix();
            }

            //ghost leg - central leg
            glColor3ub(this->r, this->g, this->b);
            glPushMatrix();
                glTranslatef(0.0, -12.0, 0.0);
                glPushMatrix();
                    glRotatef(90, 1.0, 0.0, 0.0);
                    gluCylinder(this->object, 2, 1.5, 6, 50 , 10);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0.0, -3, 0.0);
                    gluSphere(this->object, 1.5, 50, 10);
                glPopMatrix();
            glPopMatrix();

            //ghost leg - other legs
            glColor3ub(this->r, this->g, this->b);
            glPushMatrix();
//                        aniRate = !(ghost.isReversed) ? 1.5 : 3.0;
//                        glRotatef(animation, 0, 1, 0);
                int i = 0;
                while(i <= 360) {
                    glPushMatrix();
                        glRotatef(-20 + i, 0.0, 1.0, 0.0);
                        glTranslatef(5.95, -12.0, 0.0);
                        glPushMatrix();
                            glRotatef(90, 1.0, 0.0, 0.0);
                            gluCylinder(this->object, 2, 1.5, 3, 50 , 10);
                        glPopMatrix();
                        glPushMatrix();
                            glTranslatef(0.0, -3, 0.0);
                            gluSphere(this->object, 1.5, 50, 10);
                        glPopMatrix();
                    glPopMatrix();
                    i = i + 60;
                }
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}
