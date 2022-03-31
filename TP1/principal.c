#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>

/*instrucoes:
0 = SALVAR
1 = SOMAR
2 = SUBTRAIR
-1 = SAIR
*/

int main(){
   
    Memoria *memoria;
    memoria= alocaMemoria();
    montarRam();
    Menu(memoria);
    liberaMemoria(memoria);

    return 0;
}