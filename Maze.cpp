#include <iosfwd>
#include <sstream>
#include <malloc.h>
#include <cstdlib>
#include "Maze.h"
#include "Color.h"

Maze::Maze(int line, int column){
    this->alloc(line, column);
    normal = NULL;
    power = NULL;
}

int inside(float value){
    return static_cast<int>((value + 12.5) / 25);
}

int Maze::getNumberOfPellets(){
    return this->pellets;
}

int Maze::pelletCollision(float x, float y, int r){
    int l = inside(x);
    int c = inside(y);
    float x1 = 25*l;
    float y1 = 25*c;
    float dx = x - x1;
    float dy = y - y1;
    if (dx*dx + dy*dy <= r*r){
        switch(this->getValue(l, c)){
            case '0':
            case '1':
                this->pellets--;
                this->setValue(l, c, '9');
                return NORMAL_PELLET;
            case '2':
                this->pellets--;
                this->setValue(l, c, '9');
                return POWER_PELLET;
            default:
                return NOT_A_PELLET;
        }
    }
}

/*------------------------------
 * Instancia um Maze a partir
 * de um arquivo texto
------------------------------*/
Maze::Maze(char *path_char){
    int i, j;
    char valor;
    std::string path(path_char);
    this->pellets = 0;
    FILE *temp = fopen(path.c_str(), "r");
    while(temp == NULL){
        printf("Coundn't find maze file, trying again...\n");

        std::stringstream ss;
        ss << "../" << path;
        path = ss.str();
        printf("Trying at <%s>\n", path);

        temp = fopen(path.c_str(), "r");
    }

    fscanf(temp, "%d %d",&i, &j);
    this->alloc(i, j);
    fscanf(temp, "%c", &valor);
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            fscanf(temp, "%c ", &valor);
            this->value[i][j] = valor;
            if(valor == '1' || valor == '2' || valor == '0'){
                this->pellets++;
            }
        }
    }
    normal = NULL;
    power = NULL;
}

/*-----------------------------
 * Cria Maze com o numero de
 * lines = lin e columns = col
------------------------------*/
void Maze::alloc(int lin, int col){
    int i;
    this->value = (int**) malloc(sizeof(int*)*lin);
    for(i = 0; i < lin; i++){
        this->value[i] = (int*) malloc(sizeof(int)*col);
    }
    this->lin = lin;
    this->col = col;
}

void Maze::draw(){
    int i, j;
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            switch(this->getValue(i, j)){

                case MATRIX_COMMON_PELLET:
                case MATRIX_TURNING_PELLET:
                    glColor(SAND);

                    normal->setPoint(i*25, j*25);
                    normal->draw();
                    break;
                case MATRIX_POWER_PELLET:
                    glColor(BROWN_BEIGE);

                    power->setPoint(i*25, j*25);
                    power->draw();
                    break;
                case MATRIX_TOP_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(-6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, -12.5, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_BOTTOM_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, -12.5, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_LEFT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, -6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_RIGHT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_TOP_LEFT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, -6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, 12.5, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_TOP_RIGHT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, -12.5, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_BOTTOM_LEFT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, -12.5, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_BOTTOM_RIGHT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, -6.25, 0);
                    glutSolidCube(12.5);
                    glTranslatef(0, 12.5, 0);
                    glutSolidCube(12.5);
                    glTranslatef(-12.5, 0, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_INNER_TOP_LEFT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_INNER_TOP_RIGHT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(6.25, -6.25, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_INNER_BOTTOM_LEFT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(-6.25, 6.25, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
                case MATRIX_INNER_BOTTOM_RIGHT_WALL:
                    glColor(BLUE);

                    glPushMatrix();
                    glTranslated(i*25, j*25, 0);
                    glTranslatef(-6.25, -6.25, 0);
                    glutSolidCube(12.5);
                    glPopMatrix();
                    break;
            }
            
        }
    }
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(0, 0, -6.25);
        glVertex3f(0, this->col*25, -6.5);
        glVertex3f(this->lin*25, this->col*25, -6.5);
        glVertex3f(this->lin*25, 0, -6.5);
    glEnd();
}

void Maze::setValue(int line, int column, int value){
    this->value[line][column] = value;
}

int Maze::getValue(int line, int column){
    return value[line][column];
}

void Maze::show(){
    int i, j;
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            printf("%c ", (char) this->getValue(i, j));
        }
        printf("\n");
    }
}

void Maze::setPellets(Pellet *normal, Pellet *power){
    this->normal = normal;
    this->power = power;
}

bool isWall(char c){
    return (c != '0' && c != '9' && c != '2' && c != '1' && c != '8' && c != '7');
}

bool Maze::canIncrease(float x, float y, int direcao){
    int l = inside(x);
    int c = inside(y);
    int v;
    switch(direcao){
        case MAZE_UP:
            v = this->getValue(l, c+1);
            if( x/25 != (int)x/25 )
                return false;
            if( c < inside(y+13) &&  isWall(v))
                return false;
            break;
        case MAZE_DOWN:
            v = this->getValue(l, c-1);
            if( x/25 != (int)x/25 )
                return false;
            if( c > inside(y-13) && isWall(v) )
                return false;
            break;
        case MAZE_LEFT:
            v = this->getValue(l-1, c);
            if( y/25 != (int)y/25 )
                return false;
            if( l > inside(x-13) && isWall(v) )
                return false;
            break;
        case MAZE_RIGHT:
            v = this->getValue(l+1, c);
            if( y/25 != (int)y/25 )
                return false;
            if( l < inside(x+13) && isWall(v) )
                return false;
            break;
        default:
            return false;
    }
    return true;
}