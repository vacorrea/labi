/* 
 * File:   jair_vitorCorrea_uc08033082_fontes.c
 * Author: vcorrea
 *
 * Created on May 9, 2014, 6:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "m2jio.h"

int main(int argc, char** argv) {
    
    List *root;     // linked list
    int opcao=9999;

    while(opcao != 0) {
        opcao = displayMenu();
        switch(opcao) {
            case 1 : prepareRegisterNewPlane();
                 break;
            case 0: puts("fim");
        }    
    }
    // while((*root).command != NULL) {   }
    return (EXIT_SUCCESS);
}


