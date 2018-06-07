#include <stdio.h>
#include <GL/glut.h>
#include "Pellet.cpp"

/*-----------------------------
 * Define estrutura de matriz.
------------------------------*/
struct Matrix{
private:
    int **value;     // São atributos
    int lin, col;
public:
    Matrix(char *path);
    Matrix(int lines, int columns);
    void alloc(int lines, int columns);
    void setValor(int line, int column, int value);
    int getValue(int line, int column);
    void show();
    void draw(Pellet *pel, Pellet *ppel);
};

Matrix::Matrix(int line, int column){
    this->alloc(line, column);
}

/*------------------------------
 * Instancia uma matriz a partir
 * de um arquivo texto
------------------------------*/
Matrix::Matrix(char *path){
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
}

/*-----------------------------
 * Cria matriz com o numero de
 * lines = lin e columns = col
------------------------------*/
void Matrix::alloc(int lin, int col){
    int i;
    this->value = (int**) malloc(sizeof(int*)*lin);
    for(i = 0; i < lin; i++){
        this->value[i] = (int*) malloc(sizeof(int)*col);
    }
    this->lin = lin;
    this->col = col;
}


void Matrix::draw(Pellet *pel, Pellet *ppel){
    int i, j;
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            switch(this->getValue(i, j)){
            case 0:
                glColor3ub(230, 220, 175);
                glPushMatrix();
                glTranslatef(i*25, j*25, 0);
                glutSolidSphere(5, 20, 20);
                glPopMatrix();
                pel->draw(i*25, j*25);
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
                glPushMatrix();
                glTranslatef(i*25, j*25, 0);
                glutSolidSphere(7, 20, 20);
                glPopMatrix();
                ppel->draw(i*25, j*25);
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

void Matrix::setValor(int line, int column, int value){
    this->value[line][column] = value;
}

int Matrix::getValue(int line, int column){
    return value[line][column];
}

void Matrix::show(){
    int i, j;
    for(i = 0; i < this->lin; i++){
        for(j = 0; j < this->col; j++){
            printf("%d ", this->getValue(i, j));
        }
        printf("\n");
    }
}
