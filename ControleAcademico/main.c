// TRABALHO FINAL DE ESTRUTURA DE DADOS
// SISTEMAS DE INFORMAÇÃO - UENP CLM- 2º ANO
// Aluno: Chayene Goncharenco    RA: 400963
// Aluno: Rafael Lucas da Costa  RA: 400898

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arquivo.h"
#include <stdbool.h>
int main()
{
    setlocale(LC_ALL, "Portuguese");//Permite utilizar acentuação da língua portuguesa
    //Definição das variáveis
    LISTACONTROLE lista;
    ALUNO al;
    PONTEIROLISTA controlePorLista;
    PONTEIROARVORE arvoreRA, arvoreNome;
    PONTEIROARVORE retornoBusca;
    inicializaLista(&lista);
    arvoreRA = inicializaArvore();
    arvoreNome = inicializaArvore();
    int opcao, i=1, cod;
    bool aux=true;
    char nome[50];

    do
    {
        //EXIBE O MENU COM AS OPÇÕES DE ESCOLHA PARA O USUÁRIO;
        printf("  ---------------------------------------\n");
        printf(" |     SISTEMA ACADÊMICO - UENP-CLM      |\n");
        printf(" |---------------------------------------|\n");
        printf(" |      1 -> CADASTRAR NOVO ALUNO        |\n");
        printf(" |      2 -> BUSCAR ALUNO POR RA         |\n");
        printf(" |      3 -> BUSCAR ALUNO POR NOME       |\n");
        printf(" |      4 -> BUSCAR ALUNOS POR CURSO     |\n");
        printf(" |      5 -> REMOVER ALUNO POR RA        |\n");
        printf(" |      6 -> REMOVER ALUNO POR NOME      |\n");
        printf(" |---------------------------------------|\n");
        printf(" |      7 -> SAIR                        |\n");
        printf("  ---------------------------------------");
        printf("  \nO QUE DESEJA FAZER?\n");
        scanf("%i", &opcao);

        switch(opcao)
        {
        case 1: // CASO OPÇÃO SEJA 1 IRÁ CADASTRAR O ALUNO
            system("cls"); // LIMPA A TELA
            aux=true;
            printf("  ---------------------------------------\n");
            printf(" |           CADASTRO DE ALUNOS          |\n");
            printf(" |---------------------------------------|\n");
            printf(" |      CURSOS DISPONÍVEIS NO CAMPUS     |\n");
            printf(" |---------------------------------------|\n");
            printf(" |         10 -> AGRONOMIA               |\n");
            printf(" |         12 -> CIÊNCIA DA COMPUTAÇÃO   |\n");
            printf(" |         20 -> CIÊNCIAS BIOLÓGICAS     |\n");
            printf(" |         30 -> MEDICINA VETERINÁRIA    |\n");
            printf(" |         40 -> SISTEMAS DE INFORMAÇÃO  |\n");
            printf(" |         50 -> ENFERMAGEM              |\n");
            printf("  ---------------------------------------\n");
            printf("\n\n(ATENÇÃO: Os dois primeiros números do RA são\n o código do curso, os 4 últimos correspondem\n a ordem de matrícula do aluno)\n\n");
            fflush(stdin);//LIMPA O BUFFER DO TECLADO
            printf("  \nNOME: ");
            scanf("%s",&al.nome);
            fflush(stdin);//LIMPA O BUFFER DO TECLADO
            printf("  \nRA: ");
            scanf("%i",&al.RA);
            while(al.RA <= 0) //GARANTE QUE O RA SEJA MAOR QUE 0
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |           INSIRA UM RA VÁLIDO.        |\n");
                printf("  ---------------------------------------\n");
                printf("  \nRA: ");
                scanf("%i",&al.RA);
            }
            while(aux) //VERIFICA SE O CÓDIGO DO CURSO INSERIDO É VÁLIDO
            {
                if(al.RA / 10000 == 10
                        || al.RA / 10000 == 12
                        || al.RA / 10000 == 20
                        || al.RA / 10000 == 30
                        || al.RA / 10000 == 40
                        || al.RA / 10000 == 50)
                {
                    al.curso = al.RA / 10000;
                    aux = false;
                }
                else
                {
                    printf("  ---------------------------------------\n");
                    printf(" |                  ERRO!                |\n");
                    printf(" |       CÓDIGO DO CURSO INEXISTENTE,    |\n");
                    printf(" |          INSIRA O RA NOVAMENTE.       |\n");
                    printf("  ---------------------------------------\n");
                    printf("  \nRA: ");
                    scanf("%i",&al.RA);

                }
            }
            controlePorLista = inserir(&lista, al);//CHAMA A FUNÇÃO DE INSERÇÃO
            if(controlePorLista != NULL)
            {
                arvoreNome = insereNome(arvoreNome, &controlePorLista->aluno);//INSERE NA ARVORE O NOME
                arvoreRA = insereRA(arvoreRA, &controlePorLista->aluno);//INSERE NA ARVORE O RA
                system("cls");
                printf("  ---------------------------------------\n");
                printf(" |       ALUNO CADASTRADO COM SUCESSO    |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                system("cls");
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |     RA OU NOME JÁ FORAM CADASTRADOS   |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 2: // CASO A OPÇÃO SEJA 2 IRÁ BUSCAR O ALUNO POR RA
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |          BUSCAR ALUNOS POR RA         |\n");
            printf("  ---------------------------------------\n");
            printf("  \nRA: ");
            scanf("%i",&cod);
            retornoBusca = procurarRa(arvoreRA, cod);//CHAMA A FUNÇÃO QUE FAZ A BUSCA POR RA
            if(retornoBusca == NULL)
            {
                system("cls");
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |         O RA NÃO FOI ENCONTRADO       |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |            ALUNO ENCONTRADO           |\n");
                printf("  ---------------------------------------\n");
                printf("  NOME: %s\n", retornoBusca->aluno->nome);
                printf("  RA: %i\n", retornoBusca->aluno->RA);
                printf("  CURSO: %i\n", retornoBusca->aluno->curso);
                printf("  ---------------------------------------\n");
            }
            break;

        case 3: // CASO A OPÇÃO SEJA 3 IRÁ BUSCAR O ALUNO POR NOME
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |         BUSCAR ALUNOS POR NOME        |\n");
            printf("  ---------------------------------------\n");
            printf("  \nNOME: ");
            scanf("%s", &nome);
            retornoBusca = procurarNome(arvoreNome, nome);//CHAMA A FUNÇÃO QUE IRÁ PROCURAR POR NOME
            if(retornoBusca != NULL)
            {
                printf("  ---------------------------------------\n");
                printf(" |            ALUNO ENCONTRADO           |\n");
                printf("  ---------------------------------------\n");
                printf("  NOME: %s\n", retornoBusca->aluno->nome);
                printf("  RA: %i\n", retornoBusca->aluno->RA);
                printf("  CURSO: %i\n", retornoBusca->aluno->curso);
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |       O ALUNO NÃO FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 4: // CASO A OPÇÃO SEJA 4 IRÁ BUSCAR TODOS OS ALUNOS DE UM CURSO
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |        BUSCAR ALUNOS POR CURSO        |\n");
            printf(" |---------------------------------------|\n");
            printf(" |      CURSOS DISPONÍVEIS NO CAMPUS     |\n");
            printf(" |---------------------------------------|\n");
            printf(" |         10 -> AGRONOMIA               |\n");
            printf(" |         12 -> CIÊNCIA DA COMPUTAÇÃO   |\n");
            printf(" |         20 -> CIÊNCIAS BIOLÓGICAS     |\n");
            printf(" |         30 -> MEDICINA VETERINÁRIA    |\n");
            printf(" |         40 -> SISTEMAS DE INFORMAÇÃO  |\n");
            printf(" |         50 -> ENFERMAGEM              |\n");
            printf("  ---------------------------------------\n");
            printf("  \nCÓDIGO DO CURSO: ");
            scanf("%i",&cod);
            system("cls");
            if (cod==10){
                printf("  ---------------------------------------\n");
                printf(" |          ALUNOS DE AGRONOMIA          |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==12){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE CIÊNCIA DA COMPUTAÇÃO   |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==20){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE CIÊNCIAS BIOLÓGICAS     |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==30){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE MEDICINA VETERINÁRIA    |\n");
                printf("  ---------------------------------------\n");
            }
            if (cod==40){
                printf("  ---------------------------------------\n");
                printf(" |    ALUNOS DE SISTEMAS DE INFORMAÇÃO   |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==50){
                printf("  ---------------------------------------\n");
                printf(" |          ALUNOS DE ENFERMAGEM         |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod!=10 && cod!=12 &&cod!=20 && cod!=30 && cod!=40 && cod!=50){
                system("cls");
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |        CÓDIGO DE CURSO INVÁLIDO       |\n");
                printf("  ---------------------------------------\n");
                break;
            }
            buscarCurso(arvoreRA, cod);//CHAMA A FUNÇÃO QUE FAZ A BUSCA PELO CÓDIGO DO CURSO
            break;

        case 5: // CASO A OPÇÃO SEJA 5 IRÁ EXCLUIR PELO RA
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |        EXCLUSÃO DE ALUNOS POR RA      |\n");
            printf("  ---------------------------------------\n");
            printf("  \nRA: ");
            scanf("%i",&cod);
            retornoBusca = procurarRa(arvoreRA, cod);//CHAMA A FUNÇÃO QUE PROCURA O RA
            if(retornoBusca != NULL)
            {
                arvoreRA = removerRa(arvoreRA, retornoBusca->aluno->RA);//CHAMA A FUNÇÃO QUE RETORNA O RA DA ARVORE
                arvoreNome = removerNome(arvoreNome, retornoBusca->aluno->nome);// CHAMA FUNÇAO QUE RETORNA O NOME DA ARVORE
                removeLista(&lista, retornoBusca->aluno->RA);//CHAMA A FUNÇÃO QUE REMOVE O ALUNO DA LISTA
                printf("  ---------------------------------------\n");
                printf(" |        ALUNO EXCLUÍDO COM SUCESSO     |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |       O ALUNO NÃO FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 6: // CASO A OPÇÃO SEJA 6 IRÁ EXCLUIR O ALUNO PELO NOME
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |      EXCLUSÃO DE ALUNOS POR NOME      |\n");
            printf("  ---------------------------------------\n");
            printf("\nNOME: ");
            scanf("%s", &nome);
            retornoBusca = procurarNome(arvoreNome, nome);//CHAMA A FUNÇÃO QUE FAZ A BUSCA DO ALUNO PELO NOME
            if(retornoBusca != NULL)
            {
                arvoreRA = removerRa(arvoreRA, retornoBusca->aluno->RA);//CHAMA A FUNÇÃO QUE RETORNA O RA DA ARVORE
                arvoreNome = removerNome(arvoreNome, retornoBusca->aluno->nome);// CHAMA A FUNÇÃO QUE RETORNA O NOME DA ÁRVORE
                removeLista(&lista, retornoBusca->aluno->RA);//REMOVE O ALUNO DA LISTA
                printf("  ---------------------------------------\n");
                printf(" |        ALUNO EXCLUÍDO COM SUCESSO     |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |       O ALUNO NÃO FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;
        case 7: // CASO A OPÇÃO SEJA 7 IRÁ ENCERRAR O SISTEMA E LIBERAR OS ESPAÇOS DA MEMÓRIA
            reinicializaProg(&arvoreRA, &arvoreNome, &lista);//CHAMA A FUNÇÃO PARA LIBERAR ESPAÇO DA MEMÓRIA
            break;
        default:
            system("cls");
            printf("OPÇÃO INVÁLIDA, TENTE NOVAMENTE!");
        }
    }
    while(opcao!=7);
    return 0;
}
