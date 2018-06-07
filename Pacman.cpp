//GLUquadricObj *object;

class Pacman {
    private:
        int x, y;

    public:
        Pacman(int valX, int valY) {
            x = valX;
            y = valY;
            object = gluNewQuadric();
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        void setX(int valX) {
            x = valX;
        }

        void setY(int valY) {
            y = valY;
        }

        void draw(int valX, int valY) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPushMatrix();
                setX(valX);
                setY(valY);
                glTranslatef(x, y, 0);
                glRotatef(90.0, 1.0, 0.0, 0.0);
//                glRotatef(angX, 1.0, 0.0, 0.0);
//                glRotatef(angY, 0.0, 1.0, 0.0);
//                glRotatef(angZ, 0.0, 0.0, 1.0);

                glPushMatrix();
                    glColor3ub(255, 255, 0);
                    double clip[2][4] = {{ 5.0, 0.0, 0.0, 1.0 }, { -5.0, 0.0, 0.0, 1.0 }};
                    glEnable(GL_CLIP_PLANE0);
                        glPushMatrix();
//                            glRotatef(animation1, 0, 0, 1);
                            glRotatef(-45, 0.0, 0.0, 1.0);
                            glClipPlane(GL_CLIP_PLANE0, clip[1]);
                            glPushMatrix();
                                gluSphere(object, 4, 50, 10);
                            glPopMatrix();
                        glPopMatrix();
                        glPushMatrix();
//                            glRotatef(animation2, 0, 0, 1);
                            glRotatef(45, 0.0, 0.0, 1.0);
                            glClipPlane(GL_CLIP_PLANE0, clip[1]);
                            glPushMatrix();
                                gluSphere(object, 8, 50, 10);
                            glPopMatrix();
                        glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                    glDisable(GL_CLIP_PLANE0);
                    glColor3ub(0, 0, 0);
                    glPushMatrix();
                        glRotatef(20, 0.0, 0.0, 1.0);
                        glRotatef(20, 0.0, 1.0, 0.0);
                        glTranslatef(4.6, 4.6, 4.6);
                        gluSphere(object, 1, 50, 10);
                    glPopMatrix();
                    glPushMatrix();
                        glRotatef(20, 0.0, 0.0, 1.0);
                        glRotatef(70, 0.0, 1.0, 0.0);
                        glTranslatef(4.6, 4.6, 4.6);
                        gluSphere(object, 1, 50, 10);
                    glPopMatrix();
                glPopMatrix();
                glDisable(GL_CLIP_PLANE0);

            glPopMatrix();
//            glutSwapBuffers();
        }
};
