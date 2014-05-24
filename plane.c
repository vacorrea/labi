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
    do {    
        receberString("informe o codigo do aviao", aviao.codigo, 0, PLANE_CODE_SIZE);        
    }while(isPlaneCodeValid(aviao.codigo) == 1);
    receberString("informe o modelo do aviao", aviao.modelo, 0, MODELO_SIZE);        
    aviao.capacidade = receberInteiro("informe a capacidade do aviao", 0, 9999);
    receberString("informe o nome do cliente", aviao.nomeCliente, 0, NAME_SIZE);
    receberString("informe o pais de origem", aviao.paisOrigem, 0, NAME_SIZE);   
    if(registerNewPlane(aviao) == 1)
        puts("problema ao registrar aviao / tente novamente");
    else
        puts(" aviao registrado com sucesso");
}
/* Objetivo: efetuar o registro do aviao*/
int registerNewPlane(Aviao aviao) {
    return persistPlane(&aviao,"planes.dat");      
}

void preparePlaneUpdate() {
    Aviao aviao;
    
    // 1. Encontrar o aviao pelo id
    receberString("informe o codigo do aviao que deseja alterar", aviao.codigo, 0, PLANE_CODE_SIZE);
    /* 2. Procurar o aviao informado em arquivo 
         o metodo isPlaneCodeValid retorna 1 se o aviao foi encontrado, e a instancia
         retorna populada */
    if(isPlaneCodeValid(aviao.codigo) == 0) return;    
    if(updatePlane(&aviao) == 0)
        puts("registro atualizado com sucesso");
    else
        puts("erro ao atualizar registro");    
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
    /* verificar se o aviao ja realizou testes atraves da chave estrangeira no
      arquivo de testes*/
    
    return 0;
}
/* Objetivo: Alterar um aviao
 */
int updatePlane(Aviao *aviao) {  
    /*1. abrir arquivo novo temporario e escrever o conteudo do arquivo anterior ate a linha do registro
      2. inserir a linha nova no arquivo novo temporario
      3. copiar o restante do arquivo anterior no novo temporario
      4. apagar o arquivo anterior / renomear o arquivo temporario
      5. fechar os dois arquivos
     */
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
    pFile = openStream("planes.dat","rb");      
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
    puts("codigo nao encontrado");    
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

