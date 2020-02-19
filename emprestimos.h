#pragma once
#include "alunos.h"
#include "livros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tpEmprestimo{
    int dia;
    int mes;
    int dia_devolucao;
    int mes_devolucao;
    int tombo_emprestimo;
    int pront_emprestimo;
    char sit;
};
struct tpEmprestimo ler_registro_emprestimo(int posicao){
    FILE *arquivo;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;

    arquivo = fopen("emprestimos.dat", "rb");

    fseek(arquivo, posicao * sizeof(struct tpEmprestimo), SEEK_SET);
    fread(&emprestimo, sizeof(struct tpEmprestimo), 1, arquivo);

    fclose(arquivo);
    return emprestimo;
}

int localizar_emprestimo(int tombo){
    FILE *arquivo;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;

    int posicao = -2;
    int i = 0;

    arquivo = fopen("emprestimos.dat", "rb");

    if(arquivo == NULL){
        return -1;
    }

    fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo);

    while(!feof(arquivo) && posicao == -2){
        
        if(emprestimo.tombo_emprestimo == tombo){
            posicao = i;
        }

        fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo);
        i++;
    }
    fclose(arquivo);
    return posicao;
}

int localizar_emprestimo_pront(int prontuario){
    FILE *arquivo;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;

    int posicao = -2;
    int i = 0;

    arquivo = fopen("emprestimos.dat", "rb");

    if(arquivo == NULL){
        return -1;
    }

    fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo);

    while(!feof(arquivo) && posicao == -2){
        
        if(emprestimo.pront_emprestimo == prontuario){
            posicao = i;
        }

        fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo);
        i++;
    }
    fclose(arquivo);
    return posicao;
}

void imprimir_emprestimo_linha(struct tpEmprestimo emprestimo){
    printf("%d\t %d\t %d\t %d\t", emprestimo.dia,emprestimo.mes,emprestimo.dia_devolucao,emprestimo.mes_devolucao);
    printf("%d\t %d\t %c\t\n\n",emprestimo.tombo_emprestimo, emprestimo.pront_emprestimo, emprestimo.sit);
    
}

void incluir_emprestimo(){
    FILE *arquivo_emprestimo, *arquivo_livro;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;
    int posicao_aluno;
    int posicao_livro;

    arquivo_emprestimo = fopen("emprestimos.dat", "ab");
    arquivo_livro = fopen("livros.dat", "rb+");

        printf("Digite o tombo do livro que será emprestado...: ");
        scanf("%d",&emprestimo.tombo_emprestimo);
            posicao_livro = localizar_livro(emprestimo.tombo_emprestimo);
            livro = ler_registro_livro(posicao_livro);
            imprimir_livro_linha(livro);
            
                if(emprestimo.tombo_emprestimo == livro.tombo){
                    emprestimo.tombo_emprestimo = livro.tombo;
                }
        
    if(livro.situacao == 'D'){
        printf("    Inclusão de Emprestimo  \n\n");
        
        livro.situacao = 'E';
        
        printf("Digite o dia em que o livro foi pego...: ");
        scanf("%d",&emprestimo.dia);

        printf("Digite o mes em que o livro foi pego...: ");
        scanf("%d",&emprestimo.mes);

        emprestimo.dia_devolucao = emprestimo.dia+7;
        emprestimo.mes_devolucao = emprestimo.mes;

        if(emprestimo.dia_devolucao > 30)
                {
                emprestimo.dia_devolucao = emprestimo.dia_devolucao - 30;
                emprestimo.mes_devolucao = emprestimo.mes + 1;
            }
        if(emprestimo.mes_devolucao > 12){
            emprestimo.mes_devolucao = emprestimo.mes_devolucao - 12;
        }
            printf("Dia de devolucao...: %d\n",emprestimo.dia_devolucao);
            printf("Mes de devolucao...: %d\n",emprestimo.mes_devolucao);

        printf("Digite o prontuario do aluno...: ");
        scanf("%d",&emprestimo.pront_emprestimo);
            posicao_aluno = localizar_aluno(emprestimo.pront_emprestimo);
            alunos = ler_registro_aluno(posicao_aluno);
                if(emprestimo.pront_emprestimo == alunos.pront){
                    emprestimo.pront_emprestimo = alunos.pront;
                }

        emprestimo.sit = 'P';
        livro.situacao = 'E';

        fseek(arquivo_livro, posicao_livro*sizeof(struct tplivro),SEEK_SET);
        fwrite(&livro, sizeof(struct tplivro),1,arquivo_livro);

        fwrite(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo_emprestimo);
        fclose(arquivo_livro);
        fclose(arquivo_emprestimo); 
    }
    else{
        printf("Livro está emprestado ou nao existe\n");
        fclose(arquivo_emprestimo);
        fclose(arquivo_livro);
    }   
}

void apresentar_emprestimo_aluno(){
    FILE *arquivo_emprestimo;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;
    int posicao;
    int aux_emp_pront;
    int posicao_emp;

    arquivo_emprestimo = fopen("emprestimos.dat", "rb");

    printf("Digite o prontuario do Aluno que deseja procurar...: ");
    scanf("%d",&aux_emp_pront);

    posicao = localizar_aluno(aux_emp_pront);
    alunos = ler_registro_aluno(posicao);

    posicao_emp = localizar_emprestimo_pront(aux_emp_pront);
    emprestimo = ler_registro_emprestimo(posicao_emp);

        if(aux_emp_pront == alunos.pront){
            
            imprimir_emprestimo_linha(emprestimo);
        }
        else
        {
            printf("Aluno não encontrado\n");
        }
        fclose(arquivo_emprestimo);
   
}

void emprestimos_curso(){
    FILE *arquivo_emprestimo, *arquivo_alunos;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;
    char curso_emp[4];
    int cont = 0;

    arquivo_emprestimo = fopen("emprestimos.dat", "rb");
    arquivo_alunos = fopen("alunos.dat", "rb");

    printf("Digite o curso que deseja saber a quantidade de emprestimos: ");
    gets(curso_emp);
    
    fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo_emprestimo);
    fread(&alunos, sizeof(struct tpAluno),1,arquivo_alunos);
    while(!feof(arquivo_emprestimo)){
        if(strcmp(curso_emp,alunos.curso) == 0){
            cont++;
        }
        fread(&alunos, sizeof(struct tpAluno),1,arquivo_alunos);
        fread(&emprestimo, sizeof(struct tpEmprestimo),1,arquivo_emprestimo);
    }
        printf("Quantidadde de emprestimos de %s: %d\n", curso_emp, cont);
        fclose(arquivo_emprestimo);
        fclose(arquivo_alunos);
}

void apresentar_atrasados(){
    FILE *arquivo_emprestimo;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;

    int dia_emp;
    int mes_emp;
    int auxiliar_atraso;
    int pos_livro;

    arquivo_emprestimo = fopen("emprestimos.dat", "rb");

        printf("Digite o dia...: ");
        scanf("%d",&dia_emp);

        printf("Digite o mes...: ");
        scanf("%d",&mes_emp);

        fread(&emprestimo, sizeof(struct tpEmprestimo),1, arquivo_emprestimo);
        while(!feof(arquivo_emprestimo)){
            if((mes_emp > emprestimo.mes_devolucao) || (mes_emp == emprestimo.mes_devolucao && dia_emp > emprestimo.dia_devolucao)){
                if(emprestimo.sit == 'P'){

                    auxiliar_atraso = emprestimo.tombo_emprestimo;
                    pos_livro = localizar_livro(auxiliar_atraso);
                    livro = ler_registro_livro(pos_livro);
                    imprimir_livro_linha(livro);

                }
            }
        fread(&emprestimo, sizeof(struct tpEmprestimo),1, arquivo_emprestimo);
        }
        fclose(arquivo_emprestimo);
} 

void devolucao_livro(){
     FILE *arquivo_emprestimo, *arquivo_livro;

    struct tpEmprestimo emprestimo;
    struct tplivro livro;
    struct tpAluno alunos;
    int tombo_digitado;
    int posicao_tab;
    int posicao_livro;
    char op_devolucao;

    arquivo_emprestimo = fopen("emprestimos.dat", "rb+");
    arquivo_livro = fopen("livros.dat", "rb+");

        printf("Digite o codigo do livro que deseja devolver...: ");
        scanf("%d%*C",&tombo_digitado);

        posicao_livro = localizar_livro(tombo_digitado);
        livro = ler_registro_livro(posicao_livro);
        imprimir_livro_linha(livro);
        printf("\n");
        posicao_tab = localizar_emprestimo(tombo_digitado);
        emprestimo = ler_registro_emprestimo(posicao_tab);
        imprimir_emprestimo_linha(emprestimo);
        printf("\n");

        if(emprestimo.sit == 'P'){
            printf("S - Sim\t N - Não\n");
            printf("Deseja realmente devolver o livro...: \n");
            scanf("%c",&op_devolucao);

                if(op_devolucao == 'S'){

                    livro.situacao = 'D';
                    fseek(arquivo_livro,posicao_livro * sizeof(struct tplivro), SEEK_SET);
                    fwrite(&livro, sizeof(struct tplivro),1,arquivo_livro);
                    printf("Situacao livro: %c\n",livro.situacao);
                    printf("Situacao Emprestimo: %c\n",emprestimo.sit);
                    emprestimo.sit = 'F';
                    fseek(arquivo_emprestimo, posicao_tab * sizeof(struct tpEmprestimo), SEEK_SET);
                    fwrite(&emprestimo, sizeof(struct tpEmprestimo),1, arquivo_emprestimo);
                    printf("Situacao Emprestimo: %c\n",emprestimo.sit);
                    printf("O livro foi devolvido\n");
                }
        }
        fclose(arquivo_emprestimo);
        fclose(arquivo_livro);
}

/*void main(){
    int op;
    char opcao_livro;
    char opcao_aluno;

        do{
        printf("\n");
        printf("1 - Incluir livro\n");
        printf("2 - Incluir Aluno\n");
        printf("3 - Alterar livro\n");
        printf("4 - Alterar Aluno\n");
        printf("5 - Apresentar livro\n");
        printf("6 - Apresentar Aluno\n");
        printf("7 - Mostrar todos os livros\n");
        printf("8 - Mostrar todos os Alunos\n");
        printf("9 - Exclusão Lógica Livro\n");
        printf("10 - Exclusão Lógica Aluno\n");
        printf("11 - Recuperação Lógica Livro\n");
        printf("12 - Recuperação Lógica Aluno\n");
        printf("13 - Incluir um Emprestimo\n");
        printf("14 - Apresentar Emprestimo\n");
        printf("15 - Apresentar emprestimos por curso\n");
        printf("16 - Apresentar livros disponiveis\n");
        printf("17 - Apresentar atrasados\n");
        printf("18 - Devolucao de um Livro\n");



        printf("\n0 - Sair do programa\n");

        printf("Digite a opcao desejada...: ");
        scanf("%d%*c",&op);
         

        switch(op){
            case 1: incluir_livro();
                break;

            case 2: incluir_aluno();
                break;

            case 3: alterar_livro();
                break;

            case 4: alterar_aluno();
                break;

            case 5: apresentar_livro();
                break;

            case 6: apresentar_aluno();
                break;

            case 7: imprimir_relacao_livro();
                break;

            case 8: imprimir_relacao_aluno();
                break;

            case 9: exclusao_logica_livro();
                break;

            case 10: exclusao_logica_aluno();
                break;

            case 11: recuperar_livro();
                break;

            case 12: recuperar_aluno();
                break;

            case 13: incluir_emprestimo();
                break;

            case 14: apresentar_emprestimo_aluno();
                break;

            case 15: emprestimos_curso();
                break;
        
            case 16: apresentar_disponiveis();
                break;
            
            case 17: apresentar_atrasados();
                break;

            case 18: devolucao_livro();
                break;

            default: break;
        } 
    }while(op != 0);
}*/