// TRABALHO FINAL DE ESTRUTURA DE DADOS
// SISTEMAS DE INFORMA��O - UENP CLM- 2� ANO
// Aluno: Chayene Goncharenco    RA: 400963
// Aluno: Rafael Lucas da Costa  RA: 400898

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arquivo.h"
#include <stdbool.h>
int main()
{
    setlocale(LC_ALL, "Portuguese");//Permite utilizar acentua��o da l�ngua portuguesa
    //Defini��o das vari�veis
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
        //EXIBE O MENU COM AS OP��ES DE ESCOLHA PARA O USU�RIO;
        printf("  ---------------------------------------\n");
        printf(" |     SISTEMA ACAD�MICO - UENP-CLM      |\n");
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
        case 1: // CASO OP��O SEJA 1 IR� CADASTRAR O ALUNO
            system("cls"); // LIMPA A TELA
            aux=true;
            printf("  ---------------------------------------\n");
            printf(" |           CADASTRO DE ALUNOS          |\n");
            printf(" |---------------------------------------|\n");
            printf(" |      CURSOS DISPON�VEIS NO CAMPUS     |\n");
            printf(" |---------------------------------------|\n");
            printf(" |         10 -> AGRONOMIA               |\n");
            printf(" |         12 -> CI�NCIA DA COMPUTA��O   |\n");
            printf(" |         20 -> CI�NCIAS BIOL�GICAS     |\n");
            printf(" |         30 -> MEDICINA VETERIN�RIA    |\n");
            printf(" |         40 -> SISTEMAS DE INFORMA��O  |\n");
            printf(" |         50 -> ENFERMAGEM              |\n");
            printf("  ---------------------------------------\n");
            printf("\n\n(ATEN��O: Os dois primeiros n�meros do RA s�o\n o c�digo do curso, os 4 �ltimos correspondem\n a ordem de matr�cula do aluno)\n\n");
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
                printf(" |           INSIRA UM RA V�LIDO.        |\n");
                printf("  ---------------------------------------\n");
                printf("  \nRA: ");
                scanf("%i",&al.RA);
            }
            while(aux) //VERIFICA SE O C�DIGO DO CURSO INSERIDO � V�LIDO
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
                    printf(" |       C�DIGO DO CURSO INEXISTENTE,    |\n");
                    printf(" |          INSIRA O RA NOVAMENTE.       |\n");
                    printf("  ---------------------------------------\n");
                    printf("  \nRA: ");
                    scanf("%i",&al.RA);

                }
            }
            controlePorLista = inserir(&lista, al);//CHAMA A FUN��O DE INSER��O
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
                printf(" |     RA OU NOME J� FORAM CADASTRADOS   |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 2: // CASO A OP��O SEJA 2 IR� BUSCAR O ALUNO POR RA
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |          BUSCAR ALUNOS POR RA         |\n");
            printf("  ---------------------------------------\n");
            printf("  \nRA: ");
            scanf("%i",&cod);
            retornoBusca = procurarRa(arvoreRA, cod);//CHAMA A FUN��O QUE FAZ A BUSCA POR RA
            if(retornoBusca == NULL)
            {
                system("cls");
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |         O RA N�O FOI ENCONTRADO       |\n");
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

        case 3: // CASO A OP��O SEJA 3 IR� BUSCAR O ALUNO POR NOME
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |         BUSCAR ALUNOS POR NOME        |\n");
            printf("  ---------------------------------------\n");
            printf("  \nNOME: ");
            scanf("%s", &nome);
            retornoBusca = procurarNome(arvoreNome, nome);//CHAMA A FUN��O QUE IR� PROCURAR POR NOME
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
                printf(" |       O ALUNO N�O FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 4: // CASO A OP��O SEJA 4 IR� BUSCAR TODOS OS ALUNOS DE UM CURSO
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |        BUSCAR ALUNOS POR CURSO        |\n");
            printf(" |---------------------------------------|\n");
            printf(" |      CURSOS DISPON�VEIS NO CAMPUS     |\n");
            printf(" |---------------------------------------|\n");
            printf(" |         10 -> AGRONOMIA               |\n");
            printf(" |         12 -> CI�NCIA DA COMPUTA��O   |\n");
            printf(" |         20 -> CI�NCIAS BIOL�GICAS     |\n");
            printf(" |         30 -> MEDICINA VETERIN�RIA    |\n");
            printf(" |         40 -> SISTEMAS DE INFORMA��O  |\n");
            printf(" |         50 -> ENFERMAGEM              |\n");
            printf("  ---------------------------------------\n");
            printf("  \nC�DIGO DO CURSO: ");
            scanf("%i",&cod);
            system("cls");
            if (cod==10){
                printf("  ---------------------------------------\n");
                printf(" |          ALUNOS DE AGRONOMIA          |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==12){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE CI�NCIA DA COMPUTA��O   |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==20){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE CI�NCIAS BIOL�GICAS     |\n");
                printf("  ---------------------------------------\n");
            }
            else if (cod==30){
                printf("  ---------------------------------------\n");
                printf(" |     ALUNOS DE MEDICINA VETERIN�RIA    |\n");
                printf("  ---------------------------------------\n");
            }
            if (cod==40){
                printf("  ---------------------------------------\n");
                printf(" |    ALUNOS DE SISTEMAS DE INFORMA��O   |\n");
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
                printf(" |        C�DIGO DE CURSO INV�LIDO       |\n");
                printf("  ---------------------------------------\n");
                break;
            }
            buscarCurso(arvoreRA, cod);//CHAMA A FUN��O QUE FAZ A BUSCA PELO C�DIGO DO CURSO
            break;

        case 5: // CASO A OP��O SEJA 5 IR� EXCLUIR PELO RA
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |        EXCLUS�O DE ALUNOS POR RA      |\n");
            printf("  ---------------------------------------\n");
            printf("  \nRA: ");
            scanf("%i",&cod);
            retornoBusca = procurarRa(arvoreRA, cod);//CHAMA A FUN��O QUE PROCURA O RA
            if(retornoBusca != NULL)
            {
                arvoreRA = removerRa(arvoreRA, retornoBusca->aluno->RA);//CHAMA A FUN��O QUE RETORNA O RA DA ARVORE
                arvoreNome = removerNome(arvoreNome, retornoBusca->aluno->nome);// CHAMA FUN�AO QUE RETORNA O NOME DA ARVORE
                removeLista(&lista, retornoBusca->aluno->RA);//CHAMA A FUN��O QUE REMOVE O ALUNO DA LISTA
                printf("  ---------------------------------------\n");
                printf(" |        ALUNO EXCLU�DO COM SUCESSO     |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |       O ALUNO N�O FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;

        case 6: // CASO A OP��O SEJA 6 IR� EXCLUIR O ALUNO PELO NOME
            system("cls");
            fflush(stdin);
            printf("  ---------------------------------------\n");
            printf(" |      EXCLUS�O DE ALUNOS POR NOME      |\n");
            printf("  ---------------------------------------\n");
            printf("\nNOME: ");
            scanf("%s", &nome);
            retornoBusca = procurarNome(arvoreNome, nome);//CHAMA A FUN��O QUE FAZ A BUSCA DO ALUNO PELO NOME
            if(retornoBusca != NULL)
            {
                arvoreRA = removerRa(arvoreRA, retornoBusca->aluno->RA);//CHAMA A FUN��O QUE RETORNA O RA DA ARVORE
                arvoreNome = removerNome(arvoreNome, retornoBusca->aluno->nome);// CHAMA A FUN��O QUE RETORNA O NOME DA �RVORE
                removeLista(&lista, retornoBusca->aluno->RA);//REMOVE O ALUNO DA LISTA
                printf("  ---------------------------------------\n");
                printf(" |        ALUNO EXCLU�DO COM SUCESSO     |\n");
                printf("  ---------------------------------------\n");
            }
            else
            {
                printf("  ---------------------------------------\n");
                printf(" |                  ERRO!                |\n");
                printf(" |       O ALUNO N�O FOI ENCONTRADO      |\n");
                printf("  ---------------------------------------\n");
            }
            break;
        case 7: // CASO A OP��O SEJA 7 IR� ENCERRAR O SISTEMA E LIBERAR OS ESPA�OS DA MEM�RIA
            reinicializaProg(&arvoreRA, &arvoreNome, &lista);//CHAMA A FUN��O PARA LIBERAR ESPA�O DA MEM�RIA
            break;
        default:
            system("cls");
            printf("OP��O INV�LIDA, TENTE NOVAMENTE!");
        }
    }
    while(opcao!=7);
    return 0;
}
