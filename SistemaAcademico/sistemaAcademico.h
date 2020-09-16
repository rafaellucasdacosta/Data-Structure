#ifndef ESTRUTURAACAD_H_INCLUDED
#define ESTRUTURAACAD_H_INCLUDED
#define MAX 50

//STRUCT DO ALUNO;
typedef struct{
    int RA;
    char nome[MAX];
    int curso;
}ALUNO;

//STRUCT NÓ PARA SER UTILIZADA NO ALUNO
typedef struct auxArvoreAvl{
    ALUNO* aluno;
    struct auxArvoreAvl *esq, *dir;
    int h;
}NO;

//STRUCT DO ELEMENTO PARA SER UTILIZADA NA LISTA
typedef struct auxLista{
    ALUNO aluno;
    struct auxLista* prox;
}ELEMENTO;

//PONTEIRO QUE APONTA PARA A ARVORE
typedef NO* PONTEIROARVORE;

//PONTEIRO QUE APONTA PARA A LISTA;
typedef ELEMENTO* PONTEIROLISTA;

//STRUCT DA LISTA COM O PONTEIRO QUE INDICA SEU INÍCIO
typedef struct{
    PONTEIROLISTA inicio;
}LISTACONTROLE;

//PROTÓTIPO DAS FUNÇÕES UTILIZADAS
void inicializaLista(LISTACONTROLE* l);
void buscarCurso(PONTEIROARVORE raiz, int codigoCurso);
void destruirArv(PONTEIROARVORE raiz);
void removeLista(LISTACONTROLE* l, int ra);
int maior(int a, int b);
int altura(PONTEIROARVORE raiz);
int fatorBalanceamento(PONTEIROARVORE raiz);
int definirAltura(PONTEIROARVORE p);

PONTEIROLISTA insere(LISTACONTROLE* l, ALUNO aluno);
PONTEIROLISTA buscaLista(LISTACONTROLE* l,ALUNO aluno, PONTEIROLISTA* ant);
PONTEIROARVORE inicializaArvore();
PONTEIROARVORE criaNo(ALUNO* aluno);
PONTEIROARVORE rotacaoEsquerda(PONTEIROARVORE raiz);
PONTEIROARVORE rotacaoEsquerdaDireta(PONTEIROARVORE r);
PONTEIROARVORE rotacaodireitaEsquerda(PONTEIROARVORE r);
PONTEIROARVORE rotacao(PONTEIROARVORE raiz);
PONTEIROARVORE rotacaoDireita(PONTEIROARVORE raiz);
PONTEIROARVORE insereRA(PONTEIROARVORE raiz, ALUNO* aluno);
PONTEIROARVORE insereNome(PONTEIROARVORE raiz, ALUNO* aluno);
PONTEIROLISTA buscaRemove(LISTACONTROLE* l, int ra, PONTEIROLISTA* ant);
PONTEIROARVORE procuraNoNome(PONTEIROARVORE q, PONTEIROARVORE p);
PONTEIROARVORE procuraNoRa(PONTEIROARVORE q, PONTEIROARVORE p);
PONTEIROARVORE removeRa(PONTEIROARVORE raiz, int ra);
PONTEIROARVORE removeNome(PONTEIROARVORE raiz, char nome[MAX]);
PONTEIROARVORE procuraRa(PONTEIROARVORE raiz, int RA);
PONTEIROARVORE procuraNome(PONTEIROARVORE raiz, char nome[MAX]);
PONTEIROARVORE reinicializaSistema(PONTEIROARVORE* raizRa, PONTEIROARVORE* raizNome, LISTACONTROLE* l);
#endif // ESTRUTURAACAD_H_INCLUDED
