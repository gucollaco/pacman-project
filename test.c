#include <GL/glut.h>

double aspect_ratio = 0;



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(255,0,0);
    
    output(0,0,"hello");

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(500,500);
    glutCreateWindow("Text");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}