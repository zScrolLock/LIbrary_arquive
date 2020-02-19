#pragma once
#include <ctype.h>
#include "emprestimos.h"

struct tplivro{
    int tombo;
    char titulo[40];
    char autor[40];
    char ano[5];
    char situacao;
    int status;
};

struct auxiliar_livro{
    int tombo_aux;
    char titulo_aux[40];
    char autor_aux[40];
    char ano_aux[5];
    char situacao_aux;
};

struct tplivro ler_registro_livro(int posicao)
{
    FILE *arquivo;

    struct tplivro livro;

    arquivo = fopen("livros.dat", "rb");

    fseek(arquivo, posicao * sizeof(struct tplivro), SEEK_SET);
    fread(&livro, sizeof(struct tplivro), 1, arquivo);

    fclose(arquivo);
    return livro;
}

void incluir_livro(){

    FILE *arquivo;
    struct tplivro livro;

    int auxiliar_tombo;
    int aux;

    arquivo = fopen("livros.dat", "ab");

    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo\n");
        printf("Ele será criado\n");
        
        arquivo = fopen("alunos.dat", "wb");
        
        if(arquivo == NULL){
            printf("Não foi possivel criar ou abrir o arquivo\n");
            exit(1);
        }
    }
    
    printf("Inclusão de Livro\n\n");

    printf("Digite o Tombo...: ");
    fflush(stdin);
    scanf("%d%*c",&auxiliar_tombo);

    aux = localizar_livro(auxiliar_tombo);

        if(aux == -2){
            livro.tombo = auxiliar_tombo;

            printf("Digite o Titulo do Livro..: ");
            fflush(stdin);
            gets(livro.titulo);
            
            printf("Digite o Autor do Livro..: ");
            fflush(stdin);
            gets(livro.autor);

            printf("Digite o Ano do Livro..: ");
            fflush(stdin);
            gets(livro.ano);

            livro.situacao = 'D';

            livro.status = 1;
            
            imprimir_livro_linha(livro);
            fwrite(&livro, sizeof(struct tplivro),1,arquivo);
            fclose(arquivo);
        }
        else{
            printf("Esse tombo já existe\n");
            fclose(arquivo);
        }
}

void imprimir_livro_linha(struct tplivro livro){
    printf("%d\t %s\t %s\t %s\t %c\t\n", livro.tombo, livro.titulo, livro.autor, livro.ano, livro.situacao);
    
}

void imprimir_todos_livros(){
    FILE *arquivo;

    struct tplivro livro;
    
    arquivo = fopen("livros.dat", "rb");
    
    if(arquivo == NULL){
        printf("Não foi possivel ler o arquivo ou não há livros a serem impressos\n");
        exit(1);
    }
    else{
        fread(&livro, sizeof(struct tplivro),1,arquivo);

        while(!feof(arquivo)){
            printf("\n");
            imprimir_livro_linha(livro); 
            fread(&livro, sizeof(struct tplivro),1,arquivo);
        }
        fclose(arquivo);
    }
}

void imprimir_relacao_livro(){
    FILE *arquivo;

    struct tplivro livro;
    
    arquivo = fopen("livros.dat", "rb");
    
    if(arquivo == NULL){
        printf("Não foi possivel ler o arquivo ou não há livros a serem impressos\n");
        exit(1);
    }
    else{
        fread(&livro, sizeof(struct tplivro),1,arquivo);

        while(!feof(arquivo)){
            if(livro.status == 1){
                printf("\n");
                imprimir_livro_linha(livro); 
            }
            fread(&livro, sizeof(struct tplivro),1,arquivo);
        }
        fclose(arquivo);
    }
}

int localizar_livro(int tombo){
    FILE *arquivo;

    struct tplivro livro;

    int posicao = -2;
    int i = 0;

    arquivo = fopen("livros.dat", "rb");

    if(arquivo == NULL){
        return -1;
    }

    fread(&livro, sizeof(struct tplivro),1,arquivo);

    while(!feof(arquivo) && posicao == -2){
        
        if(livro.tombo == tombo){
            posicao = i;
        }

        fread(&livro, sizeof(struct tplivro),1,arquivo);
        i++;
    }
    fclose(arquivo);
    return posicao;
}

void apresentar_livro(){

    int tombo;
    int posicao;
    struct tplivro livro;

    printf("Qual o tombo do Livro..: ");
    scanf("%d",&tombo);

    posicao = localizar_livro(tombo);    

    if(posicao == -1){
        printf("Não há livros com esse tombo.\n");
    }else{    
        livro = ler_registro_livro(posicao);

        if(livro.status == 1){
            imprimir_livro_linha(livro);
        }
    }
}

int escrever_livro(struct tplivro livro, int posicao){

    FILE *arquivo;

    arquivo = fopen("livros.dat", "rb+");
    int registro=0;

        fseek(arquivo, 0, SEEK_END);
        registro = ftell(arquivo)/sizeof(struct tplivro);
        
        if(posicao < registro)
        {
            fseek(arquivo, posicao*sizeof(struct tplivro), SEEK_SET);
            fwrite(&livro, sizeof(struct tplivro), 1, arquivo);
            fclose(arquivo);
            return 1;
        }
        fclose(arquivo);
        return 0;
}

void alterar_livro(){
    FILE *arquivo;
    struct tplivro livro;
    struct auxiliar_livro aux;

    int tombo;
    int posicao;

        
        printf("Qual o tombo do livro a ser alterado...: ");
        scanf("%d%*c",&tombo);
        fflush(stdin);

    posicao = localizar_livro(tombo);

    if(posicao == -1){
        printf("Não há livros com esse tombo");
    }
    else{

        arquivo = fopen("livros.dat", "rb");

        fseek(arquivo, posicao * sizeof(struct tplivro), SEEK_SET);
        fread(&livro, sizeof(struct tplivro), 1, arquivo);
        
        printf("Dados do Livro\n");

        imprimir_livro_linha(livro);

        printf("\nDigite os novos dados desse Livro\n");

        fflush(stdin); 
        printf("Digite o Titulo do Livro..: ");
        gets(aux.titulo_aux);
            if(strlen(aux.titulo_aux) > 0){
                strcpy(livro.titulo,aux.titulo_aux);
            }

        fflush(stdin);
        printf("Digite o Autor do Livro..: ");
        gets(aux.autor_aux);
            if(strlen(aux.autor_aux) > 0){
                strcpy(livro.autor,aux.autor_aux);
            }

        fflush(stdin);
        printf("Digite o ano do Livro..: ");
        gets(aux.ano_aux);
            if(strlen(aux.ano_aux) > 0){
                strcpy(livro.ano,aux.ano_aux);
            }

        if(escrever_livro(livro,posicao)==0){
            printf("Não foi possivel alterar\n");
        }
        fclose(arquivo);
    }
}

void exclusao_logica_livro(){
   FILE *arquivo;

    arquivo = fopen("livros.dat", "rb+");

    struct tplivro livro;
    int exclusao_tombo;
    int pos;
    char opcao;
    int retorno;

        imprimir_relacao_livro();
        printf("\n");

        printf("Digite o numero do tombo que deseja excluir...: ");
        scanf("%d%*c",&exclusao_tombo);

        pos = localizar_livro(exclusao_tombo);
        retorno = localizar_emprestimo(exclusao_tombo);

        if(pos != -1 && retorno == -2){
            printf("Você deseja realmente excluir esse livro...: ");
            printf("Digite S para SIM\t");
            printf("Digite N para NÃO\n");
            scanf("%c",&opcao);
                if(opcao == 'S' || opcao == 's'){ 
                    livro = ler_registro_livro(pos);
                    imprimir_livro_linha(livro);
                    livro.status = 0;
                    printf("Exclusão lógica feita com sucesso\n");
                    escrever_livro(livro,pos);
                }
        }
    fclose(arquivo);
}

void exclusao_fisica_livro(){
    FILE *arquivo, *arquivo2;

    arquivo = fopen("livros.dat", "rb");
    arquivo2 = fopen("livros2.dat", "ab");

    struct tplivro livro;
    
    fread(&livro, sizeof(struct tplivro),1,arquivo);

    while(!feof(arquivo)){
        
        if(livro.status == 1){
            fwrite(&livro, sizeof(struct tplivro),1,arquivo2);
        }
        fread(&livro, sizeof(struct tplivro),1,arquivo);  
    }
    fclose(arquivo);
    fclose(arquivo2);
    remove("livros.dat");
    rename("livros2.dat","livros.dat");
}

void recuperar_livro(){
    FILE *arquivo;

    arquivo = fopen("livros.dat", "rb");

    struct tplivro livro;
    int recuperar_tombo;
    int pos;
    char opcao;

        imprimir_todos_livros();
        printf("\n");
        
        printf("Digite o numero do tombo que deseja recuperar...: ");
        scanf("%d%*c",&recuperar_tombo);

        pos = localizar_livro(recuperar_tombo);
        if(pos != -1){
            
            livro = ler_registro_livro(pos);
            imprimir_livro_linha(livro);

            livro.status = 1;
            printf("Recuperação feita com sucesso\n");
            escrever_livro(livro,pos);
            }
        fclose(arquivo);
}

void apresentar_disponiveis(){
    FILE *arquivo;

    struct tplivro livro;
    int posicao_livro;

    arquivo = fopen("livros.dat", "rb");

    if(arquivo == NULL){
        printf("Não foi possivel ler o arquivo ou não há livros a serem impressos\n");
        exit(1);
    }
    else{

        fread(&livro, sizeof(struct tplivro),1,arquivo);

        while(!feof(arquivo)){
            if(livro.situacao == 'D'){
                printf("\n");
                imprimir_livro_linha(livro); 
            }
            fread(&livro, sizeof(struct tplivro),1,arquivo);
        }
        fclose(arquivo);
    }
}