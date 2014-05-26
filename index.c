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
        fpurge(stdin);
        opcao = displayMenu();
        switch(opcao) {
            case 1 : planeMenu();
                 break;
            case 2: prepareNewTrack();
                 break;
            case 3: prepareNewTest();
                 break;                
            case 0: puts("fim");
        }    
    }
    // while((*root).command != NULL) {   }
    return (EXIT_SUCCESS);
}


