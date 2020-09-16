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
int max(int a, int b);
int altura(PONTEIROARVORE raiz);
int fatorBalanceamento(PONTEIROARVORE raiz);
int definirAltura(PONTEIROARVORE p);
PONTEIROLISTA insere(LISTACONTROLE* l, ALUNO aluno);
PONTEIROLISTA buscaLista(LISTACONTROLE* l,ALUNO aluno, PONTEIROLISTA* ant);
PONTEIROARVORE inicializaArvore();
PONTEIROARVORE criaNo(ALUNO* aluno);
PONTEIROARVORE rotEsquerda(PONTEIROARVORE raiz);
PONTEIROARVORE rotEsquerdaDireta(PONTEIROARVORE r);
PONTEIROARVORE rotdireitaEsquerda(PONTEIROARVORE r);
PONTEIROARVORE rotacao(PONTEIROARVORE raiz);
PONTEIROARVORE rotDireita(PONTEIROARVORE raiz);
PONTEIROARVORE insereRA(PONTEIROARVORE raiz, ALUNO* aluno);
PONTEIROARVORE insereNome(PONTEIROARVORE raiz, ALUNO* aluno);
PONTEIROLISTA buscaRemover(LISTACONTROLE* l, int ra, PONTEIROLISTA* ant);
PONTEIROARVORE procuraNoNome(PONTEIROARVORE q, PONTEIROARVORE p);
PONTEIROARVORE procuraNoRa(PONTEIROARVORE q, PONTEIROARVORE p);
PONTEIROARVORE removerRa(PONTEIROARVORE raiz, int ra);
PONTEIROARVORE removerNome(PONTEIROARVORE raiz, char nome[MAX]);
PONTEIROARVORE procurarRa(PONTEIROARVORE raiz, int RA);
PONTEIROARVORE procurarNome(PONTEIROARVORE raiz, char nome[MAX]);
PONTEIROARVORE reinicializaProg(PONTEIROARVORE* raizRa, PONTEIROARVORE* raizNome, LISTACONTROLE* l);
#endif // ESTRUTURAACAD_H_INCLUDED
