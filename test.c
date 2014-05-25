#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m2jio.h"

/*
typedef struct Teste {
    char codigoAviaoFK[PLANE_CODE_SIZE];
    int codigoPistaFK;
    int data;  // coletada pelo ntp no formato DDMMYYYY
    float velocidadeMaximaTeste;
} Teste;
 */

/* Objetivo: receber dados de um teste
 *      o codigo do aviao pode ser selecionado de uma lista 
 */
void prepareNewTest() {
    Teste teste;
    
    system("clear");
    // verificar se  codigo existe
    receberString("informe o codigo do aviao", teste.codigoAviaoFK, PLANE_CODE_SIZE);     
    // verificar se o codigo existe
    teste.codigoPistaFK = receberInteiro("informe o codigo da pista", 0, 99999);
    //teste.data = system("date");
    teste.velocidadeMaximaTeste = receberFloat("informe a velocidade maxima obtida no teste", 1, 99999);
    if(persistTeste(&teste) == 1) 
        puts("erro ao salvar arquivo, tente novamente");           
    else puts("arquivo salvo com        sucesso"); 
    getchar();
}
int persistTeste(Teste *teste) {
    
    FILE *pFile = openStream("teste.dat","ab");
    if(pFile != NULL) {
        fwrite(teste, sizeof(Teste), 1, pFile);              
        fclose(pFile);
        return OPERATION_SUCCESS;    
    }
    fclose(pFile);
    return OPERATION_ERROR;
}
/* Objetivo: verificar se o aviao ja realizou algum teste
 */
int findTestByPlaneID(char *key) {
    FILE *pFile = openStream("teste.dat", "rb");
    
    Teste teste;
    if(pFile != NULL) {
        while(!feof(pFile)){
            fread(&teste,sizeof(Teste),1,pFile);
            if(strcmp(teste.codigoAviaoFK,key) == 0) 
                return 1;
        }
    }
    return 0;
}

