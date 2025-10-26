#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "funcoes.h"
#include "structs.h"

/* ============================================
   Fun��o: main
   Descri��o: Fun��o principal do programa
   Retorno: 0 se executado com sucesso
   ============================================ */
int main(void)
{
  /* Inicializa o gerador de N�meros aleat�rios */
  srand((unsigned int)time(NULL));

  /* Declara a estrutura de configura��o do jogo */
  GameConfig cfg;

  /* Inicializa todos os campos para evitar lixo em memória */
  cfg.listaVencedores = NULL;
  cfg.tamanhoLista = 0;
  cfg.intervaloMax = 0;

  char opcao;        /* op��o do usuário */
  bool sair = false; /* Flag para sair do programa */

  /* Limpa a tela no inicio do programa */
  limparTela();

  /* Loop principal do programa */
  do
  {
    /* Exibe o menu */
    mostrarMenu();

    /* Lê a opção do usuário */
    printf("Escolha uma opcao: ");
    opcao = getchar();
    limparBuffer();

    /* Ignora entradas vazias */
    if (opcao == '\n' || opcao == EOF)
      continue;

    /* Menu de opções */
    switch (opcao)
    {
    case '1':
      /* Op��o 1: Configurar Jogo */
      configurarJogo(&cfg);
      break;

    case '2':
      /* Op��o 2: Jogar Uma Vez */
      if (cfg.listaVencedores == NULL)
      {
        limparTela();
        printf("  [ERRO] Jogo nao configurado. Configure primeiro!\n");
        printf("\n  Pressione ENTER para continuar...");
        getchar();
        break;
      }

      /* Declara variável para armazenar número sorteado */
      int sorteado;

      /* Executa uma jogada e armazena resultado */
      int ganhou = jogarUmaVez(&cfg, &sorteado);

      /* Limpa a tela para mostrar resultado */
      limparTela();

      /* Exibe resultado da jogada */
      printf("\n");
      printf("+========================================+\n");
      printf("|          RESULTADO DA JOGADA           |\n");
      printf("+========================================+\n");
      printf("|  Numero Sorteado: %d\n", sorteado);
      printf("|  Resultado: %s\n", ganhou ? "[VENCEU!]" : "[PERDEU!]");
      printf("+========================================+\n");
      printf("\n  Pressione ENTER para continuar...");
      getchar();
      break;

    case '3':
      /* Op��o 3: Sair */
      sair = true;
      break;

    default:
      /* Op��o inválida */
      printf("  [ERRO] Opcao invalida. Escolha novamente.\n");
      break;
    }
  } while (!sair);

  /* Libera mem�ria antes de encerrar */
  liberarConfig(&cfg);

  printf("\n  Obrigado por jogar! Ate logo!\n\n");
  return 0;
}
