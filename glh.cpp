//
// Auxiliary file created by dsalexan on 20/06/2018.
//

#include <cstdarg>
#include <cstring>
#include "glh.h"


/* AUXILIAR CODE */
std::string format(const std::string fmt_str, ...){
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

/* BASIC OPERATIONS */
void glText(std::string text, int X, int Y){
    int i;
    void* font = GLUT_BITMAP_9_BY_15;

    glPushMatrix();
    glDisable(GL_DEPTH_TEST);

    glRasterPos3f(X, Y, 1);

    for(i=0; i < text.length(); i++)
        glutBitmapCharacter(font, text[i]);

    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}