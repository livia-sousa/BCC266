#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(){
    clock_t tempo;
    int cont = 0;

    // Inicializando memorias e instrucoes.   
    blocoMemoria **RAM = alocarRam(TAM_RAM);
    blocoMemoria **cache_01 = alocarCache(TAM_CACHE_01);
    blocoMemoria **cache_02 = alocarCache(TAM_CACHE_02);
    blocoMemoria **cache_03 = alocarCache(TAM_CACHE_03);
    Instrucoes **instrucoes;

    instrucoes = malloc(TAM_INSTRUCOES * sizeof(Instrucoes*));
	
    Endereco *aux_01;
	Endereco *aux_02;
	Endereco *aux_03;
	
    FILE *instrucoes_file = fopen("instrucoes.txt","r");

    int opcode, endereco_bloco_01, endereco_palavra_01, endereco_bloco_02, endereco_palavra_02, endereco_bloco_03, endereco_palavra_03;

	for(int i = 0; i < 100; i++){
        fscanf (instrucoes_file, "%d", &opcode);

        fscanf (instrucoes_file, "%d", &endereco_palavra_01);
        fscanf (instrucoes_file, "%d", &endereco_bloco_01);
        
        fscanf (instrucoes_file, "%d", &endereco_palavra_02);
        fscanf (instrucoes_file, "%d", &endereco_bloco_02);
        
        fscanf (instrucoes_file, "%d", &endereco_palavra_03);
        fscanf (instrucoes_file, "%d", &endereco_bloco_03);

		aux_01 = criarEndereco(endereco_palavra_01, endereco_bloco_01);
		aux_02 = criarEndereco(endereco_palavra_02, endereco_bloco_02);
		aux_03 = criarEndereco(endereco_palavra_03, endereco_bloco_03);

		instrucoes[i] = criarInstrucao(opcode, aux_01, aux_02, aux_03);
    }

    fclose(instrucoes_file);

    tempo = clock(); // Aloca tempo inicial
    int PC = 0;
    int hit_total = 0;
    int miss_total = 0;
    long int custo_total = 0;

    while (instrucoes[PC]->opcode != -1){
        int prim_cache_posicao = -1;
        int seg_cache_posicao = -1;
        int terc_cache_posicao = -1;

        if(instrucoes[PC]->opcode != -1){
            prim_cache_posicao = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->endereco_01);
            seg_cache_posicao = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->endereco_02);
            terc_cache_posicao = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->endereco_03);
            
            switch (instrucoes[PC]->opcode){
            case ADICAO:

                    adicao(instrucoes[PC], cache_01[prim_cache_posicao], cache_01[seg_cache_posicao], cache_01[terc_cache_posicao]);

                    cache_01[terc_cache_posicao]->atualizado = true;

                break;
            case SUB:
                    subtracao(instrucoes[PC], cache_01[prim_cache_posicao], cache_01[seg_cache_posicao], 
                    cache_01[terc_cache_posicao]);   
                    
                    cache_01[terc_cache_posicao]->atualizado = true;
                
                break;
            case SAIR:
                printf("NAO HA DEMANDA POR LEVAR DADOS EXTERNOS PARA AS MEMORIAS.\n");
                break;
            }
        }
        PC++;
    }
    
    hit_total = cache_01[0]->cache_hit + cache_02[0]->cache_hit + cache_03[0]->cache_hit + RAM[0]->cache_hit;
    miss_total = cache_01[0]->cache_miss + cache_02[0]->cache_miss + cache_03[0]->cache_miss + RAM[0]->cache_miss;

    custo_total = cache_01[0]->custo + cache_02[0]->custo + cache_03[0]->custo + RAM[0]->custo;

    printf("\n| TAMANHO CACHE 1 -> %d|\n", TAM_CACHE_01);
    printf("| TAMANHO CACHE 2 -> %d|\n", TAM_CACHE_02);
    printf("| TAMANHO CACHE 3 -> %d|\n", TAM_CACHE_03);
    printf("| TAMANHO RAM     -> %d|\n\n", TAM_RAM);

    printf("| HIT CACHE 1 -> %d | MISS CACHE 1 -> %d |\n", cache_01[0]->cache_hit, cache_01[0]->cache_miss);
    printf("| HIT CACHE 2 -> %d | MISS CACHE 2 -> %d |\n", cache_02[0]->cache_hit, cache_02[0]->cache_miss);
    printf("| HIT CACHE 3 -> %d | MISS CACHE 3 -> %d |\n", cache_03[0]->cache_hit, cache_03[0]->cache_miss);
    printf("| HIT RAM     -> %d | MISS RAM     -> %d |\n", RAM[0]->cache_hit, RAM[0]->cache_miss);

    printf("\n| HIT TOTAL   -> %d | MISS TOTAL   -> %d |\n", hit_total, miss_total);
    
    printf("\n| CUSTO CACHE 1 -> %ld |", cache_01[0]->custo);
    printf("\n| CUSTO CACHE 2 -> %ld |", cache_02[0]->custo);
    printf("\n| CUSTO CACHE 3 -> %ld |", cache_03[0]->custo);
    printf("\n| CUSTO RAM      -> %ld|", RAM[0]->custo);
    printf("\n\n| CUSTO TOTAL    -> %ld|\n\n", custo_total);
    
    tempo = clock() - tempo; // armazena tempo final - inicial   
    double *tempoPrograma = malloc(sizeof(double));
    *tempoPrograma = ((double)tempo)/((CLOCKS_PER_SEC/1000));
     
    printf("\nTempo de execucao: %.2lf ms.\n\n", *tempoPrograma);

    for (int i = 0; i < TAM_CACHE_01; i++){
        free(cache_01[i]);
    }
    free(cache_01);
    
    for (int i = 0; i < TAM_CACHE_02; i++){
        free(cache_02[i]);
    }
    free(cache_02);
    
    for (int i = 0; i < TAM_CACHE_03; i++){
        free(cache_03[i]);
    }
    free(cache_03);

    for (int i = 0; i < TAM_RAM; i++){
        free(RAM[i]);
    }
    free(RAM);
    
    free(tempoPrograma);

    return 0;
}
