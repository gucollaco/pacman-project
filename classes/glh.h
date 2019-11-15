//
// Created by dsalexan on 20/06/2018.
//

#ifndef PACMAN_PROJECT_GLH_H
#define PACMAN_PROJECT_GLH_H


#include <string>
#include <cstdarg>
#include <cstring>
#include <memory>
#include <list>

#include <cmath>

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

#include "Point.h"

/* AUXILIAR CODE */
std::string format(const std::string fmt_str, ...);

/* BASIC OPERATIONS */
void glText(std::string text, int x, int y);


#endif //PACMAN_PROJECT_GLH_H
