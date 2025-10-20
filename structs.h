#ifndef STRUCTS_H
#define STRUCTS_H

/* Estrutura de configuração do jogo - Roleta Russa */
typedef struct GameConfig {
    int *listaVencedores;    // Ponteiro para array de números vencedores
    int tamanhoLista;        // Quantidade de números vencedores
    int intervaloMax;        // Número máximo para sorteio
    float probabilidade;     // Probabilidade de passar no teste (0.0 a 1.0)
} GameConfig;

#endif /* STRUCTS_H */
