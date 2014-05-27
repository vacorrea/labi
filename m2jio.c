#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m2jio.h"


/* Objetivo: apresentar mensagens  */
void apresentarMensagem(char *message) {
    puts(message);
}

int displayMenu(void) {
    
    int opcao = 0;
    
    fpurge(stdin);
    system("clear");
    puts("informe a opcao desejada");
    puts(" 1 - AVIAO | incluir novo / alterar / excluir dados");
    puts(" 2 - PISTAS DE TESTES | incluir novo / alterar dados");
    puts(" 3 - TESTES | incluir novo / alterar / excluir dados");    
    puts(" 4 - Relatórios ");
    puts(" 0 - Sair ");
    opcao = receberInteiro("",0, 5);     
    return opcao;
}
void planeMenu(void) {
    int opcao=0;
    
    fpurge(stdin);
    system("clear");
    puts("1 - Cadastrar Novo Aviao");
    puts("2 - Atualizar Aviao");
    puts("3 - Excluir Avião");
    puts("4 - Listar arquivo de avioes");
    opcao = receberInteiro("",1,4);
    switch(opcao) {
        case 1: prepareForRegister();
            break;            
        case 2: prepareForUpdate();                
            break;            
        case 3: excludePlane();
            break;
        case 4: listarAvioes();
            break;
    }
}

/* Objetivo: Receber o codigo do aviao*/
void inputPlaneCode(char *message, char *array, int min) {
    char *pattern = "AAA9999";
    
    do {
        receberString(message, array,PLANE_CODE_SIZE);
        if((strlen(array) == min) || (strlen(array) > 7))
            puts("tamanho de codigo invalido");        
    }while((strlen(array) == min) ||  (strlen(array) > 7));    
}
/* Objetivo: receber e tratar o endereco */
void inputAddress(char *message, char *array, int min, int max) {
    do {
        receberString(message, array, max);
    }while(sizeof(*array) == min);
}

/* input data */
void receberString(char *message, char *array, int max) {    
    
    fpurge(stdin);    
    do {
        puts(message);
        fgets(array,max,stdin);    
        if(array[strlen(array)] == '\n')
            array[strlen(array)] = '\0';
        if(strlen(array) == 0)
            puts("preencha o campo");
    }while(strlen(array) == 0);
}
/* Objetivo: receber float
 */
float receberFloat(char *message, float min, float max) {
    float value = 0.0;
    int ret =0;
    
    fpurge(stdin);
    do {
        puts(message);
        ret = scanf("%f",&value);
        if(ret == 1) 
           if((value < min) || (value > max))
                puts("dado invalido");
    }while((ret == 0) || (value < min) || (value > max));
    fpurge(stdin);
    return value;
}
/* Objetivo: Receber valor inteiro
 * bugs: não está limpando o buffer, testei com somente o scanf mas não funcionou.
 */
int receberInteiro(char *message, int min, int max) {    
    int variable = 0,ret;
    do {
        puts(message);
        fpurge(stdin);        
        ret = scanf("%d",&variable);
          if(ret == 1)
            if((variable < min) || (variable > max))
                puts("valor invalido");
    }while(ret == 0 || variable < min || variable > max);
    fpurge(stdin);
    return variable;
    
}
/* Objetivo: encontrar o proximo valor a ser utilizado como chave para a pista
 */
int getNextValue(char * fileName) {
    return 1;
}

/* Objetivo: persistir dados de uma estrutura qualquer
 */
int persistData(void *pointer, char *fileName) {
    FILE *pFile = openStream(fileName, "ab");
    
    switch(sizeof(pointer)) {        
                break;  
       default : puts("erro"); break;
    }    
    if(pFile != NULL) { 
        fwrite(pointer,sizeof(Aviao),1, pFile);
    }
}
/* Objetivo: abrir stream
 */
FILE * openStream(char *fileName, char *mode) {
    FILE *arq;
    arq = fopen(fileName,mode);
    if(arq == NULL)
        puts("erro ao abrir arquivo, tente novamente");  
    return arq;
}
/* Objetivo: verificar se o caminho para o arquivo está disponivel
 */
int isPathValid(char *fileName) {
    FILE *pFile = fopen(fileName, "rb");
    if(pFile == NULL)
        puts("falha na abertura do arquivo");
    fclose(pFile);
}