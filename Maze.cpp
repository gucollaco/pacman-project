#include <iosfwd>
#include <sstream>
#include "Maze.h"

Maze::Maze(int line, int column){
    this->alloc(line, column);
    normal = NULL;
    power = NULL;
}

int inside(float value){
    return static_cast<int>((value + 12.5) / 25);
}

void Maze::pelletCollision(Pacman *Pac){
    float x = Pac->getX();
    float y = Pac->getY();
    float r = Pac->getRadius();
    int l = inside(x);
    int c = inside(y);
    float x1 = 25*l;
    float y1 = 25*c;
    float dx = x - x1;
    float dy = y - y1;
    if (dx*dx + dy*dy <= r*r){
        if(this->getValue(l, c) == '0' || this->getValue(l, c) == '2' ){
            this->setValue(l, c, '9');
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
            case '0':
                glColor3ub(230, 220, 175);
                normal->setPoint(i*25, j*25);
                normal->draw();
                break;
            case '2':
                glColor3ub(205, 130, 65);
                power->setPoint(i*25, j*25);
                power->draw();
                break;
            case '3':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(-6.25, 6.25, 0);
                glutSolidCube(12.5);
                glTranslatef(0, -12.5, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case '4':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(6.25, 6.25, 0);
                glutSolidCube(12.5);
                glTranslatef(0, -12.5, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case '5':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(6.25, -6.25, 0);
                glutSolidCube(12.5);
                glTranslatef(-12.5, 0, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case '6':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(6.25, 6.25, 0);
                glutSolidCube(12.5);
                glTranslatef(-12.5, 0, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case 'a':
                glColor3ub(0, 0, 255);
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
            case 'b':
                glColor3ub(0, 0, 255);
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
            case 'c':
                glColor3ub(0, 0, 255);
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
            case 'd':
                glColor3ub(0, 0, 255);
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
            case 'e':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(6.25, 6.25, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case 'f':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(6.25, -6.25, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case 'g':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(-6.25, 6.25, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            case 'h':
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glTranslatef(-6.25, -6.25, 0);
                glutSolidCube(12.5);
                glPopMatrix();
                break;
            }
            
        }
    }
    glColor3ub(0, 0, 255);
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

bool Maze::canIncrease(float x, float y, int direcao){
    int l = inside(x);
    int c = inside(y);
    int v;
    switch(direcao){
        case MAZE_UP:
            v = this->getValue(l, c+1);
            if( x/25 != (int)x/25 )
                return false;
            if( c < inside(y+13) && (v != '0' && v != '9' && v != '2') )
                return false;
            break;
        case MAZE_DOWN:
            v = this->getValue(l, c-1);
            if( x/25 != (int)x/25 )
                return false;
            if( c > inside(y-13) && (v != '0' && v != '9' && v != '2') )
                return false;
            break;
        case MAZE_LEFT:
            v = this->getValue(l-1, c);
            if( y/25 != (int)y/25 )
                return false;
            if( l > inside(x-13) && (v != '0' && v != '9' && v != '2') )
                return false;
            break;
        case MAZE_RIGHT:
            v = this->getValue(l+1, c);
            if( y/25 != (int)y/25 )
                return false;
            if( l < inside(x+13) && (v != '0' && v != '9' && v != '2') )
                return false;
            break;
        default:
            return false;
    }
    return true;
}