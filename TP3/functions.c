
#include "functions.h"

int cont = 0;

Endereco* criarEndereco(int end_block, int end_word){
    Endereco *new = malloc(sizeof(Endereco));
    new->end_bloco = end_block;
    new->end_palavra = end_word;
    
    return new;
}

int getEndpalavra(Endereco *a){
	return a->end_palavra;
}

int getEndBloco(Endereco *a){
	return a->end_bloco;
}

Instrucoes* criarInstrucao(int opcode, Endereco* ad1, Endereco* ad2, Endereco* ad3){
	Instrucoes *new = malloc(sizeof(Instrucoes));
	new->opcode = opcode;
	new->end_01 = ad1;
	new->end_02 = ad2;
	new->end_03 = ad3;
	return new;
}

Endereco* getAD1(Instrucoes* i){
	return i->end_01;
}

Endereco* getAD2(Instrucoes* i){
	return i->end_02;
}

Endereco* getAD3(Instrucoes* i){
	return i->end_03;
}

BlocoMemoria *criarBlocoMem(int tamanho){
    BlocoMemoria *new = malloc(sizeof(BlocoMemoria));

    for(int i = 0; i < 4; i++){
	    new->palavra[i] = -1;
    }

    new->tamanho = tamanho;
    new->vazio = true;
    new->atualizado = 0;
    new->hit = 0;
    new->miss = 0;
    new->acessado = 0;
    new->cost = 0;

    return new;
}

BlocoMemoria **criarMemoria(int tamanho){
   
    BlocoMemoria **new = malloc(tamanho * sizeof(BlocoMemoria));

    for (int i = 0; i < tamanho; i++){
        new[i] = criarBlocoMem(tamanho);
        new[i]->end_bloco = -1;
    }

    return new;
}

int getPalavra(BlocoMemoria *m, int ad){
	return m->palavra[ad];
}

void setPalavra(BlocoMemoria *m, int ind, int word){
	m->palavra[ind] = word;	
}

void setAtualizado(BlocoMemoria *m, int updated){
	m->atualizado = updated;
}

void criarHD(int tamanho){
    int palavra;
    srand(time(NULL));

    FILE *HD = fopen("HD.bin", "wb");

    for (int i = 0; i < tamanho; i++){
        palavra = rand() % 3;
        fwrite(&palavra, sizeof(int), 1, HD);
    }
    fclose(HD);
}

int MMU(BlocoMemoria **cache_01, BlocoMemoria **cache_02, BlocoMemoria **cache_03, BlocoMemoria **RAM, Endereco *endereco){

    int posicao_cache = 0;

    if(procurarCache(cache_01, endereco->end_bloco, TAM_CACHE_01) != -1){

        posicao_cache = procurarCache(cache_01, endereco->end_bloco, TAM_CACHE_01);
        
        cache_01[0]->hit += 1;
        
        cache_01[0]->cost += 1;
        
        return posicao_cache;
    }
    else if(procurarCache(cache_02, endereco->end_bloco, TAM_CACHE_02) != -1){

        posicao_cache = procurarCache(cache_02, endereco->end_bloco, TAM_CACHE_02);
        posicao_cache = tranferirDado(cache_02, cache_01, posicao_cache);
        
        cache_02[0]->hit += 1;
        
        cache_01[0]->miss += 1;     
        
        cache_02[0]->cost += 10;
        
        return posicao_cache;
    }
   
    else if(procurarCache(cache_03, endereco->end_bloco, TAM_CACHE_03) != -1){
        
        posicao_cache = procurarCache(cache_03, endereco->end_bloco, TAM_CACHE_03);
        posicao_cache = tranferirDado(cache_03, cache_02, posicao_cache);
        posicao_cache = tranferirDado(cache_02, cache_01, posicao_cache);
        
        cache_03[0]->hit += 1;
        
        cache_01[0]->miss += 1;
        cache_02[0]->miss += 1;     

        cache_03[0]->cost += 100;

        return posicao_cache;
    }

    else if(procurarCache(RAM, endereco->end_bloco, TAM_RAM) != -1){

        posicao_cache = tranferirDado(RAM, cache_03, posicao_cache);
        posicao_cache = tranferirDado(cache_03, cache_02, posicao_cache);
        posicao_cache = tranferirDado(cache_02, cache_01, posicao_cache);       
        
        cache_01[0]->miss += 1;   
        cache_02[0]->miss += 1;   
        cache_03[0]->miss += 1;

        RAM[0]->hit += 1;

        RAM[0]->cost += 5000;
        
        return posicao_cache;
    }
    else{

        posicao_cache = procurarHD(RAM, endereco->end_bloco, TAM_RAM);
        posicao_cache = tranferirDado(RAM, cache_03, posicao_cache);
        posicao_cache = tranferirDado(cache_03, cache_02, posicao_cache);
        posicao_cache = tranferirDado(cache_02, cache_01, posicao_cache);  

        cache_01[0]->miss += 1;   
        cache_02[0]->miss += 1;   
        cache_03[0]->miss += 1;
        RAM[0]->miss += 1;

        RAM[1]->cost += 100000;
        RAM[1]->hit += 1;

        return posicao_cache; 
        
    }
}

int procurarCache(BlocoMemoria **cache, int address, int tamanho){  
    for(int i = 0; i < tamanho; i++){
        if((cache[i]->end_bloco) == (address)){
            cont += 1;
            cache[i]->acessado = cont;
            return i;
        }
    }
    return -1;
}

int procurarHD(BlocoMemoria **RAM, int endereco, int tamanho){
    
    BlocoMemoria *aux_troca = criarBlocoMem(1);
   
    FILE *HD = fopen("HD.bin", "rb");
    
    fseek(HD, endereco * 16, SEEK_SET); //ir p/ bitoffset do hd

    for(int i = 0; i < 4; i++ ){
        fread(&aux_troca->palavra[i], sizeof(int), 1, HD); //salva em buffer
    }
    
    int posicaoVazia = getPosicaoVazia(RAM);

    if(posicaoVazia != -1){
        
        transfereBloco(RAM[posicaoVazia], aux_troca);
        RAM[posicaoVazia]->end_bloco = endereco; 
        free(aux_troca);
        
        return posicaoVazia;
    }
    else{
        
        int menor = 279888; 
        int posTroca = 0;
        
        for (int i = 0; i < TAM_RAM; i++){
            if(RAM[i]->acessado < menor){
                menor = RAM[i]->acessado;
                posTroca = i;       
            }
        }

        if(RAM[posTroca]->atualizado == 1){
            
            HD = fopen("HD.bin","wb"); //escreve
        
            BlocoMemoria *palavra_aux = criarBlocoMem(1); 

            transfereBloco(palavra_aux, RAM[posTroca]);
            transfereBloco(RAM[posTroca], aux_troca);
            transfereBloco(aux_troca, palavra_aux);
           
            blocoDesatualizado(RAM[posTroca]);
            
            for(int i = 0; i < 4; i++){
                fseek(HD, -sizeof(int), SEEK_CUR); //volta o bit
            }

            for(int i = 0;i < 4; i++){
                fwrite(&aux_troca->palavra[i], sizeof(int), 1, HD); //escreve no arquivo
            }
            
			fclose(HD);

            RAM[posTroca]->end_bloco = endereco;
            free(aux_troca);
            free(palavra_aux);

            return posTroca;
        }
        
        transfereBloco(RAM[posTroca], aux_troca);
        RAM[posTroca]->end_bloco = endereco; 
        
        free(aux_troca);
        
        return posTroca;   
    }
}

int tranferirDado(BlocoMemoria **blocoOrigem, BlocoMemoria **blocoDestino, int cache_position_aux){

    int posicaoVazia = getPosicaoVazia(blocoDestino);
    int selectedPosition = 0;

    if (posicaoVazia == -1){

        int menor = 10000; 
        for (int i = 0; i < blocoDestino[0]->tamanho; i++){
            if(blocoDestino[i]->acessado < menor){
                menor = blocoDestino[i]->acessado;
                selectedPosition = i;       
            }
        }
        
        BlocoMemoria *aux = criarBlocoMem(1);
        transfereBloco(aux, blocoDestino[selectedPosition]);
        transfereBloco(blocoDestino[selectedPosition], blocoOrigem[cache_position_aux]);
        transfereBloco(blocoOrigem[cache_position_aux], aux);
        
        free(aux);
        return selectedPosition;
    }    

    BlocoMemoria *aux = criarBlocoMem(1);

    transfereBloco(aux, blocoDestino[posicaoVazia]);
    transfereBloco(blocoDestino[posicaoVazia], blocoOrigem[cache_position_aux]);
    transfereBloco(blocoOrigem[cache_position_aux], aux);
    
    free(aux);
    return posicaoVazia;
}

void transfereBloco(BlocoMemoria *blocoDestino, BlocoMemoria *blocoOrigem){  
    
    blocoDestino->vazio = false;
    blocoDestino->end_bloco = blocoOrigem->end_bloco;  
    blocoDestino->atualizado = blocoOrigem->atualizado;
    blocoDestino->palavra[0] = blocoOrigem->palavra[0];
    blocoDestino->palavra[1] = blocoOrigem->palavra[1];
    blocoDestino->palavra[2] = blocoOrigem->palavra[2];
    blocoDestino->palavra[3] = blocoOrigem->palavra[3];
    
}

void transferePalavra(int *blocoDestino, int *blocoOrigem){  
    blocoDestino[0] = blocoOrigem[0];   
    blocoDestino[1] = blocoOrigem[1];   
    blocoDestino[2] = blocoOrigem[2];   
    blocoDestino[3] = blocoOrigem[3];   
}

int getPosicaoVazia(BlocoMemoria **memory_cache){
    int posicaoVazia;

    for (int i = 0; i < memory_cache[0]->tamanho; i++){
        if(memory_cache[i]->end_bloco == -1){
            posicaoVazia = i;
            return posicaoVazia;
        }   
    }
    return -1;
}

void blocoDesatualizado(BlocoMemoria *MemoryBlock){
    MemoryBlock->atualizado = 0;
    MemoryBlock->acessado = 0;
}

void soma(Instrucoes *instructions, BlocoMemoria *cache_01_frist_position, BlocoMemoria *cache_01_second_position, BlocoMemoria *cache_01_third_position){
    int word_01 = getPalavra(cache_01_frist_position, getEndpalavra(getAD1(instructions)));
    int word_02 = getPalavra(cache_01_second_position, getEndpalavra(getAD2(instructions)));

    int sum = word_01 + word_02;

    setPalavra(cache_01_third_position, getEndpalavra(getAD3(instructions)), sum);
    setAtualizado(cache_01_third_position, 1);
}

void subtracao(Instrucoes *instructions, BlocoMemoria *cache_01_frist_position, BlocoMemoria *cache_01_second_position, BlocoMemoria *cache_01_third_position){
    int word_01 = getPalavra(cache_01_frist_position, getEndpalavra(getAD1(instructions)));
    int word_02 = getPalavra(cache_01_second_position, getEndpalavra(getAD2(instructions)));

    int sub = word_01 - word_02;

    setPalavra(cache_01_third_position, getEndpalavra(getAD3(instructions)), sub);
    setAtualizado(cache_01_third_position, 1);
}