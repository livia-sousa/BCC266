# ifndef comandos_h
# define comandos_h

typedef struct memoria Memoria;

Memoria *alocaMemoria();

void liberaMemoria(Memoria *memoria);

int *retornaRAM(Memoria *memoria);

void montarRam();

void instrucoesProgramaAleatorio(Memoria *memoria);

void maquina(Memoria *memoria);

void maquinaInterpretada(int *umaInstrucao, Memoria *memoria);

int *retornaRAM(Memoria *memoria);

double funcaoSoma(Memoria *memoria, int n1, int n2);

double funcaoSubtracao(Memoria *memoria, int n1, int n2);

double funcaoMultiplicacao(Memoria *memoria, int n1, long int n2);

double funcaoDivisao(Memoria *memoria, int num1, int num2);

double funcaoPotencia(Memoria *memoria, int base, int expoente);

double funcaoSomadosQuadrados(Memoria *memoria, int n1, int n2);

double funcaoFatorial(Memoria *memoria, int termo);

double funcaoAreaTriangulo(Memoria *memoria, int base, int altura);

double funcaoAreaQuadrado (Memoria *memoria, int base);

double funcaoAreaRetangulo(Memoria *memoria, int baseMaior, int baseMenor);

double funcaoPerimetroTriangulo(Memoria *memoria, int base, int lado1, int lado2);

double funcaoPerimetroQuadrado(Memoria *memoria, int base);

double funcaoPerimetroRetangulo(Memoria *memoria, int baseMaior, int baseMenor);

double funcaoVolumeParalelepipedo(Memoria *memoria, int comprimento, int largura, int altura);

double funcaoVolumePiramide(Memoria *memoria, int areabase, int altura);

double funcaoVolumeCubo(Memoria *memoria, int lado);

double funcaoVelocidadeMedia(Memoria *memoria, int distancia, int tempo);

double funcaoAceleracaoMedia(Memoria *memoria, int velocidade, int tempo);

double funcaoDistanciaPercorrida(Memoria *memoria, int velocidade, int tempo);

double funcaoForca(Memoria *memoria, int massa, int aceleracao);

double funcaoEnergia(Memoria *memoria, int massa);

double funcaoCelsius_Kelvin(Memoria *memoria, int temperatura);

double funcaoKelvin_Celsius(Memoria *memoria, int temperatura);

double funcaoHoraMin(Memoria *memoria, int hora);

double funcaoMinSeg(Memoria *memoria, int minuto);

double funcaoMinHora(Memoria *memoria, int minutos);

double funcaoSegMin(Memoria *memoria, int segundos);

void Menu(Memoria *memoria);
# endif