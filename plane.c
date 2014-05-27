/* 
 * File:   plane.c
 * Author: vcorrea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m2jio.h"

/* typedef struct Aviao {
    char codigo[PLANE_CODE_SIZE];
    char modelo[MODELO_SIZE];
    int capacidade;
    char nomeCliente[NAME_SIZE];
    char paisOrigem[NAME_SIZE];
} Aviao;
 */

void prepareForRegister(void) {
    Aviao aviao;
    
    system("clear");    
    do {
        inputPlaneCode("informe o codigo do aviao", aviao.codigo, 0);            
    }while(isPlaneCodeValid(aviao.codigo));
    getPlane(&aviao);
    if(persistPlane(&aviao,"aviao.dat") == 1) 
        puts("problema ao registrar aviao / tente novamente");    
    else 
        puts(" aviao registrado com sucesso");    
    getchar();
}
/* Objetivo: receber os dados comuns de um aviao*/
void getPlane(Aviao *aviao) {
    receberString("informe o modelo do aviao", aviao->modelo, MODELO_SIZE);        
    aviao->capacidade = receberInteiro("informe a capacidade do aviao", 0, 9999);
    receberString("informe o nome do cliente", aviao->nomeCliente, NAME_SIZE);
    receberString("informe o pais de origem", aviao->paisOrigem, 2);   
}
/* Objetivo: Listar os avioes persistidos em arquivo */
void listarAvioes(){
    FILE *pFile = openStream("aviao.dat","rb");
    Aviao aviao;
    
    system("clear");
    if(pFile != NULL) {
        while(!feof(pFile)) {
            fread(&aviao,sizeof(Aviao),1,pFile);
            apresentarAviao(&aviao);
        }
        puts("\n");
        puts("\n");
        getchar();
    }
}
/* Objetivo: apresentar os dados de um aviao em formato tabular*/ 
void apresentarAviao(Aviao *aviao) {
    printf("Codigo: %s  Modelo: %s  Capacidade: %d \n",aviao->codigo, aviao->modelo, aviao->capacidade);
}
/* Objetivo: preparar o objeto aviao para ser atualizado*/
void prepareForUpdate() {
    Aviao aviao;
    
    system("clear");
    // 1. Encontrar o aviao pelo id
    
    inputPlaneCode("informe o codigo do aviao que deseja alterar", aviao.codigo, PLANE_CODE_SIZE); 
    if(isPlaneCodeValid(aviao.codigo) == 0) return;
    getPlane(&aviao);
    if(updatePlane(&aviao) == 0) puts("registro atualizado com sucesso");
    else puts("erro ao atualizar registro");     
}
/* Objetivo: receber os dados do aviao a ser excluido*/
void prepareForDelete() {
    Aviao aviao;
    
    do {
        inputPlaneCode("informe o codigo do aviao que deseja excluir",aviao.codigo,1);
    }while(isPlaneCodeValid(aviao.codigo));
    if(isDeletionAllowed(aviao.codigo) == 0) {
        deletePlane(&aviao);        
    } else 
        puts("operacao nao autorizada | aviao ja realizou testes");    
}
/* Objetivo: Alterar os dados de um aviao que não realizou nenhum teste
 */
int deletePlane(Aviao *aviao) {
    
    int cursor = 0;
    FILE *pFile = openStream("aviao.dat","rb");
    FILE *pFileTMP = openStream("aviaoTMP.dat","ab");
    Aviao aviaoTmp;
    /*1. abrir arquivo novo temporario e copiar o conteudo do arquivo anterior ate a linha do registro
      2. inserir a linha nova no arquivo novo temporario
      3. copiar o restante do arquivo anterior no novo temporario
      4. apagar o arquivo anterior / renomear o arquivo temporario
      5. fechar os dois arquivos
     */
    if((pFile != NULL) && (pFileTMP != NULL)) {
        while(!feof(pFile)) {
            fread(&aviaoTmp,sizeof(Aviao),1,pFile);
            if(strcmp(aviaoTmp.codigo,aviao->codigo) == 0)
                fwrite(aviao,sizeof(Aviao),1,pFileTMP);
            else
                fwrite(&aviaoTmp,sizeof(Aviao),1,pFileTMP);
        }        
    }
    fclose(pFile);
    fclose(pFileTMP);
    system("rm aviao.dat; mv aviaoTMP.dat aviao.dat"); 
    return 0;
}
int isDeletionAllowed(char *key) {
    return findTestByPlaneID(key);    
}

/* Objetivo: Alterar dados de um aviao
 */
int updatePlane(Aviao *aviao) {  
    int cursor = 0;
    FILE *pFile = openStream("aviao.dat","rb");
    FILE *pFileTMP = openStream("aviaoTMP.dat","ab");
    Aviao aviaoTmp;
    /*1. abrir arquivo novo temporario e copiar o conteudo do arquivo anterior ate a linha do registro
      2. inserir a linha nova no arquivo novo temporario
      3. copiar o restante do arquivo anterior no novo temporario
      4. apagar o arquivo anterior / renomear o arquivo temporario
      5. fechar os dois arquivos
     */
    if((pFile != NULL) && (pFileTMP != NULL)) {
        while(!feof(pFile)) {
            fread(&aviaoTmp,sizeof(Aviao),1,pFile);
            if(strcmp(aviaoTmp.codigo,aviao->codigo) == 0)
                fwrite(aviao,sizeof(Aviao),1,pFileTMP);
            else
                fwrite(&aviaoTmp,sizeof(Aviao),1,pFileTMP);
        }        
    }
    fclose(pFile);
    fclose(pFileTMP);
    system("rm aviao.dat; mv aviaoTMP.dat aviao.dat"); 
    return 0;
}
/* Objetivo: encontrar o aviao pelo código 
 * Parametros:
 * Retorno: 1 se foi encontrado | 0 se nao for encontrado
 */
int isPlaneCodeValid(char *code) {
    
    FILE *pFile;
    Aviao aviao;
    int indice=0, ret;
    
    fpurge(stdin);
    pFile = openStream("aviao.dat","rb"); 
    if(pFile != NULL) {                
        while(! (ret = feof(pFile))) {                       
            if(fread(&aviao,sizeof(aviao),1,pFile)==1){    
              if(strcmp(aviao.codigo,code) == 0) {
                  fclose(pFile);
                  puts("codigo encontrado");                  
                  return 1;
               }
            }
        }        
        fclose(pFile);
    } 
    puts("codigo nao encontrado"); getchar();
    return 0;
}
/* Objetivo: Persistir aviao
 */
int persistPlane(Aviao *aviao, char *fileName) {    
    
    FILE *pFile = openStream(fileName,"ab");
    if(pFile != NULL) {
        fwrite(aviao, sizeof(Aviao), 1, pFile);              
        fclose(pFile);
        return OPERATION_SUCCESS;    
    }
    fclose(pFile);
    return OPERATION_ERROR;
}

