#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tpAluno{
    int pront;
    char nome[40];
    char curso[4];
    int status;
};

struct auxiliar_aluno{
    int pront_aux;
    char nome_aux[40];
    char curso_aux[4];
};

struct tpAluno ler_registro_aluno(int posicao) 
{
    FILE *arquivo;

    struct tpAluno alunos;

    arquivo = fopen("alunos.dat", "rb");

    fseek(arquivo, posicao * sizeof(struct tpAluno), SEEK_SET); 
    fread(&alunos, sizeof(struct tpAluno), 1, arquivo); 

    fclose(arquivo);
    return alunos;
}

void incluir_aluno(){

    FILE *arquivo;
    struct tpAluno alunos;

    int auxiliar_prontuario;
    int aux;

    arquivo = fopen("alunos.dat", "ab");

    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo\n");
        printf("Ele será criado\n");
        
        arquivo = fopen("alunos.dat", "wb");
        
        if(arquivo == NULL){
            printf("Não foi possivel criar ou abrir o arquivo\n");
            exit(1);
        }
    }
    
    printf("Inclusão de Aluno\n\n");

    printf("Digite o prontuario...: ");
    fflush(stdin);
    scanf("%d%*c",&auxiliar_prontuario);

    aux = localizar_aluno(auxiliar_prontuario);

        if(aux == -1){
            alunos.pront = auxiliar_prontuario;
            
            printf("Digite o Nome do Aluno..: ");
            fflush(stdin);
            gets(alunos.nome);

            printf("Digite o Curso do Aluno..: ");
            fflush(stdin);
            gets(alunos.curso);

            alunos.status = 1;
        
            fwrite(&alunos, sizeof(struct tpAluno),1,arquivo);
            fclose(arquivo);
        }
        else{
            printf("Esse prontuario já existe\n");
            fclose(arquivo);
        }
}

void imprimir_aluno_linha(struct tpAluno alunos){
    printf("%d\t %s\t %s\t\n", alunos.pront, alunos.nome, alunos.curso);
    
}

void imprimir_todos_alunos(){
    FILE *arquivo;

    struct tpAluno alunos;
    
    arquivo = fopen("alunos.dat", "rb");
    
    if(arquivo == NULL){
        printf("Não foi possivel ler o arquivo ou não há alunos\n");
        exit(1);
    }
    else{
        fread(&alunos, sizeof(struct tpAluno),1,arquivo);

        while(!feof(arquivo)){
            printf("\n");
            imprimir_aluno_linha(alunos); 
            fread(&alunos, sizeof(struct tpAluno),1,arquivo);
        }
        fclose(arquivo);
    }
}

void imprimir_relacao_aluno(){
    FILE *arquivo;

    struct tpAluno alunos;
    
    arquivo = fopen("alunos.dat", "rb");
    
    if(arquivo == NULL){
        printf("Não foi possivel ler o arquivo ou não há alunos\n");
        exit(1);
    }
    else{
        fread(&alunos, sizeof(struct tpAluno),1,arquivo);

        while(!feof(arquivo)){
            if(alunos.status == 1){
                printf("\n");
                imprimir_aluno_linha(alunos); 
            }
            fread(&alunos, sizeof(struct tpAluno),1,arquivo);
        }
        fclose(arquivo);
    }
}

int localizar_aluno(int pront){
    FILE *arquivo;

    struct tpAluno alunos;

    int posicao = -1;
    int i = 0;

    arquivo = fopen("alunos.dat", "rb");

    if(arquivo == NULL){
        return -1;
    }

    fread(&alunos, sizeof(struct tpAluno),1,arquivo);

    while(!feof(arquivo) && posicao == -1){
        
        if(alunos.pront == pront){
            posicao = i;
        }

        fread(&alunos, sizeof(struct tpAluno),1,arquivo);
        i++;
    }
    fclose(arquivo);
    return posicao;
}

void apresentar_aluno(){

    FILE *arquivo;

    int pront;
    int posicao;
    struct tpAluno alunos;

    printf("Qual o prontuario do Aluno..: ");
    scanf("%d",&pront);

    posicao = localizar_aluno(pront);

    if(posicao == -1 || alunos.status == 0){
        printf("Não há alunos com esse prontuario.\n");
    }else{

        arquivo = fopen("alunos.dat", "rb");

        fseek(arquivo, posicao * sizeof(struct tpAluno), SEEK_SET);
        fread(&alunos, sizeof(struct tpAluno), 1, arquivo);
        imprimir_aluno_linha(alunos);

        fclose(arquivo);
    }
}

int escrever_aluno(struct tpAluno alunos, int posicao){

    FILE *arquivo;

    arquivo = fopen("alunos.dat", "rb+");
    int registro=0;

        fseek(arquivo, 0, SEEK_END);
        registro = ftell(arquivo)/sizeof(struct tpAluno);
        
        if(posicao < registro)
        {
            fseek(arquivo, posicao*sizeof(struct tpAluno), SEEK_SET);
            fwrite(&alunos, sizeof(struct tpAluno), 1, arquivo);
            fclose(arquivo);
            return 1;
        }
        fclose(arquivo);
        return 0;
}

void alterar_aluno(){
    FILE *arquivo;
    struct tpAluno alunos;
    struct auxiliar_aluno aux;

    int pront;
    int posicao;

        
        printf("Qual o prontuario do aluno a ser alterado...: ");
        scanf("%d%*c",&pront);
        fflush(stdin);

    posicao = localizar_aluno(pront);

    if(posicao == -1){
        printf("Não há alunos com esse prontuario\n");
    }
    else{

        arquivo = fopen("alunos.dat", "rb");

        fseek(arquivo, posicao * sizeof(struct tpAluno), SEEK_SET);
        fread(&alunos, sizeof(struct tpAluno), 1, arquivo);
        
        printf("Dados do Aluno\n");

        imprimir_aluno_linha(alunos);

        printf("\nDigite os novos dados desse Aluno\n");

        fflush(stdin); 
        printf("Digite o Nome do Aluno..: ");
        gets(aux.nome_aux);
            if(strlen(aux.nome_aux) > 0){
                strcpy(alunos.nome,aux.nome_aux);
            }

        fflush(stdin);
        printf("Digite o Curso do Aluno..: ");
        gets(aux.curso_aux);
            if(strlen(aux.curso_aux) > 0){
                strcpy(alunos.curso,aux.curso_aux);
            }

        fflush(stdin);

        if(escrever_aluno(alunos,posicao)==0){
            printf("Não foi possivel alterar\n");
        }
        fclose(arquivo);
    }
}

void exclusao_logica_aluno(){
   FILE *arquivo;

    arquivo = fopen("alunos.dat", "rb+");

    struct tpAluno alunos;
    int exclusao_pront;
    int retorno;
    int pos;
    char opcao;

        imprimir_relacao_aluno();
        printf("\n");

        printf("Digite o numero do tombo que deseja excluir...: ");
        scanf("%d%*c",&exclusao_pront);

        pos = localizar_aluno(exclusao_pront);
        retorno = localizar_emprestimo_pront(exclusao_pront);

        if(pos != -1 && retorno == -2){
            printf("Você deseja realmente excluir esse Aluno...: ");
            printf("Digite S para SIM\t");
            printf("Digite N para NÃO\n");
            scanf("%c",&opcao);
                if(opcao == 'S' || opcao == 's'){ 
                    alunos = ler_registro_aluno(pos);
                    imprimir_aluno_linha(alunos);
                    alunos.status = 0;
                    printf("Exclusão lógica feita com sucesso\n");
                    escrever_aluno(alunos,pos);
                }
        }
    fclose(arquivo);
}

void exclusao_fisica_aluno(){
    FILE *arquivo, *arquivo2;

    arquivo = fopen("alunos.dat", "rb");
    arquivo2 = fopen("alunos2.dat", "ab");

    struct tpAluno alunos;
    
    fread(&alunos, sizeof(struct tpAluno),1,arquivo);

    while(!feof(arquivo)){
        
        if(alunos.status == 1){
            fwrite(&alunos, sizeof(struct tpAluno),1,arquivo2);
        }
        fread(&alunos, sizeof(struct tpAluno),1,arquivo);  
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove("alunos.dat");
    rename("alunos2.dat","alunos.dat");
}

void recuperar_aluno(){
    FILE *arquivo;

    arquivo = fopen("alunos.dat", "rb");

    struct tpAluno alunos;
    int recuperar_pront;
    int pos;
    char opcao;

        imprimir_todos_alunos();
        printf("\n");
        
        printf("Digite o numero do prontuario que deseja recuperar...: ");
        scanf("%d%*c",&recuperar_pront);

        pos = localizar_aluno(recuperar_pront);
        if(pos != -1){
            
            alunos = ler_registro_aluno(pos);
            imprimir_aluno_linha(alunos);

            alunos.status = 1;
            printf("Recuperação feita com sucesso\n");
            escrever_aluno(alunos,pos);
            }
        fclose(arquivo);
}