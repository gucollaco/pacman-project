#ifndef _POINT_H_
#define _POINT_H_

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
        void increaseX(float x);
        void increaseY(float y);
};

#endif