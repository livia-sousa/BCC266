#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*instrucoes:
    0 = SALVAR
    1 = SOMAR
    2 = SUBTRAIR
    -1 = SAIR
*/

struct memoria {
    int MemoriaInstrucoes [100][4]; //programa interpretado
    int MemoriaDados [1000];
};

Memoria *alocaMemoria() {
    Memoria *memoria = malloc (sizeof (Memoria));
    return memoria;
}

void montarRam(Memoria *memoria){
    srand(time(NULL));
    for (int i = 0; i < 1000; i++){
        memoria->MemoriaDados[i] = rand() % 100;
    }
}

void liberaMemoria(Memoria *memoria){
    free(memoria);
}

void Menu(Memoria *memoria){

    int comando;
    double auxiliar;

    do{
        printf("\n\n\t|*SEJA BEM VINDO AO MENU DE OPÇÕES!* \n");
        printf("\t|PARA SAIR DIGITE -1\n");
        printf("\t|PARA CALCULOS BAŚICOS DIGITE 0\n"); 
        printf("\t|PARA CALCULOS DE ÁREA DIGITE 1\n");
        printf("\t|PARA CALCULOS DE PERIMETRO DIGITE 2\n");
        printf("\t|PARA CALCULOS DE VOLUME DIGITE 3\n");
        printf("\t|PARA CALCULOS DE FÍSICA DIGITE 4\n");
        printf("\t|PARA CALCULOS DE CONVERSÃO DE MEDIDAS DIGITE 5\n\n");
        
        scanf("%d", &comando);

        if(comando < -2 || comando > 6){
            printf("Comando inválido");
            Menu(memoria);
        }
       
    }while (comando != -1 & comando < 0);

    switch (comando){

        int Comando, numero1, numero2;

        case 0:
            printf("\n\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA SOMA DIGITE 0\n");
            printf("\t|PARA SUBTRAÇÃO DIGITE 1\n");
            printf("\t|PARA MULTIPLICAÇÃO DIGITE 2\n");
            printf("\t|PARA DIVISÃO DIGITE 3\n");
            printf("\t|PARA POTENCIA DIGITE 4\n");
            printf("\t|PARA SOMA DE QUADRADOS DIGITE 5\n");
            printf("\t|PARA CALCULO FATORIAL DIGITE 6\n\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 7){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){
                case 0:
                    printf("\n DIGITE DOIS NUMEROS PARA SOMAR: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoSoma(memoria, numero1, numero2);
                    printf("\n RESULTADO DA SOMA = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                
                case 1:
                    printf("\n DIGITE DOIS NUMEROS PARA SUBTRAIR: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoSubtracao(memoria, numero1, numero2);
                    printf("\n RESULTADO DA SUBTRAÇÃO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                
                case 2:
                    printf("\n DIGITE DOIS NUMEROS PARA MULTIPLICAR: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoMultiplicacao(memoria, numero1, numero2);
                    printf("\n RESULTADO DA MULTIPLICAÇÃO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                
                case 3:
                    printf("\n DIGITE DOIS NUMEROS PARA DIVIDIR: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoDivisao(memoria, numero1, numero2);
                    printf("\n RESULTADO DA DIVISÃO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case 4:
                    printf("\n DIGITE DOIS NUMEROS PARA CALCULO DE POTENCIA: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoPotencia(memoria, numero1, numero2);
                    printf("\n RESULTADO DA POTENCIA = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                    
                case 5:
                    printf("\n DIGITE DOIS NUMEROS PARA SOMA DE QUADRADOS: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoSomadosQuadrados(memoria, numero1, numero2);
                    printf("\n RESULTADO DA SOMA DOS QUADRADOS = %.1lf\n", auxiliar);
                    Menu(memoria);
                    
                    break;
                    
                case 6:
                    printf("\n DIGITE UM NUMERO PARA CALCULO FATORIAL: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoFatorial (memoria, numero1);
                    printf("\n RESULTADO DE %d FATORIAL = %.1lf\n", numero1, auxiliar);
                    Menu(memoria);
                    
                    break;

                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                break;
            }

        break;
        
        case 1:
            //AREA
            printf("\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA CALCULO DA AREA DO TRIANGULO DIGITE 0\n");
            printf("\t|PARA CALCULO DA AREA DO QUADRADO DIGITE 1\n");
            printf("\t|PARA CALCULO DA AREA DO RETANGULO DIGITE 2\n\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 3){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){
                case 0:
                    printf("\n DIGITE O VALOR DA BASE E DA ALTURA DO TRIANGULO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoAreaTriangulo(memoria, numero1, numero2);
                    printf("\n RESULTADO DA AREA DO TRIANGULO = %.1lf\n\n", auxiliar);

                    Menu(memoria);

                    break;
                    
                case 1:
                    printf("\n DIGITE O VALOR DA BASE DO QUADRADO: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoAreaQuadrado(memoria, numero1);
                    printf("\n RESULTADO DA AREA DO QUADRADO = %.1lf\n\n", auxiliar);

                    Menu(memoria);

                    break;

                case 2:
                    printf("\n DIGITE O VALOR DA BASE MAIOR E DA BASE MENOR: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoAreaRetangulo(memoria, numero1, numero2);
                    printf("\n RESULTADO DA AREA DO RETANGULO = %.1lf\n\n", auxiliar);

                    Menu(memoria);

                    break;

                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                    break;
            }

            break;
        
        case 2:
            //PERIMETRO
            printf("\n\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA CALCULAR O PERIMETRO DE UM TRIANGULO DIGITE 0\n");
            printf("\t|PARA CALCULAR O PERIMETRO DE UM QUADRADO DIGITE 1\n");
            printf("\t|PARA PARA CALCULAR O PERIMETRO DE UM RETANGULO DIGITE 2\n\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 3){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){
                int numero3;
                case 0:
                    printf("\n DIGITE O VALOR DA BASE, DO LADO 1 E DO LADO 2: ");
                    scanf("%d %d %d", &numero1, &numero2, &numero3);
                    auxiliar = funcaoPerimetroTriangulo (memoria, numero1, numero2, numero3);
                    printf("\n RESULTADO DO PERIMETRO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case 1:
                    printf("\n DIGITE O VALOR DA BASE DO QUADRADO: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoPerimetroQuadrado (memoria, numero1);
                    printf("\n RESULTADO DO PERIMETRO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case 2:
                    printf("\n DIGITE OS VALORES DA BASE MENOR E MAIOR DO RETANGULO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoPerimetroRetangulo (memoria, numero1, numero2);
                    printf("\n RESULTADO DO PERIMETRO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                    break;
            }

            break;

        case 3:
            //VOLUME
            printf("\n\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA CALCULAR O VOLUME DE UM PARALELEPIDO DIGITE 0\n");
            printf("\t|PARA CALCULAR O VOLUME DE UMA PIRAMIDE DIGITE 1\n");
            printf("\t|PARA PARA CALCULAR O VOLUME DE UM CUBO DIGITE 2\n\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 3){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){
                int numero3;
                case 0:
                    printf("\n DIGITE O VALOR DO COMPRIMENTO, LARGURA E ALTURA DO PARALELEPIPEDO: ");
                    scanf("%d %d %d", &numero1, &numero2, &numero3);
                    auxiliar = funcaoVolumeParalelepipedo (memoria, numero1, numero2, numero3);
                    printf("\n RESULTADO DO PERIMETRO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                
                case 1:
                    printf("\n DIGITE O VALOR DA AREA DA BASE E ALTURA DA PIRAMIDE: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoVolumePiramide (memoria, numero1, numero2);
                    printf("\n RESULTADO DO VOLUME = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                
                case 2:
                    printf("\n DIGITE O VALOR DO LADO DO CUBO: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoVolumeCubo (memoria, numero1);
                    printf("\n RESULTADO DO VOLUME = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                break;
            }

            break;

        case 4:
            //FISICA
            printf("\n\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA CALCULAR A VELOCIDADE MEDIA DIGITE 0\n");
            printf("\t|PARA CALCULAR A ACELERAÇÃO MEDIA DIGITE 1\n");
            printf("\t|PARA PARA CALCULAR A DISTANCIA PERCORRIDA DIGITE 2\n");
            printf("\t|PARA PARA CALCULAR FORÇA DIGITE 3\n");
            printf("\t|PARA PARA CALCULAR ENERGIA DIGITE 4\n\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 5){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){

                case 0:
                    printf("\n DIGITE O VALOR DA DISTANCIA E DO TEMPO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoVelocidadeMedia (memoria, numero1, numero2);
                    printf("\n RESULTADO DA VELOCIDADE = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case 1:
                    printf("\n DIGITE O VALOR DA VELOCIDADE E DO TEMPO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoAceleracaoMedia (memoria, numero1, numero2);
                    printf("\n RESULTADO DA ACELERAÇÃO = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 2:
                    printf("\n DIGITE O VALOR DA VELOCIDADE E DO TEMPO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoDistanciaPercorrida (memoria, numero1, numero2);
                    printf("\n RESULTADO DA DISTANCIA = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 3:
                    printf("\n DIGITE O VALOR DA MASSA E DA ACELERAÇÃO: ");
                    scanf("%d %d", &numero1, &numero2);
                    auxiliar = funcaoForca (memoria, numero1, numero2);
                    printf("\n RESULTADO DA FORÇA = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 4:
                    printf("\n DIGITE O VALOR DA MASSA: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoEnergia (memoria, numero1);
                    printf("\n RESULTADO DA ENERGIA = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                break;
            }

            break;
        
        case 5:
            //CONVERSÃO
            printf("\n\t|PARA SAIR DIGITE -1\n");
            printf("\t|PARA CONVERTER DE CELSIUS PARA KELVIN DIGITE 0\n");
            printf("\t|PARA CONVERTER DE KELVIN PARA CELSIUS DIGITE 1\n");
            printf("\t|PARA CONVERTER DE HORA PARA MINUTO DIGITE 2\n");
            printf("\t|PARA CONVERTER DE MINUTO PARA SEGUNDO DIGITE 3\n");
            printf("\t|PARA CONVERTER DE MINUTO PARA HORA DIGITE 4\n");
            printf("\t|PARA CONVERTER DE SEGUNDO PARA MINUTO DIGITE 5\n");

            scanf("%d", &Comando);
            if(comando < -2 || comando > 6){
                printf("Comando inválido");
                Menu(memoria);
            }
            switch (Comando){

                case 0:
                    printf("\n DIGITE O VALOR DA TEMPERATURA EM CELSIUS: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoCelsius_Kelvin (memoria, numero1);
                    printf("\n RESULTADO DA TEMPERATURA EM KELVIN = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 1:
                    printf("\n DIGITE O VALOR DA TEMPERATURA EM KELVIN: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoKelvin_Celsius (memoria, numero1);
                    printf("\n RESULTADO DA TEMPERATURA EM CELSIUS = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 2:
                    printf("\n DIGITE O TEMPO EM HORAS: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoHoraMin (memoria, numero1);
                    printf("\n RESULTADO DO TEMPO EM MINUTOS = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 3:
                    printf("\n DIGITE O TEMPO EM MINUTOS: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoMinSeg (memoria, numero1);
                    printf("\n RESULTADO DO TEMPO EM SEGUNDOS = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case 4:
                    printf("\n DIGITE O TEMPO EM MINUTOS: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoMinHora (memoria, numero1);
                    printf("\n RESULTADO DO TEMPO EM HORAS = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;

                case 5:
                    printf("\n DIGITE O TEMPO EM SEGUNDOS: ");
                    scanf("%d", &numero1);
                    auxiliar = funcaoSegMin (memoria, numero1);
                    printf("\n RESULTADO DO TEMPO EM MINUTOS = %.1lf\n", auxiliar);
                    Menu(memoria);

                    break;
                case -1:
                    Menu(memoria);
                    break;

                default:
                    printf("Comando inválido");
                    Menu(memoria);

                break;
            }

            break;
        
    }

}

//int *retornaRAM(Memoria *memoria){
 //   return memoria-> MemoriaDados;
//}

void instrucoesProgramaAleatorio(Memoria *memoria){

    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */

    srand(time(NULL));

    for (int i = 0; i < 999; i++){
        memoria->MemoriaInstrucoes[i][0] = rand() % 2;
        memoria->MemoriaInstrucoes[i][1] = rand() % 100;
        memoria->MemoriaInstrucoes[i][2] = rand() % 100;
        memoria->MemoriaInstrucoes[i][3] = rand() % 100;
    }
    memoria->MemoriaInstrucoes[999][0] = -1;
    memoria->MemoriaInstrucoes[999][1] = -1;
    memoria->MemoriaInstrucoes[999][2] = -1;
    memoria->MemoriaInstrucoes[999][3] = -1;

    maquina(memoria);

}

void maquina(Memoria *memoria){
    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */

    int opcode = TMP_MAX; // Maior inteiro possivel
    int cont = 0;
    int num, end1, end2, end3, soma, subtracao;

	while(opcode != -1) { 

        opcode = memoria->MemoriaInstrucoes[cont][0];
                    
	    switch (opcode){
        //SOMAR
        case 0:

            end1 = memoria->MemoriaInstrucoes[cont][1]; //posicao numero1
            end2 = memoria->MemoriaInstrucoes[cont][2]; //posicao numero 2
            end3 = memoria->MemoriaInstrucoes[cont][3]; // posicao resultado

            soma = memoria->MemoriaDados[end1] + memoria->MemoriaDados[end2];
            //SALVANDO O RESULTADO
            memoria->MemoriaDados[end3] = soma;

           // printf("somando %d  com  %d  e gerando  %d\n", memoria->MemoriaDados[end1],memoria->MemoriaDados[end2],memoria->MemoriaDados[end3]);
            break;

        //SUBTRAIR
        case 1:
            end1 = memoria->MemoriaInstrucoes[cont][1]; //posicao numero1
            end2 = memoria->MemoriaInstrucoes[cont][2]; //posicao numero 2
            end3 = memoria->MemoriaInstrucoes[cont][3]; // posicao resultado

            soma = memoria->MemoriaDados[end1] - memoria->MemoriaDados[end2];
            //SALVANDO O RESULTADO
            memoria->MemoriaDados[end3] = soma;

            //printf("subtraindo %d  com  %d  e gerando  %d\n", memoria->MemoriaDados[end1],memoria->MemoriaDados[end2],memoria->MemoriaDados[end3]);
            break;

        //SALVAR
        case 2:
            end1 = memoria->MemoriaInstrucoes[cont][1]; //posicao numero1
            end2 = memoria->MemoriaInstrucoes[cont][2]; //posicao numero 2

            memoria->MemoriaDados[end2] = end1;
            break;

        //trazer
        case 3:

            memoria->MemoriaInstrucoes[cont][1] = memoria->MemoriaDados[memoria->MemoriaInstrucoes[cont][2]];
            break;
        }

    cont++;
    }
}

//CALCULOS BASICOS

double funcaoSoma(Memoria *memoria, int n1, int n2){

    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */
    memoria->MemoriaInstrucoes[0][0] = 2;
    memoria->MemoriaInstrucoes[0][1] = n1;
    memoria->MemoriaInstrucoes[0][2] = 0;
    memoria->MemoriaInstrucoes[0][3] =-1;

    memoria->MemoriaInstrucoes[1][0] = 2;
    memoria->MemoriaInstrucoes[1][1] = n2;
    memoria->MemoriaInstrucoes[1][2] = 1;
    memoria->MemoriaInstrucoes[1][3] = -1;

    memoria->MemoriaInstrucoes[2][0] = 0;
    memoria->MemoriaInstrucoes[2][1] = 0;
    memoria->MemoriaInstrucoes[2][2] = 1;
    memoria->MemoriaInstrucoes[2][3] = 1;

    memoria->MemoriaInstrucoes[3][0] = -1;
    memoria->MemoriaInstrucoes[3][1] = -1;
    memoria->MemoriaInstrucoes[3][2] = -1;
    memoria->MemoriaInstrucoes[3][3] = -1;

    maquina(memoria);

    return memoria->MemoriaDados[1];

}

double funcaoSubtracao(Memoria *memoria, int n1, int n2){

    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */
    memoria->MemoriaInstrucoes[0][0] = 2;
    memoria->MemoriaInstrucoes[0][1] = n1;
    memoria->MemoriaInstrucoes[0][2] = 0;
    memoria->MemoriaInstrucoes[0][3] =-1;

    memoria->MemoriaInstrucoes[1][0] = 2;
    memoria->MemoriaInstrucoes[1][1] = n2;
    memoria->MemoriaInstrucoes[1][2] = 1;
    memoria->MemoriaInstrucoes[1][3] = -1;

    memoria->MemoriaInstrucoes[2][0] = 1;
    memoria->MemoriaInstrucoes[2][1] = 0;
    memoria->MemoriaInstrucoes[2][2] = 1;
    memoria->MemoriaInstrucoes[2][3] = 1;

    memoria->MemoriaInstrucoes[3][0] = -1;
    memoria->MemoriaInstrucoes[3][1] = -1;
    memoria->MemoriaInstrucoes[3][2] = -1;
    memoria->MemoriaInstrucoes[3][3] = -1;

    maquina(memoria);

    return memoria->MemoriaDados[1];
}

double funcaoMultiplicacao(Memoria *memoria, int n1, long int n2){

    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */
    memoria->MemoriaInstrucoes[0][0] = 2; // salvar
    memoria->MemoriaInstrucoes[0][1] = n1; // n1
    memoria->MemoriaInstrucoes[0][2] = 0; // na posicao 0
    memoria->MemoriaInstrucoes[0][3] =-1;

    memoria->MemoriaInstrucoes[1][0] = 2; // salvar
    memoria->MemoriaInstrucoes[1][1] = 0;// 0 pra somar com o n1
    memoria->MemoriaInstrucoes[1][2] = 1;// na posicao 1
    memoria->MemoriaInstrucoes[1][3] = -1;

    //Realiza as somas e salva o resultado na posição 1 da RAM;
    for (int i = 0; i < n2; i++){

        memoria->MemoriaInstrucoes[i + 2][0] = 0; //soma 
        memoria->MemoriaInstrucoes[i + 2][1] = 0; // n1
        memoria->MemoriaInstrucoes[i + 2][2] = 1; //com o numero que vai ficar armazenado em 1
        memoria->MemoriaInstrucoes[i + 2][3] = 1; //guarda o numero na pos 1
    }//soma o da posicao 0 (multiplicando) com o da posicao 1 (que no inicio é 0)

    memoria->MemoriaInstrucoes[n2 + 2][0] = -1;
    memoria->MemoriaInstrucoes[n2 + 2][1] = -1;
    memoria->MemoriaInstrucoes[n2 + 2][2] = -1;
    memoria->MemoriaInstrucoes[n2 + 2][3] = -1;

    maquina(memoria);
    return memoria->MemoriaDados[1];
}

double funcaoDivisao(Memoria *memoria, int n1, int n2){

    /*instrucoes:
        0 = SOMAR
        1 = SUBTRAIR
        2 = SALVAR
        -1 = SAIR
    */
    int cont = 0;
    
    memoria->MemoriaInstrucoes[0][0] = 2;
    memoria->MemoriaInstrucoes[0][1] = n1;
    memoria->MemoriaInstrucoes[0][2] = 0;
    memoria->MemoriaInstrucoes[0][3] =-1;

    memoria->MemoriaInstrucoes[1][0] = 2;
    memoria->MemoriaInstrucoes[1][1] = n2;
    memoria->MemoriaInstrucoes[1][2] = 1;
    memoria->MemoriaInstrucoes[1][3] = -1;
   
    memoria->MemoriaInstrucoes[2][0] = -1;
    memoria->MemoriaInstrucoes[2][1] = -1;
    memoria->MemoriaInstrucoes[2][2] = -1;
    memoria->MemoriaInstrucoes[2][3] = -1;

    maquina(memoria);

    //Faz a divisão, conferindo se o dividendo é maior que o divisor
    while(memoria->MemoriaDados[0] >= memoria->MemoriaDados[1]){
        memoria->MemoriaInstrucoes[0][0] = 1;
        memoria->MemoriaInstrucoes[0][1] = 0;
        memoria->MemoriaInstrucoes[0][2] = 1;
        memoria->MemoriaInstrucoes[0][3] = 0;

        memoria->MemoriaInstrucoes[1][0] = -1;
        memoria->MemoriaInstrucoes[1][1] = -1;
        memoria->MemoriaInstrucoes[1][2] = -1;
        memoria->MemoriaInstrucoes[1][3] = -1;

        maquina(memoria);

        cont++;
        
    }
    memoria->MemoriaDados[1] = cont;

    return memoria->MemoriaDados[1];
}

double funcaoPotencia(Memoria *memoria, int base, int expoente){    
    if(expoente == 0)  
        memoria->MemoriaDados[1] = 1;

    else if(expoente == 1)
        memoria->MemoriaDados[1] = base;

    else if(expoente > 1){
        int aux = base;

        for(int i = 0; i < (expoente - 1); i++){
            funcaoMultiplicacao(memoria, aux, base);
            aux = memoria->MemoriaDados[1];
        }
    }
    return memoria->MemoriaDados[1];
}

double funcaoSomadosQuadrados(Memoria *memoria, int n1, int n2){
    int aux1 , aux2;

    funcaoPotencia(memoria, n1, 2);
    aux1 = memoria->MemoriaDados[1];
    
    funcaoPotencia(memoria, n2, 2);
    aux2 = memoria->MemoriaDados[1];

    funcaoSoma(memoria, aux1, aux2);

    return memoria->MemoriaDados[1];

}

double funcaoFatorial(Memoria *memoria, int termo){
    int aux1 = termo, aux2 = 1;
    for(int i = 0; i < termo; i++){
        funcaoMultiplicacao(memoria, aux2, aux1);
        aux2 = memoria->MemoriaDados[1];
        aux1--;
    }
    return memoria->MemoriaDados[1];
}

//Area

double funcaoAreaTriangulo(Memoria *memoria, int base, int altura){
    int aux;

    funcaoMultiplicacao(memoria, base, altura);
    aux = memoria->MemoriaDados[1];

    funcaoDivisao(memoria, aux, 2);

    return memoria->MemoriaDados[1];
}

double funcaoAreaQuadrado(Memoria *memoria, int base){

    funcaoMultiplicacao(memoria, base, base);
    
    return memoria->MemoriaDados[1];
}

double funcaoAreaRetangulo(Memoria *memoria, int baseMaior, int baseMenor){

    funcaoMultiplicacao(memoria, baseMaior, baseMenor);

    return memoria->MemoriaDados[1];

}

//PERIMETRO

double funcaoPerimetroTriangulo(Memoria *memoria, int base, int lado1, int lado2){
    int aux;

    aux = funcaoSoma(memoria, base, lado1);

    funcaoSoma(memoria, aux, lado2);

    return memoria->MemoriaDados[1];
}

double funcaoPerimetroQuadrado(Memoria *memoria, int base){

    funcaoMultiplicacao(memoria, base, 4);
    return memoria->MemoriaDados[1];
}

double funcaoPerimetroRetangulo(Memoria *memoria, int baseMaior, int baseMenor){
    int aux1, aux2;

    funcaoMultiplicacao(memoria, baseMaior, 2);
    aux1 = memoria->MemoriaDados[1];

    funcaoMultiplicacao(memoria, baseMenor, 2);
    aux2 = memoria->MemoriaDados[1];

    funcaoSoma(memoria, aux1, aux2);
    return memoria->MemoriaDados[1];

}

//VOLUME

double funcaoVolumeParalelepipedo(Memoria *memoria, int comprimento, int largura, int altura){
    int aux;
    
    funcaoMultiplicacao(memoria, comprimento, largura);
    aux = memoria->MemoriaDados[1];

    funcaoMultiplicacao(memoria, aux, altura);

    return memoria->MemoriaDados[1];
}

double funcaoVolumePiramide(Memoria *memoria, int areabase, int altura){
    int aux;

    funcaoMultiplicacao(memoria, areabase, altura);
    aux = memoria->MemoriaDados[1];

    funcaoDivisao(memoria, aux, 3);

    return memoria->MemoriaDados[1];
}

double funcaoVolumeCubo(Memoria *memoria, int lado){
    funcaoPotencia(memoria, lado, 3);

    return memoria->MemoriaDados[1];
}

//FISICA

double funcaoVelocidadeMedia(Memoria *memoria, int distancia, int tempo){
    funcaoDivisao(memoria, distancia, tempo);
    return memoria->MemoriaDados[1];
}

double funcaoAceleracaoMedia(Memoria *memoria, int velocidade, int tempo){
    funcaoDivisao(memoria, velocidade, tempo);
    return memoria->MemoriaDados[1];
}

double funcaoDistanciaPercorrida(Memoria *memoria, int velocidade, int tempo){
    funcaoMultiplicacao(memoria, velocidade, tempo);
    return memoria->MemoriaDados[1];
}

double funcaoForca(Memoria *memoria, int massa, int aceleracao){
    funcaoMultiplicacao(memoria, massa, aceleracao);
    return memoria->MemoriaDados[1];
}

double funcaoEnergia(Memoria *memoria, int massa){
    funcaoMultiplicacao(memoria, massa, 9);
    return memoria->MemoriaDados[1];
}

//CONVERSÃO

double funcaoCelsius_Kelvin(Memoria *memoria, int temperatura){
    funcaoSoma(memoria, temperatura, 273);
    return memoria->MemoriaDados[1];
}

double funcaoKelvin_Celsius(Memoria *memoria, int temperatura){
    funcaoSubtracao(memoria, temperatura, 273);
    return memoria->MemoriaDados[1];
}

double funcaoHoraMin(Memoria *memoria, int hora){
    funcaoMultiplicacao(memoria, hora, 60);
    return memoria->MemoriaDados[1];
}

double funcaoMinSeg(Memoria *memoria, int minuto){
    funcaoMultiplicacao(memoria, minuto, 60);
    return memoria->MemoriaDados[1];
}

double funcaoMinHora(Memoria *memoria, int minutos){
    funcaoDivisao(memoria, minutos, 60);
    return memoria->MemoriaDados[1];
}

double funcaoSegMin(Memoria *memoria, int segundos){
    funcaoDivisao(memoria, segundos, 60);
    return memoria->MemoriaDados[1];
}