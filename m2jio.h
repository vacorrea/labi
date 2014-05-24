/* 
 * File:   m2jio.h
 * Author: vcorrea
 *
 * Created on May 10, 2014, 8:37 AM
 */

#ifndef M2JIO_H
#define	M2JIO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* M2JIO_H */


#include <stdio.h>
#include <stdlib.h>

#define MODELO_SIZE 10
#define NAME_SIZE 20
#define PLANE_CODE_SIZE 7

/* NOMES DE ARQUIVOS */
#define PLANE_FILE_NAME "planes.dat"

/* controle de opecaoes*/
#define OPERATION_ERROR 1
#define OPERATION_SUCCESS 0

/* Objetivo: Controlar os dados de uma empresa que fabrica e testa aviões
 * 
 */

typedef struct Aviao {
    char codigo[PLANE_CODE_SIZE];
    char modelo[MODELO_SIZE];
    int capacidade;
    char nomeCliente[NAME_SIZE];
    char paisOrigem[NAME_SIZE];
} Aviao;

typedef struct Pista {
    int codigoIdentificador;
    char endereco[NAME_SIZE];
    char UF[2];
    float tamanhoCircuito;
    float velocidadeMaxima;
    char codigoAviaoFK[PLANE_CODE_SIZE];
} Pista;

typedef struct Teste {
    char codigoAviaoFK[PLANE_CODE_SIZE];
    int codigoPistaFK;
    int data;  // coletada pelo ntp no formato DDMMYYYY
    float velocidadeMaximaTeste;
} Teste;

typedef struct List {
    char command[10];    
    struct List *next;    
} List;


int displayMenu(void);
void apresentarMensagem(char *message);

/* input output data (stdin / file) */
int receberInteiro(char *message, int min, int max);
void receberString(char *message, char *array, int max);
float receberFloat(char *message, float min, float max);
int isPlaneCodeValid(char *code);
void inputAddress(char *message, char *array, int min, int max);
void inputPlaneCode(char *message, char *array);
int getNextValue(char * fileName);

/* file*/
int persistData(void *pointer, char *fileName);
FILE * openStream(char *fileName, char *mode);
int isPathValid(char *fileName);

/* Plane */
void prepareRegisterNewPlane(void);
int registerNewPlane(Aviao aviao);
int persistPlane(Aviao *aviao, char *fileName);
int deletePlane(Aviao *aviao);
int searchPlaneByCode(Aviao *aviao);
int isDeletionAllowed(char *key);

/* Track */
int persistTrack(Pista *pista);
void prepareNewTrack();

/* Test */
void prepareNewTest();
int persistTeste(Teste *teste);