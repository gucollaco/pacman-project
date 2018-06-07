#include <GL/glut.h>

class Pellet {
    private:
        int x, y, r;
        GLUquadricObj *object;
    public:
        Pellet(int valX, int valY, int valr) {
            x = valX;
            y = valY;
            r = valr;
            object = gluNewQuadric();
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        int getR() {
            return r;
        }

        void setX(int valX) {
            x = valX;
        }

        void setR(int valr) {
            x = valr;
        }

        void setY(int valY) {
            y = valY;
        }

        void draw(int valX, int valY) {
            glPushMatrix();
                setX(valX);
                setY(valY);
                glTranslatef(x, y, 0);
                gluSphere(object, r, 20, 20);
            glPopMatrix();
        }
};
