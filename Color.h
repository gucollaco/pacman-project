//
// Created by dsalexan on 08/06/2018.
//

#ifndef PACMAN_PROJECT_COLOR_H
#define PACMAN_PROJECT_COLOR_H

#define WHITE {255, 255, 255}
#define BLACK {0,0,0}

#define RED {255, 0, 0}
#define GREEN {0, 255, 0}
#define BLUE {0, 0, 255}

#define LIGHT_PINK {255, 165, 0}
#define ORANGE {255, 105, 180}
#define CYAN {0, 255, 255}

#define SAND {230, 220, 175}
#define YELLOW {255, 255, 0}
#define BROWN_BEIGE {205, 130, 65}


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Color {
public:
    int r;
    int g;
    int b;

    double a;

    Color();
    explicit Color(int* c);
    Color(int r, int g, int b);
};

void glColor(Color c);
void glColor(int* c);


#endif //PACMAN_PROJECT_COLOR_H
