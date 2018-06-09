
#include <iosfwd>
#include <sstream>
#include "Maze.h"

Maze::Maze(int line, int column){
    this->alloc(line, column);
    normal = NULL;
    power = NULL;
}

int circ(float x, float y, float r, float x1, float y1){
    float dx = x - (x1);
    float dy = y - (y1);
    return dx*dx + dy*dy <= r*r;
}

int inside(float value){
    return static_cast<int>((value + 12.5) / 25);
}

void Maze::colisaoPellet(float x, float y, float r){
    int l = inside(x);
    int c = inside(y);
    float x1 = 25*l;
    float y1 = 25*c;
    float dx = x - x1;
    float dy = y - y1;
    if (dx*dx + dy*dy <= r*r){
        if(this->getValue(l, c) == 0 || this->getValue(l, c) == 2 ){
            this->setValue(l, c, 9);
        }
    }
}

/*------------------------------
 * Instancia um Maze a partir
 * de um arquivo texto
------------------------------*/
Maze::Maze(char *path_char){
    int i, j;
    std::string path(path_char);

    FILE *temp = fopen(path.c_str(), "r");
    while(temp == NULL){
        printf("Coundn't find maze file, trying again...\n");

        std::stringstream ss;
        ss << "../" << path;
        path = ss.str();
        printf("Trying at <%s>", path);

        temp = fopen(path.c_str(), "r");
    }

    fscanf(temp, "%d %d",&i, &j);
    this->alloc(i, j);
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            fscanf(temp, "%d", &this->value[i][j]);
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
            case 0:
                glColor3ub(230, 220, 175);
                normal->setPoint(i*25, j*25);
                normal->draw();
                break;
            case 1:
                glColor3ub(0, 0, 255);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glutSolidCube(25);
                glPopMatrix();
                break;
            case 2:
                glColor3ub(205, 130, 65);
                power->setPoint(i*25, j*25);
                power->draw();
                break;
            case 3:
                glColor3ub(255, 255, 0);
                glPushMatrix();
                glTranslated(i*25, j*25, 0);
                glutSolidCube(25);
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
            printf("%d ", this->getValue(i, j));
        }
        printf("\n");
    }
}

void Maze::setPellets(Pellet *normal, Pellet *power){
    this->normal = normal;
    this->power = power;
}

bool Maze::canIncrease(Maze *maze, float x, float y, int direcao){
    int l = inside(x);
    int c = inside(y);
    int v1, v2, v3;
    if(direcao == MAZE_UP){
        v1 = maze->getValue(l-1, c+1);
        v2 = maze->getValue(l, c+1);
        v3 = maze->getValue(l+1, c+1);
        if( c < inside(y+7.5) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside(x-7.25) )
                return 0;
        }
    }
    if(direcao == MAZE_DOWN){
        v1 = maze->getValue(l-1, c-1);
        v2 = maze->getValue(l, c-1);
        v3 = maze->getValue(l+1, c-1);
        if( c > inside(y-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && l < inside(x+7.25) )
                return 0;
            if(v1 == 1 && l > inside(x-7.25) )
                return 0;
        }
    }
    if(direcao == MAZE_LEFT){
        v1 = maze->getValue(l-1, c-1);
        v2 = maze->getValue(l-1, c);
        v3 = maze->getValue(l-1, c+1);
        if( l > inside(x-7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside(y-7.25) )
                return 0;
        }
    }
    if(direcao == MAZE_RIGHT){
        v1 = maze->getValue(l+1, c-1);
        v2 = maze->getValue(l+1, c);
        v3 = maze->getValue(l+1, c+1);
        if( l < inside(x+7.6) ){
            if(v2 == 1)
                return 0;
            if(v3 == 1 && c < inside(y+7.25) )
                return 0;
            if(v1 == 1 && c > inside(y-7.25) )
                return 0;
        }
    }
    return 1;
}