#ifndef TFE_H_INCLUDED
#define TFE_H_INCLUDED

/*
CURSOS
Agronomia= 10
Veterinaria= 11
CC= 12
Biologia= 13
SI= 14
Enfermagem= 15
*/
typedef struct{
    int RA;
    char nome[50];
    int curso;
}ALUNO;

typedef struct aux{
    ALUNO aluno;
    struct ALUNO* prox;
}ELEMENTO;

typedef ELEMENTO* PONTLIST;

typedef struct{
    PONTLIST inicio;
}LISTA;

typedef struct auxArv{
    ALUNO *aluno;
    struct auxArv *esq, *dir;
    int h;
}NO;

typedef NO* PONT;

PONT arvoreRA;
PONT arvoreNome;


PONT inicializaArvore();
void inicializaLista(LISTA*);
void inserirLista(LISTA* , ALUNO);
void reinicializar(LISTA*);
void inserirDesordenado(LISTA*, ALUNO);
void inserirFinal(LISTA*, ALUNO);
PONT criaNovoNo(ALUNO*);

int max(int, int);
int altura(PONT);
int fatorB(PONT);

PONT direita(PONT);
PONT esquerda(PONT);
PONT esquerdaDireita(PONT);
PONT direitaEsquerda(PONT);
PONT rotacao(PONT);

PONT insereRA(PONT, ALUNO*);
PONT insereNome(PONT, ALUNO*);

void removerListaRA(LISTA*, int);
void removerListaNome(LISTA*, char[200]);

PONT removerRA(PONT, int);
PONT removerNome(PONT, char[200]);

ALUNO salvarInfo(LISTA*, int);

PONT procuraNoRA(PONT, PONT);
PONT procuraNoNome(PONT, PONT);
void buscarRA(PONT, int);
void buscarNome(PONT, char[200]);
int setCurso(int );
void menu();

void leituraPreOrdem(PONT);
void reinicializarArvore(PONT);
#endif // TFE_H_INCLUDED
