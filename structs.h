#ifndef STRUCTS_H
#define STRUCTS_H

/* Estrutura de configura��o do jogo - Roleta Russa */
typedef struct GameConfig {
    int *listaVencedores;    // Ponteiro para array de n�meros vencedores
    int tamanhoLista;        // Quantidade de n�meros vencedores
    int intervaloMax;        // n�mero m�ximo para sorteio
} GameConfig;

#endif /* STRUCTS_H */
