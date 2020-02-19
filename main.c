#pragma once
#include "emprestimos.h"

void main(){
    int op;
    char opcao_livro;
    char opcao_aluno;

        do{
        printf("\n");
        printf("1 - Incluir livro\n");
        printf("2 - Incluir Aluno\n");
        printf("3 - Apresentar relação de Alunos\n");
        printf("4 - Apresentar relação de Livros\n");
        printf("5 - Alterar livro\n");
        printf("6 - Alterar Aluno\n");
        printf("7 - Apresentar livro\n");
        printf("8 - Apresentar Aluno\n");
        printf("9 - Mostrar todos os livros\n");
        printf("10 - Mostrar todos os Alunos\n");
        printf("11 - Exclusão Lógica Livro\n");
        printf("12 - Exclusão Lógica Aluno\n");
        printf("13 - Recuperação Lógica Livro\n");
        printf("14 - Recuperação Lógica Aluno\n");
        printf("15 - Incluir um Emprestimo\n");
        printf("16 - Apresentar Emprestimo\n");
        printf("17 - Apresentar emprestimos por curso\n");
        printf("18 - Apresentar livros disponiveis\n");
        printf("19 - Apresentar atrasados\n");
        printf("20 - Devolucao de um Livro\n");
        printf("21 - Apresentar livros disponiveis\n");
        printf("22 - Exclusão Fisica de Livros\n");
        printf("23 - Exclusão Fisica de Aluno\n");


        printf("\n0 - Sair do programa\n");

        printf("Digite a opcao desejada...: ");
        scanf("%d%*c",&op);
         

        switch(op){
            case 1: incluir_livro();
                break;

            case 2: incluir_aluno();
                break;

            case 3: imprimir_relacao_aluno();
                break;

            case 4:imprimir_relacao_livro();
                break;

            case 5: alterar_livro();
                break;

            case 6: alterar_aluno();
                break;

            case 7: apresentar_livro();
                break;

            case 8: apresentar_aluno();
                break;

            case 9: imprimir_relacao_livro();
                break;

            case 10: imprimir_relacao_aluno();
                break;

            case 11: exclusao_logica_livro();
                break;

            case 12: exclusao_logica_aluno();
                break;

            case 13: recuperar_livro();
                break;

            case 14: recuperar_aluno();
                break;

            case 15: incluir_emprestimo();
                break;

            case 16: apresentar_emprestimo_aluno();
                break;

            case 17: emprestimos_curso();
                break;
        
            case 18: apresentar_disponiveis();
                break;
            
            case 19: apresentar_atrasados();
                break;

            case 20: devolucao_livro();
                break;

            case 21: apresentar_disponiveis();
                break;

            case 22: exclusao_fisica_livro();
                break;

            case 23: exclusao_fisica_aluno();
                break; 

            default: break;
        } 
    }while(op != 0);
}