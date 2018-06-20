#include "Ghost.h"
#include "Random.h"

Ghost::Ghost(int valX, int valY, int valR, int valG, int valB, bool rev) : Point(valX, valY) {
    this->color.r = valR;
    this->color.g = valG;
    this->color.b = valB;
    this->isReversed = rev;
    this->object = gluNewQuadric();
}

Ghost::Ghost(int valX, int valY, Color valColor, bool rev) : Point(valX, valY) {
    this->color = valColor;
    this->isReversed = rev;
    this->object = gluNewQuadric();
}

Ghost::Ghost(Point valPoint, int valR, int valG, int valB, bool rev) : Point(valPoint.getX(), valPoint.getY()) {
    this->color.r = valR;
    this->color.g = valG;
    this->color.b = valB;
    this->isReversed = rev;
    this->object = gluNewQuadric();
}

Ghost::Ghost(Point valPoint, Color valColor, bool rev) : Point(valPoint.getX(), valPoint.getY()) {
    this->color = valColor;
    this->isReversed = rev;
    this->object = gluNewQuadric();
}

int inside2(float value){
    return static_cast<int>((value + 12.5) / 25);
}

bool Ghost::walk(Maze *maze){
    bool canWalk, decision = true;
    char value;
    float x = this->getX();
    float y = this->getY();
    int l = inside2(x);
    int c = inside2(y);
    if( x/25 != (int)x/25 || y/25 != (int)y/25 )
        decision = false;
    if( decision ){
        value = maze->getValue(l, c);
        if(value == '1' || value == '8' || value == '7'){
            do{
                this->direction = Random::next(4);
                canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
            }while(!canWalk);
        }
        else{
            canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
            while(!canWalk){
                this->direction = Random::next(4);
                canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
            }    
        }
    }
    else{
        canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
        while(!canWalk){
            this->direction = Random::next(4);
            canWalk = maze->canIncrease(this->getX(), this->getY(), this->direction);
        }
    }
    switch(this->direction){
    case GHOST_UP:
        this->increaseY(12.5);
        break;
    case GHOST_DOWN:
        this->increaseY(-12.5);
        break;
    case GHOST_LEFT:
        this->increaseX(-12.5);
        break;
    case GHOST_RIGHT:
        this->increaseX(12.5);
        break;
    }
    return true;
}

void Ghost::setDirection(int direction){
    this->direction = direction;
}

int Ghost::getDirection(){
    return this->direction;
}

void Ghost::setReversed(bool reversed){
    this->isReversed = reversed;
}

bool Ghost::getReversed(){
    return this->isReversed;
}

int Ghost::collision(float x, float y, float r){
    float x1 = this->getX();
    float y1 = this->getY();
    int l = inside2(x1);
    int c = inside2(y1);
    x1 = l*25;
    y1 = c*25;
    float dx = x - x1;
    float dy = y - y1;
    if (dx*dx + dy*dy <= r*r){
        //this->isReversed = true;
        if(this->isReversed){
            this->reset();
            return 1;
        }
        return 2;
    }
    return 0;
}

void Ghost::draw() {
    glPushMatrix();
        glTranslatef(this->getX(), this->getY(), 0);
        glTranslatef(0 , 0, 16-6.25);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glRotatef(90.0*direction, 0.0, 1.0, 0.0);
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

            if(this->isReversed)
                glColor(BLUE);
            else
                glColor(this->color);

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


            //ghost leg - central leg
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


            //ghost eyes - white part
            glColor(WHITE);
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
                glColor(WHITE);
                glPushMatrix();
                    glColor(BLACK);
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

        glPopMatrix();

    glPopMatrix();
}
