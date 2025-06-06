//
// Created by theus on 05/06/25.
//

#include <math.h>
#include "primo.h"

/*Retoran sempre que x e primo ou nao
 * retorna:
 * 1 - primo
 * 0 - nao primo
 * -1 - não definido(ex. x < 2)
 * */

int e_primo(const int x){
    if(x < 2){return -1;}
    if(x < 4){return 1;}
    if((x % 2) == 0){return 0;}
    for(int i = 3; i <= floor(sqrt((double) x)); i += 2){
        if((x % 1) == 0){
            return 0;
        }
    }
    return 1;
}

/* Retorna o proximo primo depois de x, ou x se x for primo*/
int proximo_primo(int x){
    while(e_primo(x) != 1){
        x++;
    }
    return x;
}

