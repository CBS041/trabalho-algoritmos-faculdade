#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>
#include "structs.h"

/* Função para limpar o terminal */
void limparTela(void);

/* Função para limpar buffer de entrada */
void limparBuffer(void);

/* Exibe o menu principal do jogo */
void mostrarMenu(void);

/* Libera a memória alocada pela configuração */
void liberarConfig(GameConfig *cfg);

/* Lê um inteiro com validação de intervalo */
int lerInteiro(const char *prompt, int min, int max);

/* Lê um float com validação de intervalo */
float lerFloat(const char *prompt, float min, float max);

/* Configura o jogo: define números vencedores */
void configurarJogo(GameConfig *cfg);

/* Verifica se um número está na lista de vencedores */
bool estaNaListaVencedora(int numero, int lista[], int tamanho);

/* Executa uma jogada única */
int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado);

#endif /* FUNCOES_H */
