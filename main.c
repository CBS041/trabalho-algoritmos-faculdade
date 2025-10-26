#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "funcoes.h"
#include "structs.h"

/* ============================================
   Função: main
   Descrição: Função principal do programa
   Retorno: 0 se executado com sucesso
   ============================================ */
int main(void)
{
  /* Inicializa o gerador de Números aleatórios */
  srand((unsigned int)time(NULL));

  /* Declara a estrutura de configuração do jogo */
  GameConfig cfg;

  /* Inicializa todos os campos para evitar lixo em memÃ³ria */
  cfg.listaVencedores = NULL;
  cfg.tamanhoLista = 0;
  cfg.intervaloMax = 0;

  char opcao;        /* opção do usuÃ¡rio */
  bool sair = false; /* Flag para sair do programa */

  /* Limpa a tela no inicio do programa */
  limparTela();

  /* Loop principal do programa */
  do
  {
    /* Exibe o menu */
    mostrarMenu();

    /* LÃª a opÃ§Ã£o do usuÃ¡rio */
    printf("Escolha uma opcao: ");
    opcao = getchar();
    limparBuffer();

    /* Ignora entradas vazias */
    if (opcao == '\n' || opcao == EOF)
      continue;

    /* Menu de opÃ§Ãµes */
    switch (opcao)
    {
    case '1':
      /* Opção 1: Configurar Jogo */
      configurarJogo(&cfg);
      break;

    case '2':
      /* Opção 2: Jogar Uma Vez */
      if (cfg.listaVencedores == NULL)
      {
        limparTela();
        printf("  [ERRO] Jogo nao configurado. Configure primeiro!\n");
        printf("\n  Pressione ENTER para continuar...");
        getchar();
        break;
      }

      /* Declara variÃ¡vel para armazenar nÃºmero sorteado */
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
      /* Opção 3: Sair */
      sair = true;
      break;

    default:
      /* Opção invÃ¡lida */
      printf("  [ERRO] Opcao invalida. Escolha novamente.\n");
      break;
    }
  } while (!sair);

  /* Libera memória antes de encerrar */
  liberarConfig(&cfg);

  printf("\n  Obrigado por jogar! Ate logo!\n\n");
  return 0;
}
