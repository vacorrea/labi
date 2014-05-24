#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m2jio.h"

/*
typedef struct Pista {
    int codigoIdentificador;
    char endereco[NAME_SIZE];
    char UF[2];
    float tamanhoCircuito;
    float velocidadeMaxima;
    int codigoAviaoRecorde;
} Pista;
*/

/* Objetivo: receber as informacoes da pista. O código sequencial da pista é gerado pelo
 *      programa garantindo que não haverá repetiçao
 */
void prepareNewTrack() {
    
    Pista pista;
    
    system("clear");
    receberString("informe o endereco da pista",pista.endereco,1,NAME_SIZE);
    receberString("informe a UF da pista",pista.UF, 0, 2);
    pista.tamanhoCircuito = receberFloat("informe o tamanho do circuito", 0, 100);
    pista.velocidadeMaxima = receberFloat("informe a velocidade maxima", 0, 100);
    receberString("informe o codigo do aviao que obteve o recorde",pista.codigoAviaoFK,1, PLANE_CODE_SIZE);
    if(persistTrack(&pista) == 1) 
        puts("erro ao salvar pista, tente novamente"); 
    else puts("pista registrada com sucesso"); 
    getchar();
}
int persistTrack(Pista *pista) {
    FILE *pFile = openStream("pista.dat","ab");
    if(pFile != NULL) {
        fwrite(pista, sizeof(Pista), 1, pFile);              
        fclose(pFile);
        return OPERATION_SUCCESS;    
    }
    fclose(pFile);
    return OPERATION_ERROR;
}

