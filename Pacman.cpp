#include "Pacman.h"
#include "Color.h"

Pacman::Pacman(float valX, float valY, float valRadius) : Point(valX, valY) {
    this->setRadius(radius);
    object = gluNewQuadric();
    inc = 7.5;
    animation = 60;
}

int inside3(float value){
    return static_cast<int>((value + 12.5) / 25);
}

void Pacman::walk(Maze *maze){
    bool canWalk, decision = true;
    char value;
    float x = this->getX();
    float y = this->getY();
    int l = inside3(x);
    int c = inside3(y);
    if( x/25 != (int)x/25 || y/25 != (int)y/25 )
        decision = false;
    if(decision){
        value = maze->getValue(l, c);
        if(value == '7'){
            if(this->getY() == 0){
                this->setY(27*25);
            }
            else{
                this->setY(25);
            }
        }
    }
    canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
    if(canWalk){
        switch(this->direction){
        case PAC_UP:
            this->increaseY(12.5);
            break;
        case PAC_DOWN:
            this->increaseY(-12.5);
            break;
        case PAC_LEFT:
            this->increaseX(-12.5);
            break;
        case PAC_RIGHT:
            this->increaseX(12.5);
            break;
        }
        if(animation >= 90 || animation <= 45)
            inc = -inc;
        animation += inc;
    }
}

void Pacman::setDirection(int direction){
    this->direction = direction;
}

int Pacman::getDirection(){
    return this->direction;
}

void Pacman::setRadius(float radius){
    this->radius = radius;
}

float Pacman::getRadius(){
    return this->radius;
}

void Pacman::draw(){
    glPushMatrix();
        glTranslatef(this->getX(), this->getY(), 0);
        glTranslatef(0, 0, 16-6.25);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glRotatef(90.0*direction, 0.0, 1.0, 0.0);
        glRotatef(10, 0, 0, 1);
        glPushMatrix();
            glColor(YELLOW);
            double clip[2][4] = {{ 5.0, 0.0, 0.0, 1.0 }, { -5.0, 0.0, 0.0, 1.0 }};
            glEnable(GL_CLIP_PLANE0);
                glPushMatrix();
                    glRotatef(-10, 0, 0, 1);
                    glRotatef(animation, 0.0, 0.0, 1.0);
                    glClipPlane(GL_CLIP_PLANE0, clip[1]);
                    glPushMatrix();
                        gluSphere(object, 16, 50, 10);
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                    glRotatef(-10, 0, 0, 1);
                    glRotatef(-animation, 0.0, 0.0, 1.0);
                    glClipPlane(GL_CLIP_PLANE0, clip[1]);
                    glPushMatrix();
                        gluSphere(object, 16, 50, 10);
                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glDisable(GL_CLIP_PLANE0);
            glColor(BLACK);
            glPushMatrix();
                glRotatef(20, 0.0, 0.0, 1.0);
                glRotatef(20, 0.0, 1.0, 0.0);
                glTranslatef(9, 9, 9);
                gluSphere(object, 4, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glRotatef(20, 0.0, 0.0, 1.0);
                glRotatef(70, 0.0, 1.0, 0.0);
                glTranslatef(9, 9, 9);
                gluSphere(object, 4, 50, 10);
            glPopMatrix();
        glPopMatrix();
        
        glDisable(GL_CLIP_PLANE0);

    glPopMatrix();
}
