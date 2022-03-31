#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM_CACHE_01 8    
#define TAM_CACHE_02 16  
#define TAM_CACHE_03 32
#define TAM_RAM 64
#define TAM_HD 5000
#define TAM_INSTRUCTIONS 1000  
#define TAM_INTERRUPTION_INSTRUCTIONS 900

typedef struct{
    int end_bloco;
    int end_palavra;
}Endereco;


typedef struct{
    int opcode;
    Endereco *end_01;
    Endereco *end_02;
    Endereco *end_03;
}Instrucoes;


typedef struct{   
    int end_bloco;
    int acessado;
    int hit;
    int miss;
    int tamanho;
    long int cost;
    int palavra[4];
    int atualizado;
    bool vazio; 
}BlocoMemoria;

Endereco *criarEndereco(int end_block, int end_word);

int getEndpalavra(Endereco *a);
int getEndBloco(Endereco *a);


Instrucoes* criarInstrucao(int opcode, Endereco* ad1, Endereco* ad2, Endereco* ad3);

Endereco* getAD1(Instrucoes* i);
Endereco* getAD2(Instrucoes* i);
Endereco* getAD3(Instrucoes* i);


BlocoMemoria *criarBlocoMem(int tamanho);

int getPalavra(BlocoMemoria *m, int ad);
void setPalavra(BlocoMemoria *m, int ind, int word);
void setAtualizado(BlocoMemoria *m, int atualizado);

BlocoMemoria **criarMemoria(int tamanho);

void criarHD(int tamanho);

int MMU(BlocoMemoria **cache_01, BlocoMemoria **cache_02, BlocoMemoria **cache_03, BlocoMemoria **RAM, Endereco *address);

int procurarCache(BlocoMemoria **cache, int address, int tamanho);

int procurarHD(BlocoMemoria **RAM, int address, int tamanho);

int tranferirDado(BlocoMemoria **carrierBlock, BlocoMemoria **receivingBlock, int cache_position_aux);

int getPosicaoVazia(BlocoMemoria **memory_cache);

void transfereBloco(BlocoMemoria *receivingBlock, BlocoMemoria *carrierBlock);

void transferePalavra(int *receivingBlock, int *carrierBlock);

void blocoDesatualizado(BlocoMemoria *MemoryBlock);

void soma(Instrucoes *instructions, BlocoMemoria *cache_01_frist_position, BlocoMemoria *cache_01_second_position, BlocoMemoria *cache_01_third_position);

void subtracao(Instrucoes *instructions, BlocoMemoria *cache_01_frist_position, BlocoMemoria *cache_01_second_position, BlocoMemoria *cache_01_third_position);