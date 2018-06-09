#include "Pellet.h"

Pellet::Pellet(float valRadius) : Point(0, 0){
    this->radius = valRadius;
    this->object = gluNewQuadric();
}

float Pellet::getRadius() {
    return this->radius;
}

void Pellet::setRadius(float valRadius) {
    this->radius = valRadius;
}

void Pellet::draw() {
    glPushMatrix();
        glTranslatef(this->getX(), this->getY(), 0);
        gluSphere(object, radius, 20, 20);
    glPopMatrix();
}