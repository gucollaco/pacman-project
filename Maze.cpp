#include <stdio.h>
#include <GL/glut.h>
#include "Pellet.cpp"

/*-----------------------------
 * Define estrutura de Maze.
------------------------------*/
class Maze{
private:
    int **value;     // S�o atributos
    int lin, col;
    Pellet *normal, *power;
public:
    Maze(char *path);
    Maze(int lines, int columns);
    void alloc(int lines, int columns);
    void setValue(int line, int column, int value);
    int getValue(int line, int column);
    void setPellets(Pellet *normal, Pellet *power);
    void colisaoPellet(float x, float y, float r);
    void show();
    void draw();
};

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
    float res = value + 12.5;
    res = res/25;
    return res;
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
Maze::Maze(char *path){
    FILE *temp = fopen(path, "r");
    int i, j;
//    printf("%s\n", path);
    if(temp == NULL) printf("erro arquivo\n");
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
