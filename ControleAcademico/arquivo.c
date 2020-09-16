#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

//FUN��O QUE INICIALIZA A ARVORE
PONTEIROARVORE inicializaArvore(){
    return(NULL);
}
//FUN��O QUE INICIALIZA A LISTA
void inicializaLista(LISTACONTROLE* l){
    l->inicio = NULL;
}

//FUN��O QUE CRIA O N� DO ALUNO
PONTEIROARVORE criaNo(ALUNO* aluno){
    PONTEIROARVORE novoNo = (PONTEIROARVORE)malloc(sizeof(NO));
    novoNo->aluno = aluno;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->h = 0;
    return(novoNo);
}

//FUN��O QUE RETORNA O MAIOR VALOR ENTRE E e I
int max(int e, int i){
    if(e > i){
        return e;
    }
    return i;
}

//FUN��O QUE RETORNA O VALOR DA ALTURA DA RAIZ
int altura(PONTEIROARVORE raiz){
    if(raiz == NULL){
        return -1;
    }
    return raiz->h;
}

//FUN��O QUE RETORNA O FATOR DE BALANCEAMENTO
int fatorBalanceamento(PONTEIROARVORE raiz){
    return(altura(raiz->esq) - altura(raiz->dir));
}

//FUN��O QUE RETORNA O C�LCULO DA ALTURA DA RAIZ
int defineAltura(PONTEIROARVORE p){
    return(max(altura(p->dir), altura(p->esq))+ 1);
}

//FUN��O QUE REALIZA UMA ROTA��O SIMPLES A DIREITA
PONTEIROARVORE rotDireita(PONTEIROARVORE raiz){
    PONTEIROARVORE temp;
    temp = raiz->esq;
    raiz->esq = temp->dir;
    temp->dir = raiz;
    raiz->h = defineAltura(raiz);
    temp->h = defineAltura(temp);
    return temp;
}

//FUN��O QUE REALIZA UMA ROTA��O SIMPLES A ESQUERDA
PONTEIROARVORE rotEsquerda(PONTEIROARVORE raiz){
    PONTEIROARVORE aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->h = defineAltura(raiz);
    aux->h = defineAltura(aux);
    return aux;
}

//FUN��O QUE REALIZA UMA ROTA��O DUPLA ESQUERDA-DIREITA
PONTEIROARVORE rotEsquerdaDireta(PONTEIROARVORE r){
    r->esq = rotEsquerda(r->esq);
    return(rotDireita(r));
}
//FUN��O QUE REALIZA UMA ROTA��O DUPLA DIREITA-ESQUERDA
PONTEIROARVORE rotDireitaEsquerda(PONTEIROARVORE r){
    r->dir = rotDireita(r->dir);
    return(rotEsquerda(r));
}

//FUN��O QUE VERIFICA A ROTA��O NECESS�RIA E A CHAMA. � PASSADO POR PARAMETRO A RAIZ DA ARVORE.
PONTEIROARVORE rotacao(PONTEIROARVORE raiz){
    //VERIFICA O FATOR DO N� QUE EST� DESBALANCEADO
    if(fatorBalanceamento(raiz) >= 2){
            //VERIFICA O FATOR DO FILHO DO N� QUE EST� DESBALANCEADO
        if(fatorBalanceamento(raiz->esq) == 0 || fatorBalanceamento(raiz->esq) == -1){
            raiz = rotDireita(raiz);
        }else{
            raiz = rotEsquerdaDireta(raiz);
        }
    }
    //VERIFICA O FATOR DO N� QUE EST� DESBALANCEADO
    if(fatorBalanceamento(raiz) <= -2){
        //VERIFICA O FATOR DO FILHO DO N� QUE EST� DESBALANCEADO
        if(fatorBalanceamento(raiz->dir) == 0 || fatorBalanceamento(raiz->dir) == -1){
            raiz = rotEsquerda(raiz);
        }else{
            raiz = rotDireitaEsquerda(raiz);
        }
    }
    return(raiz);
}

//FUN��O QUE INSERE O RA NA �RVORE E CHAMA A FUN��O QUE VERIFICA SE A �RVORE EST� BALANCEADA. A ARVORE � PERCORRIDA AT� ENCONTRAR O LOCAL DO NOVO N�
PONTEIROARVORE insereRA(PONTEIROARVORE raiz, ALUNO* aluno){
    if(raiz == NULL){
        return(criaNo(aluno));
    }
    if(aluno->RA < raiz->aluno->RA){
        raiz->esq = insereRA(raiz->esq, aluno);
        raiz = rotacao(raiz);
    }else{
        if(aluno->RA > raiz->aluno->RA){
            raiz->dir = insereRA(raiz->dir, aluno);
            raiz = rotacao(raiz);
        }
    }
    raiz->h = defineAltura(raiz);
    return(raiz);
}

//FUN��O QUE INSERE O NOME ORDENADAMENTE NA �RVORE E CHAMA A FUN��O QUE VERIFICA SE A �RVORE EST� BALANCEADA. A ARVORE � PERCORRIDA AT� ENCONTRAR O LOCAL DO NOVO N�
PONTEIROARVORE insereNome(PONTEIROARVORE raiz, ALUNO* aluno){
    if(raiz == NULL){
        return(criaNo(aluno));
    }
    //COMPARA SE O NOME J� FOI INSERIDO
    if(strcmp(aluno->nome, raiz->aluno->nome) < 0){
        raiz->esq = insereNome(raiz->esq, aluno);
        raiz = rotacao(raiz);
    }else{
        if(strcmp(aluno->nome, raiz->aluno->nome) > 0){
            raiz->dir = insereNome(raiz->dir, aluno);
            raiz = rotacao(raiz);
        }else{
            printf("J� existe aluno cadastrado com esse nome!\n");
        }
    }
    raiz->h = defineAltura(raiz);;
    return(raiz);
}

//FUN��O QUE INSERE OS ALUNOS NA LISTA, QUE SER� USADA PARA VERIFICAR SE O ALUNO J� FOI CADASTRADO POSTERIORMENTE
PONTEIROLISTA insere(LISTACONTROLE* l, ALUNO aluno){
    PONTEIROLISTA anterior, i;
    i = buscaLista(l, aluno, &anterior);
    if(i != NULL){
        return NULL;
    }
    i = (PONTEIROLISTA) malloc(sizeof(ELEMENTO));
    i->aluno = aluno;
    if(anterior == NULL){
        i->prox = l->inicio;
        l->inicio = i;
    }else{
        i->prox = anterior->prox;
        anterior->prox = i;
    }
    return i;
}

//FUN��O QUE CHAMA A FUN��O DE BUSCA PARA VERIFICAR SE O RA EST� NA LISTA E ENT�O REMOVE O RA
    void removeLista(LISTACONTROLE* l, int ra){
    PONTEIROLISTA anterior, i;
    i = buscaRemover(l, ra, &anterior);
    if(i == NULL){
        return -1;
    }
    if(anterior == NULL){
        l->inicio = i->prox;
    }else{
        anterior->prox = i->prox;
    }
    free(i);
}

//FUN��O QUE BUSCA O N� RA PARA EXCLUIR
PONTEIROARVORE procuraNoRa(PONTEIROARVORE q, PONTEIROARVORE p){
    if(q->aluno->RA == p->aluno->RA){
        q->h = defineAltura(q);
        q = rotacao(q);
        return q;
    }
    if(p->aluno->RA < q->aluno->RA){
        q = procuraNoRa(q->esq, p);
    }else{
        q = procuraNoRa(q->dir, p);
    }
    q->h = defineAltura(q);
    q = rotacao(q);
    return q;
}

//FUN��O QUE REMOVE O RA
PONTEIROARVORE removerRa(PONTEIROARVORE raiz, int ra){
    if(!raiz){
        printf("Aluno n�o encontrado!\n");
    }
    PONTEIROARVORE pai = NULL;

    if(ra < raiz->aluno->RA){
        pai = raiz->esq;
        raiz->esq = removerRa(raiz->esq, ra);
        raiz = rotacao(raiz);
    }else{
        if(ra > raiz->aluno->RA){
            pai = raiz->dir;
            raiz->dir = removerRa(raiz->dir, ra);
            raiz = rotacao(raiz);
        }else{
            if(ra == raiz->aluno->RA){
                PONTEIROARVORE p = NULL, q;
                if(!raiz->esq || !raiz->dir){
                    if(!raiz->esq){
                        q = raiz->dir;
                    }else{
                        q = raiz->esq;
                    }
                }else{
                    p = raiz;
                    q = raiz->esq;
                    while(q->dir){
                        p = q;
                        q = q->dir;
                    }
                    if(p != raiz){
                        p->dir = q->esq;
                        q->esq = raiz->esq;
                    }
                    q->dir = raiz->dir;
                    if(p == raiz){
                        q = rotacao(q);
                    }else{
                        if(p->aluno->RA < q->aluno->RA){
                            q->esq = procuraNoRa(q, p);
                        }else{
                            q->dir = procuraNoRa(q, p);
                        }
                        q->h = defineAltura(q);
                        q = rotacao(q);
                    }
                }
                if(!pai){
                    free(raiz);
                    return(q);
                }

                if(ra < pai->aluno->RA){
                    pai->esq = q;
                }else{
                    pai->dir = q;
                }
                free(raiz);
                q->h = defineAltura(q);
                return q;
            }else{
                printf("Aluno nao Encontrado!\n");
            }
        }
    }
    raiz->h = defineAltura(raiz);
    return raiz;
}

//FUN��O QUE BUSCA NA LISTA O N� NOME A SER EXCLU�DO
PONTEIROARVORE procuraNoNome(PONTEIROARVORE q, PONTEIROARVORE p){
    if(strcmp(q->aluno->nome,p->aluno->nome) == 0){
        q->h = defineAltura(q);
        q = rotacao(q);
        return q;
    }
    if(strcmp(p->aluno->nome,q->aluno->nome) < 0){
        q = procuraNoNome(q->esq, p);
    }else{
        q = procuraNoNome(q->dir, p);
    }
    q->h = defineAltura(q);
    q = rotacao(q);
    return q;
}


//FUN��O QUE REMOVE O RA
PONTEIROARVORE removerNome(PONTEIROARVORE r, char nome[MAX]){
    if(!r){
        printf("Aluno nao Encontrado!\n");
    }
    PONTEIROARVORE pai = NULL;
    if(strcmp(nome,r->aluno->nome) < 0){
        pai = r->esq;
        r->esq = removerNome(r->esq, nome);
        r = rotacao(r);
    }else{
        if(strcmp(nome,r->aluno->nome) > 0){
            pai = r->dir;
            r->dir = removerNome(r->dir, nome);
            r = rotacao(r);
        }else{
            if(strcmp(nome,r->aluno->nome) == 0){
                PONTEIROARVORE p = NULL, q;
                if(!r->esq || !r->dir){
                    if(!r->esq){
                        q = r->dir;
                    }else{
                        q = r->esq;
                    }
                }else{
                    p = r;
                    q = r->esq;
                    while(q->dir){
                        p = q;
                        q = q->dir;
                    }
                    if(p != r){
                        p->dir = q->esq;
                        q->esq = r->esq;
                    }
                    q->dir = r->dir;
                    if(p == r){
                        q = rotacao(q);
                    }else{
                        if(strcmp(p->aluno->nome,q->aluno->nome) < 0){
                            q->esq = procuraNoNome(q, p);
                        }else{
                            q->dir = procuraNoNome(q, p);
                        }
                        q->h = defineAltura(q);
                        q = rotacao(q);
                    }
                }
                if(!pai){
                    free(r);
                    return(q);
                }

                if(strcmp(nome,pai->aluno->nome) < 0){
                    pai->esq = q;
                }else{
                    pai->dir = q;
                }
                free(r);
                q->h = defineAltura(q);
                return q;
            }else{
                printf("Aluno nao Encontrado\n");
            }
        }
    }
    r->h = defineAltura(r);
    return r;
}

//FUN��O QUE VERIFICA SE O ELEMENTO A SER INSERIDO J� N�O FOI INSERIDO ANTERIORMENTE E IMPEDE A DUPLICA��O DOS REGISTROS
PONTEIROLISTA buscaLista(LISTACONTROLE* l,ALUNO aluno, PONTEIROLISTA* ant){
    *ant = NULL;
    PONTEIROLISTA atual = l->inicio;
    while(atual != NULL && (atual->aluno.RA < aluno.RA && (strcmp(aluno.nome, atual->aluno.nome) != 0))){
        *ant = atual;
        atual = atual->prox;
    }
    if(atual != NULL && (atual->aluno.RA == aluno.RA || (strcmp(aluno.nome, atual->aluno.nome) == 0))){
        return atual;
    }
    return NULL;
}

//FUN��O QUE VERIFICA SE O ELEMENTA J� EST� INSERIDO NA LISTA
PONTEIROLISTA buscaRemover(LISTACONTROLE* l, int ra, PONTEIROLISTA* ant){
    *ant = NULL;
    PONTEIROLISTA atual = l->inicio;
    while(atual != NULL && atual->aluno.RA < ra){
        *ant = atual;
        atual = atual->prox;
    }
    if(atual != NULL && atual->aluno.RA == ra){
        return atual;
    }
    return NULL;
}

//PROCURA O N� PELO RA E O RETORNA SE FOR ENONTRADO
PONTEIROARVORE procurarRa(PONTEIROARVORE raiz, int RA){
    if (raiz == NULL){
        return(NULL);
    }
    if(raiz->aluno->RA == RA){
        return raiz;
    }
    if(raiz->aluno->RA > RA){
        return(procurarRa(raiz->esq, RA));
    }else{
        return(procurarRa(raiz->dir, RA));
    }
}

//FUN��O QUE PROCURA O N� PELO NOME E O RETORNA SE FOR ENCONTRADO
PONTEIROARVORE procurarNome(PONTEIROARVORE raiz, char nome[MAX]){
    if (raiz == NULL){
        return(NULL);
    }
    if(strcmp(nome, raiz->aluno->nome) == 0){
        return raiz;
    }
    if(strcmp(nome, raiz->aluno->nome) < 0){
        return(procurarNome(raiz->esq, nome));
    }else{
        return(procurarNome(raiz->dir, nome));
    }
}

//FUN��O QUE DESTR�I A ARVORE E DESALOCA A MEM�RIA
void destruirArvore(PONTEIROARVORE raiz){
    if(raiz != NULL){
        destruirArvore(raiz->dir);
        destruirArvore(raiz->esq);
        free(raiz);
    }
}

//FUN��O REINICIALIZA A LISTA E CHAMA A FUN��O QUE LIBERA OS ESPA�OS DE MEM�RIA QUE ESTAVAM ALOCADOS
PONTEIROARVORE reinicializaProg(PONTEIROARVORE* RARaiz, PONTEIROARVORE* NomeRaiz, LISTACONTROLE* l){
    PONTEIROLISTA aux = l->inicio;
    destruirArvore(*RARaiz);
    *RARaiz = NULL;
    destruirArvore(*NomeRaiz);
    *NomeRaiz = NULL;
    while(aux != NULL){
        l->inicio = aux->prox;
        free(aux);
        aux = l->inicio;
    }
    l->inicio = NULL;
}

//FUN��O QUE FAZ A BUSCA DO CURSO ESCOLHIDO PELO USU�RIO
void buscarCurso(PONTEIROARVORE raiz, int codigoCurso){
    if (raiz != NULL){
        buscarCurso(raiz->esq,codigoCurso);
        if (raiz->aluno->curso==codigoCurso){
            printf("Nome: %s", raiz->aluno->nome);
            printf("\tRA: %i", raiz->aluno->RA);
            printf("\n");
        }
        buscarCurso(raiz->dir,codigoCurso);
    }
    return;
}
