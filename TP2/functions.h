#include <stdbool.h>

# ifndef functions_h
# define functions_h



#define TAM_RAM 100
#define TAM_CACHE_01 16     
#define TAM_CACHE_02 32
#define TAM_CACHE_03 128
#define TAM_INSTRUCOES 10000

#define ADICAO 0
#define SUB 1
#define SAIR -1

typedef struct{
    int endereco_bloco;
    int endereco_palavra;
}Endereco;

Endereco *criarEndereco(int bloco_final, int palavra_final);

int getEnderecoPalavra(Endereco *a);
int getEnderecoBloco(Endereco *a);

typedef struct{
    int opcode;
    Endereco *endereco_01;
    Endereco *endereco_02;
    Endereco *endereco_03;
}Instrucoes;

Instrucoes* criarInstrucao(int opcode, Endereco* end1, Endereco* end2, Endereco* end3);

Endereco* getEND1(Instrucoes* i);
Endereco* getEND2(Instrucoes* i);
Endereco* getEND3(Instrucoes* i);

typedef struct{   
    int endereco_bloco;
    int acessado;
    int cache_hit;
    int cache_miss;
    int tamanho;
    long int custo;
    int palavra[4];
    int atualizado;
    bool vazio; 
}blocoMemoria;

blocoMemoria *createMemoryBlockRAM(int tamanho);
blocoMemoria *createMemoryBlockCache(int tamanho);

int getPalavra(blocoMemoria *m, int end);
void setPalavra(blocoMemoria *m, int ind, int palavra);
void setAtualizado(blocoMemoria *m, int atualizado);

blocoMemoria **alocarRam(int tamanho);

blocoMemoria **alocarCache(int tamanho);

int MMU(blocoMemoria **cache_01, blocoMemoria **cache_02, blocoMemoria **cache_03, blocoMemoria **RAM, Endereco *endereco);

int procuraCache(blocoMemoria **cache, int endereco, int tamanho);

int procuraRAM(blocoMemoria **RAM, blocoMemoria **Cache_03, int endereco);

int transfereDados(blocoMemoria **transportarBloco, blocoMemoria **recebeBloco, int cache_posicao_aux);

int getPosicaoVazia(blocoMemoria **memoria_cache, int tamanhocache);

void transfereBloco(blocoMemoria *recebeBloco, blocoMemoria *transportarBloco);

void blocoDesatualizado(blocoMemoria *blocoMemoria);

void adicao(Instrucoes *instrucoes, blocoMemoria *cache_01_prim_posicao, blocoMemoria *cache_01_seg_posicao, blocoMemoria *cache_01_terc_posicao);

void subtracao(Instrucoes *instrucoes, blocoMemoria *cache_01_prim_posicao, blocoMemoria *cache_01_seg_posicao, blocoMemoria *cache_01_terc_posicao);

# endif