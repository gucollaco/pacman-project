#ifndef _PACMAN_H_
#define _PACMAN_H_


class Pacman {
private:
    float x, y;
    GLUquadricObj *object;
public:
    Pacman(float valX, float valY);
    float getX();
    float getY();
    void setX(float valX);
    void setY(float valY);
    void draw(float valX, float valY);
};

#endif