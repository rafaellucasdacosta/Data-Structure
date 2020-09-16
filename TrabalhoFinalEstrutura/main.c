//Ramon Garcia Camargo, 400978
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "TFE.h"

int main()
{
    PONT raizRA = inicializaArvore();
    PONT raizNome = inicializaArvore();
    PONTLIST aux;
    ALUNO aux2;
    LISTA listAlunos;
    ALUNO novoAluno;
    int opcao = 0;
    char auxChar[200];
    int auxRA = 0;

    inicializaLista(&listAlunos);

    while(1){ //Entra em um loop infinito para mostrar o menu e seleção de opção
        menu(); //chamar função menu, simplesmente printa o menu
        printf("Digite a opcao desejada: "); //usuário insere a opção desejada de acordo com o menu
        scanf("%d", &opcao);
        system ("cls"); //limpa a tela após a seleção

        switch (opcao){ //Inicia um Switch Case para a ação selecionada
            case 1:
                printf("\nCursos: \n10- Agronomia \n11- Veterinaria \n12- CC\n13- Biologia \n14- SI \n15- Enfermagem \n\nRA deve possuir 6 digitos!\n ");
                fflush(stdin);
                printf("\nNome Aluno: ");
                gets(auxChar);
                strcpy(novoAluno.nome, auxChar);
                fflush(stdin);
                printf("\nNúmero do RA: ");
                scanf("%d", &novoAluno.RA);
                fflush(stdin);
                novoAluno.curso = setCurso(novoAluno.RA);
                if(novoAluno.curso != -1){
                    inserirFinal(&listAlunos, novoAluno);
                    PONTLIST aux = listAlunos.inicio;
                    while(aux!=NULL){
                        ALUNO *aux2 = &aux->aluno;
                        raizNome = insereNome(raizNome, aux2);
                        raizRA= insereRA(raizRA, aux2);
                        aux = aux->prox;
                    }
                        /*
                    inserirDesordenado(&listAlunos, novoAluno);
                    aux2 = listAlunos.inicio->aluno;
                    raizNome = insereNome(raizNome, aux2);
                    raizRA = insereRA(raizRA, aux2);
                    */
                }
                else{
                    printf("\nCurso inválido!");
                }
                break;

            case 2:
                fflush(stdin);
                aux2 = salvarInfo(&listAlunos, 1);
                raizRA = removerNome(raizRA, aux2.RA);
                raizNome = removerNome(raizNome, aux2.nome);
                removerListaNome(&listAlunos, aux2.nome);
                /*
                fflush(stdin);
                printf("\nNome do aluno a ser removido: ");
                gets(auxChar);
                raizRA = removerNome(raizRA, auxChar);
                raizNome = removerNome(raizNome, auxChar);
                removerListaNome(&listAlunos, auxChar);
                */
                break;

            case 3:
                fflush(stdin);
                aux2 = salvarInfo(&listAlunos, 2);
                raizRA = removerRA(raizRA, aux2.RA);
                raizNome = removerRA(raizNome, aux2.RA);
                removerListaRA(&listAlunos, aux2.RA);
                /*
                fflush(stdin);
                printf("\nRA do aluno a ser removido: ");
                scanf("%d", &auxRA);
                raizRA = removerRA(raizRA, auxRA);
                raizNome = removerRA(raizNome, auxRA);
                removerListaRA(&listAlunos, auxRA);
                */
                break;

            case 4:
                fflush(stdin);
                printf("\nNome do aluno a ser buscado: ");
                gets(auxChar);
                buscarNome(raizNome, auxChar);
                break;

            case 5:
                printf("\nRA do aluno a ser buscado: ");
                scanf("%d", &auxRA);
                buscarRA(raizRA, auxRA);
                break;

            case 6:
                printf("\nCursos: \n10- Agronomia \n11- Veterinaria \n12- CC\n13- Biologia \n14- SI \n15- Enfermagem \nSelecione algum curso: ");
                scanf("%d", &auxRA);
                buscarTodosAlunosCurso(raizRA, auxRA);
                break;

            case 7:
                printf("\nPre ordem arvore RA: \n");
                leituraPreOrdem(raizRA);
                printf("\n\nPre ordem arvore nome: \n");
                leituraPreOrdem(raizNome);
                break;
            case 8:
                reinicializar(&listAlunos);
                reinicializarArvore(raizRA);
                reinicializarArvore(raizNome);
                return 0;
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    }
    return 0;
}
