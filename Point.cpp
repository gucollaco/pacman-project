
#include "Point.h"

Point::Point(float x, float y){
    this->setPoint(x, y);
}
void Point::setX(float x){
    this->x = x;
}
void Point::setY(float y){
    this->y = y;
}
void Point::setPoint(float x, float y){
    this->x = x;
    this->y = y;
}
float Point::getX(){
    return this->x;
}
float Point::getY(){
    return this->y;
}
void Point::increaseX(float x){
    this->x += x;
}
void Point::increaseY(float y){
    this->y += y;
}