#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

//FUNÇÃO QUE INICIALIZA A ARVORE
PONTEIROARVORE inicializaArvore(){
    return(NULL);
}
//FUNÇÃO QUE INICIALIZA A LISTA
void inicializaLista(LISTACONTROLE* l){
    l->inicio = NULL;
}

//FUNÇÃO QUE CRIA O NÓ DO ALUNO
PONTEIROARVORE criaNo(ALUNO* aluno){
    PONTEIROARVORE novoNo = (PONTEIROARVORE)malloc(sizeof(NO));
    novoNo->aluno = aluno;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->h = 0;
    return(novoNo);
}

//FUNÇÃO QUE RETORNA O MAIOR VALOR ENTRE E e I
int max(int e, int i){
    if(e > i){
        return e;
    }
    return i;
}

//FUNÇÃO QUE RETORNA O VALOR DA ALTURA DA RAIZ
int altura(PONTEIROARVORE raiz){
    if(raiz == NULL){
        return -1;
    }
    return raiz->h;
}

//FUNÇÃO QUE RETORNA O FATOR DE BALANCEAMENTO
int fatorBalanceamento(PONTEIROARVORE raiz){
    return(altura(raiz->esq) - altura(raiz->dir));
}

//FUNÇÃO QUE RETORNA O CÁLCULO DA ALTURA DA RAIZ
int defineAltura(PONTEIROARVORE p){
    return(max(altura(p->dir), altura(p->esq))+ 1);
}

//FUNÇÃO QUE REALIZA UMA ROTAÇÃO SIMPLES A DIREITA
PONTEIROARVORE rotDireita(PONTEIROARVORE raiz){
    PONTEIROARVORE temp;
    temp = raiz->esq;
    raiz->esq = temp->dir;
    temp->dir = raiz;
    raiz->h = defineAltura(raiz);
    temp->h = defineAltura(temp);
    return temp;
}

//FUNÇÃO QUE REALIZA UMA ROTAÇÃO SIMPLES A ESQUERDA
PONTEIROARVORE rotEsquerda(PONTEIROARVORE raiz){
    PONTEIROARVORE aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->h = defineAltura(raiz);
    aux->h = defineAltura(aux);
    return aux;
}

//FUNÇÃO QUE REALIZA UMA ROTAÇÃO DUPLA ESQUERDA-DIREITA
PONTEIROARVORE rotEsquerdaDireta(PONTEIROARVORE r){
    r->esq = rotEsquerda(r->esq);
    return(rotDireita(r));
}
//FUNÇÃO QUE REALIZA UMA ROTAÇÃO DUPLA DIREITA-ESQUERDA
PONTEIROARVORE rotDireitaEsquerda(PONTEIROARVORE r){
    r->dir = rotDireita(r->dir);
    return(rotEsquerda(r));
}

//FUNÇÃO QUE VERIFICA A ROTAÇÃO NECESSÁRIA E A CHAMA. É PASSADO POR PARAMETRO A RAIZ DA ARVORE.
PONTEIROARVORE rotacao(PONTEIROARVORE raiz){
    //VERIFICA O FATOR DO NÓ QUE ESTÁ DESBALANCEADO
    if(fatorBalanceamento(raiz) >= 2){
            //VERIFICA O FATOR DO FILHO DO NÓ QUE ESTÁ DESBALANCEADO
        if(fatorBalanceamento(raiz->esq) == 0 || fatorBalanceamento(raiz->esq) == -1){
            raiz = rotDireita(raiz);
        }else{
            raiz = rotEsquerdaDireta(raiz);
        }
    }
    //VERIFICA O FATOR DO NÓ QUE ESTÁ DESBALANCEADO
    if(fatorBalanceamento(raiz) <= -2){
        //VERIFICA O FATOR DO FILHO DO NÓ QUE ESTÁ DESBALANCEADO
        if(fatorBalanceamento(raiz->dir) == 0 || fatorBalanceamento(raiz->dir) == -1){
            raiz = rotEsquerda(raiz);
        }else{
            raiz = rotDireitaEsquerda(raiz);
        }
    }
    return(raiz);
}

//FUNÇÃO QUE INSERE O RA NA ÁRVORE E CHAMA A FUNÇÃO QUE VERIFICA SE A ÁRVORE ESTÁ BALANCEADA. A ARVORE É PERCORRIDA ATÉ ENCONTRAR O LOCAL DO NOVO NÓ
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

//FUNÇÃO QUE INSERE O NOME ORDENADAMENTE NA ÁRVORE E CHAMA A FUNÇÃO QUE VERIFICA SE A ÁRVORE ESTÁ BALANCEADA. A ARVORE É PERCORRIDA ATÉ ENCONTRAR O LOCAL DO NOVO NÓ
PONTEIROARVORE insereNome(PONTEIROARVORE raiz, ALUNO* aluno){
    if(raiz == NULL){
        return(criaNo(aluno));
    }
    //COMPARA SE O NOME JÁ FOI INSERIDO
    if(strcmp(aluno->nome, raiz->aluno->nome) < 0){
        raiz->esq = insereNome(raiz->esq, aluno);
        raiz = rotacao(raiz);
    }else{
        if(strcmp(aluno->nome, raiz->aluno->nome) > 0){
            raiz->dir = insereNome(raiz->dir, aluno);
            raiz = rotacao(raiz);
        }else{
            printf("Já existe aluno cadastrado com esse nome!\n");
        }
    }
    raiz->h = defineAltura(raiz);;
    return(raiz);
}

//FUNÇÃO QUE INSERE OS ALUNOS NA LISTA, QUE SERÁ USADA PARA VERIFICAR SE O ALUNO JÁ FOI CADASTRADO POSTERIORMENTE
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

//FUNÇÃO QUE CHAMA A FUNÇÃO DE BUSCA PARA VERIFICAR SE O RA ESTÁ NA LISTA E ENTÃO REMOVE O RA
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

//FUNÇÃO QUE BUSCA O NÓ RA PARA EXCLUIR
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

//FUNÇÃO QUE REMOVE O RA
PONTEIROARVORE removerRa(PONTEIROARVORE raiz, int ra){
    if(!raiz){
        printf("Aluno não encontrado!\n");
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

//FUNÇÃO QUE BUSCA NA LISTA O NÓ NOME A SER EXCLUÍDO
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


//FUNÇÃO QUE REMOVE O RA
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

//FUNÇÃO QUE VERIFICA SE O ELEMENTO A SER INSERIDO JÁ NÃO FOI INSERIDO ANTERIORMENTE E IMPEDE A DUPLICAÇÃO DOS REGISTROS
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

//FUNÇÃO QUE VERIFICA SE O ELEMENTA JÁ ESTÁ INSERIDO NA LISTA
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

//PROCURA O NÓ PELO RA E O RETORNA SE FOR ENONTRADO
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

//FUNÇÃO QUE PROCURA O NÓ PELO NOME E O RETORNA SE FOR ENCONTRADO
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

//FUNÇÃO QUE DESTRÓI A ARVORE E DESALOCA A MEMÓRIA
void destruirArvore(PONTEIROARVORE raiz){
    if(raiz != NULL){
        destruirArvore(raiz->dir);
        destruirArvore(raiz->esq);
        free(raiz);
    }
}

//FUNÇÃO REINICIALIZA A LISTA E CHAMA A FUNÇÃO QUE LIBERA OS ESPAÇOS DE MEMÓRIA QUE ESTAVAM ALOCADOS
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

//FUNÇÃO QUE FAZ A BUSCA DO CURSO ESCOLHIDO PELO USUÁRIO
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
