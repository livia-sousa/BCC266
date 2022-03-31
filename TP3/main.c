#include "functions.h"

int main(){

    BlocoMemoria **cache_01 = criarMemoria(TAM_CACHE_01);
    BlocoMemoria **cache_02 = criarMemoria(TAM_CACHE_02);
    BlocoMemoria **cache_03 = criarMemoria(TAM_CACHE_03);
    BlocoMemoria **RAM = criarMemoria(TAM_RAM);
    criarHD(TAM_HD);

    Instrucoes **instrucoes = malloc(TAM_INSTRUCTIONS * sizeof(Instrucoes*));
	Instrucoes **interrupcoes = malloc(TAM_INTERRUPTION_INSTRUCTIONS * sizeof(Instrucoes*));

    Endereco *aux_01;
	Endereco *aux_02;
	Endereco *aux_03;

    FILE *arq_instrucoes = fopen("instrucoes.txt","r");

    int opcode, end_bloco_1, end_palavra_01, end_bloco_2, end_palavra_02, end_bloco_3, end_palavra_03;

	for(int i = 0; i < TAM_INSTRUCTIONS; i++){
        fscanf (arq_instrucoes, "%d", &opcode);

        fscanf (arq_instrucoes, "%d", &end_palavra_01);
        fscanf (arq_instrucoes, "%d", &end_bloco_1);
        
        fscanf (arq_instrucoes, "%d", &end_palavra_02);
        fscanf (arq_instrucoes, "%d", &end_bloco_2);
        
        fscanf (arq_instrucoes, "%d", &end_palavra_03);
        fscanf (arq_instrucoes, "%d", &end_bloco_3);

		aux_01 = criarEndereco(end_palavra_01, end_bloco_1);
		aux_02 = criarEndereco(end_palavra_02, end_bloco_2);
		aux_03 = criarEndereco(end_palavra_03, end_bloco_3);

		instrucoes[i] = criarInstrucao(opcode, aux_01, aux_02, aux_03);
    }

    fclose(arq_instrucoes);

    int PC = 0;
    int hit_total = 0;
    int miss_total = 0;
    long int custo_total = 0;

    while (instrucoes[PC]->opcode != -1){
        
        int primeira_posi_cache = -1;
        int segunda_posi_cache = -1;
        int terceira_posi_cache = -1;

        if(instrucoes[PC]->opcode != -1){
            
            primeira_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->end_01);
            segunda_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->end_02);
            terceira_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, instrucoes[PC]->end_03);

            switch (instrucoes[PC]->opcode){
            case 0:            
                    soma(instrucoes[PC], cache_01[primeira_posi_cache], cache_01[segunda_posi_cache], 
                    cache_01[terceira_posi_cache]);

                    cache_01[terceira_posi_cache]->atualizado = 1;

                break;
            case 1:
                    subtracao(instrucoes[PC], cache_01[primeira_posi_cache], cache_01[segunda_posi_cache], 
                    cache_01[terceira_posi_cache]);   
                    
                    cache_01[terceira_posi_cache]->atualizado = 1;
                
                break;
            case -1:
                printf("\nNAO HA DEMANDA POR LEVAR DADOS EXTERNOS PARA AS MEMORIAS.\n");
                break;
            }
        }
        
        int probabilidade_interrup = rand() % 11;

		if( probabilidade_interrup >= 0 && probabilidade_interrup <= 3){

            printf("VALOR PROBABILIDADE INTERRUPÇÃO: %d\n",probabilidade_interrup);
            printf("\nINICIO INTERRUPCAO\n");
            int PCi = 0;

            FILE* arq_interrupcao = fopen("interrupcoes.txt","r"); 

            for(int i = 0; i < TAM_INTERRUPTION_INSTRUCTIONS; i++){

                fscanf (arq_interrupcao, "%d", &opcode);

                fscanf (arq_interrupcao, "%d", &end_palavra_01);
                fscanf (arq_interrupcao, "%d", &end_bloco_1);
                
                fscanf (arq_interrupcao, "%d", &end_palavra_02);
                fscanf (arq_interrupcao, "%d", &end_bloco_2);
                
                fscanf (arq_interrupcao, "%d", &end_palavra_03);
                fscanf (arq_interrupcao, "%d", &end_bloco_3);

                aux_01 = criarEndereco(end_palavra_01, end_bloco_1);
                aux_02 = criarEndereco(end_palavra_02, end_bloco_2);
                aux_03 = criarEndereco(end_palavra_03, end_bloco_3);

                interrupcoes[i] = criarInstrucao(opcode, aux_01, aux_02, aux_03);
            }

            fclose(arq_interrupcao);
            
            while (interrupcoes[PCi]->opcode != -1){
            
            int primeira_posi_cache = -1;
            int segunda_posi_cache = -1;
            int terceira_posi_cache = -1;

            if(interrupcoes[PCi]->opcode != -1){

                primeira_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, interrupcoes[PCi]->end_01);
                segunda_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, interrupcoes[PCi]->end_02);
                terceira_posi_cache = MMU(cache_01, cache_02, cache_03, RAM, interrupcoes[PCi]->end_03);
                
                switch (interrupcoes[PCi]->opcode){
                case 0:
                        soma(interrupcoes[PCi], cache_01[primeira_posi_cache], cache_01[segunda_posi_cache], 
                        cache_01[terceira_posi_cache]);

                        cache_01[terceira_posi_cache]->atualizado = 1;
                    

                    break;
                case 1:
                        subtracao(interrupcoes[PCi], cache_01[primeira_posi_cache], cache_01[segunda_posi_cache], 
                        cache_01[terceira_posi_cache]);   
                        
                        cache_01[terceira_posi_cache]->atualizado = 1;
                    
                    break;
                case -1:
                    printf("\nNAO HA DEMANDA POR LEVAR DADOS EXTERNOS PARA AS MEMORIAS.\n");
                    break;
                }
            }

            PCi++;
            
            }
	    }
	PC++;
    }
		
    hit_total = cache_01[0]->hit + cache_02[0]->hit + cache_03[0]->hit + RAM[0]->hit + RAM[1]->hit;
    miss_total = cache_01[0]->miss + cache_02[0]->miss + cache_03[0]->miss + RAM[0]->miss;

    custo_total = cache_01[0]->cost + cache_02[0]->cost + cache_03[0]->cost + RAM[0]->cost + RAM[1]->cost;

    printf("| HIT CACHE 1 -> %d | MISS CACHE 1 -> %d |\n", cache_01[0]->hit, cache_01[0]->miss);
    printf("| HIT CACHE 2 -> %d | MISS CACHE 2 -> %d |\n", cache_02[0]->hit, cache_02[0]->miss);
    printf("| HIT CACHE 3 -> %d | MISS CACHE 3 -> %d |\n", cache_03[0]->hit, cache_03[0]->miss);
    printf("| HIT RAM     -> %d | MISS RAM     -> %d  |\n", RAM[0]->hit, RAM[0]->miss);
    printf("| HIT HD     -> %d | MISS HD       -> 0  |\n", RAM[1]->hit);

    printf("\n| HIT TOTAL   -> %d | MISS TOTAL   -> %d |\n", hit_total, miss_total);
    
    printf("\n| CUSTO CACHE 1 -> %ld |", cache_01[0]->cost);
    printf("\n| CUSTO CACHE 2 -> %ld |", cache_02[0]->cost);
    printf("\n| CUSTO CACHE 3 -> %ld |", cache_03[0]->cost);
    printf("\n| CUSTO RAM      -> %ld|", RAM[0]->cost);
    printf("\n| CUSTO HD       -> %ld|", RAM[1]->cost);

    printf("\n\n| CUSTO TOTAL    -> %ld|\n\n", custo_total);
    
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
    
    for (int i = 0; i < TAM_INSTRUCTIONS; i++){
        free(instrucoes[i]);
    }
    free(instrucoes);
    
    for (int i = 0; i < TAM_INTERRUPTION_INSTRUCTIONS; i++){
        free(interrupcoes[i]);
    }
    free(interrupcoes);

    return 0;
}




