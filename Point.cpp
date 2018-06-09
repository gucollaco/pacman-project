#ifndef  __POINT_CPP__
#define  __POINT_CPP__

class Point {
    private:
        float x, y;
    public:
        Point(float x, float y);
        void setX(float x);
        void setY(float y);
        void setPoint(float x, float y);
        float getX();
        float getY();
};
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

#endif
