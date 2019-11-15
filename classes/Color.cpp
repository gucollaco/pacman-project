#include "Color.h"

void glColor(Color c){
    glColor4ub(static_cast<GLubyte>(c.r), static_cast<GLubyte>(c.g), static_cast<GLubyte>(c.b), static_cast<GLubyte>(c.a));
}

void glColor(int* c){
    glColor(Color(c));
}

Color::Color(){
    this->r = this->g = this->b = 255;
    this->a = 1;
}

Color::Color(int *c) {
    this->r = c[0];
    this->g = c[1];
    this->b = c[2];

    this->a = 1;
}

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;

    this->a = 1;
}

