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

void prepareRegisterNewPlane(void) {
    Aviao aviao;
    
    system("clear");       
    inputPlaneCode("informe o codigo do aviao", aviao.codigo, 0);            
    receberString("informe o modelo do aviao", aviao.modelo, MODELO_SIZE);        
    aviao.capacidade = receberInteiro("informe a capacidade do aviao", 0, 9999);
    receberString("informe o nome do cliente", aviao.nomeCliente, NAME_SIZE);
    receberString("informe o pais de origem", aviao.paisOrigem, 2);   
    if(persistPlane(&aviao,"planes.dat") == 1) 
        puts("problema ao registrar aviao / tente novamente");    
    else 
        puts(" aviao registrado com sucesso");    
    getchar();
}

/* Objetivo: preparar o objeto aviao para ser atualizado*/
void preparePlaneUpdate() {
    Aviao aviao;
    
    // 1. Encontrar o aviao pelo id
    inputPlaneCode("informe o codigo do aviao que deseja alterar", aviao.codigo, PLANE_CODE_SIZE);
    /* 2. Procurar o aviao informado em arquivo 
         o metodo isPlaneCodeValid retorna 1 se o aviao foi encontrado, e a instancia
         retorna populada */
    if(isPlaneCodeValid(aviao.codigo) == 0) return;    
    if(updatePlane(&aviao) == 0) 
        puts("registro atualizado com sucesso");
    else
        puts("erro ao atualizar registro"); 
    free(&aviao);
}
/* Objetivo: Alterar os dados de um aviao que não realizou nenhum teste
 */
int deletePlane(Aviao *aviao) {
    if(isDeletionAllowed(aviao->codigo) == 0) {
      /*1. abrir arquivo novo temporario e escrever o conteudo do arquivo anterior ate a linha do registro
      2. inserir a linha nova no arquivo novo temporario
      3. copiar o restante do arquivo anterior no novo temporario
      4. apagar o arquivo anterior / renomear o arquivo temporario
      5. fechar os dois arquivos
     */
        return 0;
    } else 
        puts("operacao nao autorizada | aviao ja realizou testes");
    return 1;
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
    //System("rm aviao.dat; mv aviaoTMP.dat aviao.dat"); 
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
    
    fflush(stdin);
    pFile = openStream("aviao.dat","rb");      
    if(pFile != NULL) {        
        while(! (ret = feof(pFile))) {                       
            if(fread(&aviao,sizeof(aviao),1,pFile)==1){    
              if(strcmp(aviao.codigo,code) == 0) {
                  fclose(pFile);
                  puts("codigo repetido");                  
                  return 1;
               }
            }
        }
        fclose(pFile);
    }   
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

