#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int cont = 0;

Endereco* criarEndereco(int bloco_final, int palavra_final){
    Endereco *novo = malloc(sizeof(Endereco));
    novo->endereco_bloco = bloco_final;
    novo->endereco_palavra = palavra_final;
    return novo;
}

int getEnderecoPalavra(Endereco *a){
	return a->endereco_palavra;
}

int getEnderecoBloco(Endereco *a){
	return a->endereco_bloco;
}

Instrucoes* criarInstrucao(int opcode, Endereco* end1, Endereco* end2, Endereco* end3){
	Instrucoes *novo = malloc(sizeof(Instrucoes));
	novo->opcode = opcode;
	novo->endereco_01 = end1;
	novo->endereco_02 = end2;
	novo->endereco_03 = end3;
	return novo;
}

Endereco* getEND1(Instrucoes* i){
	return i->endereco_01;
}

Endereco* getEND2(Instrucoes* i){
	return i->endereco_02;
}

Endereco* getEND3(Instrucoes* i){
	return i->endereco_03;
}

blocoMemoria *createMemoryBlockRAM(int tamanho){
    blocoMemoria *novo = malloc(sizeof(blocoMemoria));

    srand(time(NULL));
    for(int i = 0; i < 4; i++){
	    novo->palavra[i] = rand() % 10;
    }

    novo->tamanho = tamanho;
    novo->vazio = false;
    novo->atualizado = 0;
    novo->cache_hit = 0;
    novo->cache_miss = 0;
    novo->acessado = 0;
    novo->custo = 0;

    return novo;
}

blocoMemoria *createMemoryBlockCache(int tamanho){
    blocoMemoria *novo = malloc(sizeof(blocoMemoria));

    for(int i = 0; i < 4; i++){
	    novo->palavra[i] = -1;
    }

    novo->tamanho = tamanho;
    novo->vazio = true;
    novo->atualizado = 0;
    novo->cache_hit = 0;
    novo->cache_miss = 0;
    novo->acessado = 0;
    novo->custo = 0;

    return novo;
}

blocoMemoria **alocarRam(int tamanho){
   
    blocoMemoria **novo = malloc(tamanho * sizeof(blocoMemoria));

    for (int i = 0; i < tamanho; i++){
        novo[i] = createMemoryBlockRAM(tamanho);
        novo[i]->endereco_bloco = i;
    }
    return novo;
}

blocoMemoria **alocarCache(int tamanho){
  
    blocoMemoria **novo = malloc(tamanho * sizeof(blocoMemoria));

    for (int i = 0; i < tamanho; i++){
        novo[i] = createMemoryBlockCache(tamanho);
        novo[i]->endereco_bloco = -1;
    }
    return novo;
}

int getPalavra(blocoMemoria *m, int end){
	return m->palavra[end];
}

void setPalavra(blocoMemoria *m, int ind, int palavra){
	m->palavra[ind] = palavra;	
}

void setAtualizado(blocoMemoria *m, int atualizado){
	m->atualizado = atualizado;
}

int MMU(blocoMemoria **cache_01, blocoMemoria **cache_02, blocoMemoria **cache_03, blocoMemoria **RAM, Endereco *endereco){

    int cache_posicao = 0;

    if(procuraCache(cache_01, endereco->endereco_bloco, TAM_CACHE_01) != -1){
        // printf("entrou na cache 1\n");
        cache_posicao = procuraCache(cache_01, endereco->endereco_bloco, TAM_CACHE_01);
        
        cache_01[0]->cache_hit += 1;
        
        cache_01[0]->custo += 10;
        
        return cache_posicao;
    }
    else if(procuraCache(cache_02, endereco->endereco_bloco, TAM_CACHE_02) != -1){
        // printf("entrou na cache 2\n");

        cache_posicao = procuraCache(cache_02, endereco->endereco_bloco, TAM_CACHE_02);
        cache_posicao = transfereDados(cache_02, cache_01, cache_posicao);
        
        cache_02[0]->cache_hit += 1;
        
        cache_01[0]->cache_miss += 1;     
        
        cache_02[0]->custo += 110;
        
        return cache_posicao;
    }
   
    else if(procuraCache(cache_03, endereco->endereco_bloco, TAM_CACHE_03) != -1){
        // printf("entrou na cache 3\n");
        
        cache_posicao = procuraCache(cache_03, endereco->endereco_bloco, TAM_CACHE_03);
        cache_posicao = transfereDados(cache_03, cache_02, cache_posicao);
        cache_posicao = transfereDados(cache_02, cache_01, cache_posicao);
        
        cache_03[0]->cache_hit += 1;
        
        cache_01[0]->cache_miss += 1;
        cache_02[0]->cache_miss += 1;     

        cache_03[0]->custo += 1110;

        return cache_posicao;
    }

    else{
        // printf("entrou na ram\n");

        cache_posicao = procuraRAM(RAM, cache_03, endereco->endereco_bloco); 
        cache_posicao = transfereDados(cache_03, cache_02, cache_posicao);
        cache_posicao = transfereDados(cache_02, cache_01, cache_posicao);       
        
        cache_01[0]->cache_miss += 1;   
        cache_02[0]->cache_miss += 1;   
        cache_03[0]->cache_miss += 1;

        RAM[0]->cache_hit += 1;

        RAM[0]->custo += 101110;
        
        return cache_posicao;
    }

   
}

int procuraCache(blocoMemoria **cache, int endereco, int tamanho){  

    for(int i = 0; i < tamanho; i++){
        if((cache[i]->endereco_bloco) == (endereco)){
            cont += 1;
			cache[i]->acessado = cont;
            return i;
		}
	}
    return -1;
}

int procuraRAM(blocoMemoria **RAM, blocoMemoria **cache_03, int endereco){
    int posicaoVazia = getPosicaoVazia(cache_03, TAM_CACHE_03);

    // Cache Vazia
    if(posicaoVazia != -1){
        transfereBloco(cache_03[posicaoVazia], RAM[endereco]);
        return posicaoVazia;
    }
    else if(posicaoVazia == -1){
        int posicaoSelecionada;
        int menor = 10000;

        for (int i = 0; i < TAM_CACHE_03; i++){
            if(cache_03[i]->acessado <= menor){
                menor = cache_03[i]->acessado;
                posicaoSelecionada = i;       
            }
        }
        if(cache_03[posicaoSelecionada]->atualizado == 1){
           
            blocoMemoria* aux = createMemoryBlockCache(1);

            transfereBloco(aux, cache_03[posicaoSelecionada]);
            transfereBloco(cache_03[posicaoSelecionada], RAM[endereco]);
			transfereBloco(RAM[endereco], aux);

            blocoDesatualizado(RAM[endereco]);
            free(aux);

            return posicaoSelecionada;
        }
    }
}   

int transfereDados(blocoMemoria **transportarBloco, blocoMemoria **recebeBloco, int cache_posicao_aux){

    int posicaoVazia = getPosicaoVazia(recebeBloco, recebeBloco[0]->tamanho);
    int posicaoSelecionada;

    if (posicaoVazia == -1){
        // Primeiro a ser usado vai ser o primeiro a ser trocado
        int menor = 10000; 
        for (int i = 0; i < recebeBloco[0]->tamanho; i++){
            if(recebeBloco[i]->acessado < menor){
                menor = recebeBloco[i]->acessado;
                posicaoSelecionada = i;       
            }
        }
        
        blocoMemoria *aux = createMemoryBlockCache(1);
        transfereBloco(aux, recebeBloco[posicaoSelecionada]);
        transfereBloco(recebeBloco[posicaoSelecionada], transportarBloco[cache_posicao_aux]);
        transfereBloco(transportarBloco[cache_posicao_aux], aux);
        
        free(aux);
        return posicaoSelecionada;
    }
    else if(posicaoVazia != -1){
        blocoMemoria *aux = createMemoryBlockCache(1);
        transfereBloco(aux, recebeBloco[posicaoVazia]);
        transfereBloco(recebeBloco[posicaoVazia], transportarBloco[cache_posicao_aux]);
        transfereBloco(transportarBloco[cache_posicao_aux], aux);
    
        free(aux);
        return posicaoVazia;
    }
}

void transfereBloco(blocoMemoria *recebeBloco, blocoMemoria *transportarBloco){  
    
    recebeBloco->vazio = false;
    recebeBloco->endereco_bloco = transportarBloco->endereco_bloco;  
    recebeBloco->atualizado = transportarBloco->atualizado;
    recebeBloco->palavra[0] = transportarBloco->palavra[0];
    recebeBloco->palavra[1] = transportarBloco->palavra[1];
    recebeBloco->palavra[2] = transportarBloco->palavra[2];
    recebeBloco->palavra[3] = transportarBloco->palavra[3];
    
}

int getPosicaoVazia(blocoMemoria **memoria_cache, int tamanhocache){
    int posicaoVazia;

    for (int i = 0; i < tamanhocache; i++){
        if(memoria_cache[i]->endereco_bloco == -1){
            posicaoVazia = i;
            return posicaoVazia;
        }   
    }
    return -1;
}

void blocoDesatualizado(blocoMemoria *blocoMemoria){
    blocoMemoria->atualizado = false;
    blocoMemoria->acessado = 0;
}

void adicao(Instrucoes *instrucoes, blocoMemoria *cache_01_prim_posicao, blocoMemoria *cache_01_seg_posicao, blocoMemoria *cache_01_terc_posicao){
    int palavra_01 = getPalavra(cache_01_prim_posicao, getEnderecoPalavra(getEND1(instrucoes)));
    int palavra_02 = getPalavra(cache_01_seg_posicao, getEnderecoPalavra(getEND2(instrucoes)));

    int soma = palavra_01 + palavra_02;
    printf("Somando %d com %d e obtendo %d\n", palavra_01, palavra_02, soma);

    setPalavra(cache_01_terc_posicao, getEnderecoPalavra(getEND3(instrucoes)), soma);
    setAtualizado(cache_01_terc_posicao, 1);
}

void subtracao(Instrucoes *instrucoes, blocoMemoria *cache_01_prim_posicao, blocoMemoria *cache_01_seg_posicao, blocoMemoria *cache_01_terc_posicao){
      int palavra_01 = getPalavra(cache_01_prim_posicao, getEnderecoPalavra(getEND1(instrucoes)));
    int palavra_02 = getPalavra(cache_01_seg_posicao, getEnderecoPalavra(getEND2(instrucoes)));

    int sub = palavra_01 - palavra_02;
    printf("Subtraindo %d com %d e obtendo %d\n", palavra_01, palavra_02, sub);

    setPalavra(cache_01_terc_posicao, getEnderecoPalavra(getEND3(instrucoes)), sub);
    setAtualizado(cache_01_terc_posicao, 1);
}