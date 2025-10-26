#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "structs.h"
#include "funcoes.h"

/*
   Fun��o: limparTela
   Descri��o: Limpa o terminal/console
  */

void limparTela(void)
{
  /* No Windows, usa o comando 'cls' */
  system("cls");
}
void limparBuffer(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
    /* Descartando caracteres até encontrar nova linha */
  }
}

/*
   FUNÇÃO: mostrarMenu
   Descrição: Exibe o menu principal do jogo
    */
void mostrarMenu(void)
{
  /* Limpa o terminal */
  limparTela();

  printf("\n");
  printf("+========================================+\n");
  printf("|   ROLETA RUSSA - Garotos do JOB       |\n");
  printf("+========================================+\n");
  printf("|  1. Configurar Jogo                    |\n");
  printf("|  2. Jogar Uma Vez                      |\n");
  printf("|  3. Sair                               |\n");
  printf("+========================================+\n");
}

/*
   FUNÇÃO: liberarConfig
   Descrição: Libera toda a memória alocada
   Parâmetros: cfg - ponteiro para estrutura GameConfig
    */
void liberarConfig(GameConfig *cfg)
{
  /* Valida se o ponteiro não é nulo */
  if (cfg == NULL)
    return;

  /* Libera a lista de números vencedores se foi alocada */
  if (cfg->listaVencedores != NULL)
  {
    free(cfg->listaVencedores);
    cfg->listaVencedores = NULL;
  }

  /* Reseta o tamanho */
  cfg->tamanhoLista = 0;
}

/*
   FUNÇÃO: lerInteiro
   Descrição: Lê um inteiro com validação de intervalo
   Parâmetros:
     - prompt: mensagem a exibir
     - min: valor mínimo aceito
     - max: valor máximo aceito
   Retorno: inteiro validado
    */
int lerInteiro(const char *prompt, int min, int max)
{
  int x;   // Variável para armazenar entrada
  int res; // Resultado da leitura com scanf

  while (1)
  {
    printf("%s", prompt);
    res = scanf("%d", &x);

    /* Valida se a leitura foi bem-sucedida */
    if (res != 1)
    {
      printf("  [ERRO] Entrada invalida. Digite um numero inteiro.\n");
      limparBuffer();
      continue;
    }

    limparBuffer();

    /* Valida se o número está no intervalo permitido */
    if (x < min || x > max)
    {
      printf("  [ERRO] Valor fora do intervalo (%d - %d). Tente novamente.\n", min, max);
      continue;
    }

    return x; /* Retorna o inteiro válido */
  }
}

/*
   FUNÇÃO: lerFloat
   Descrição: Lê um float com validação de intervalo
   Parâmetros:
     - prompt: mensagem a exibir
     - min: valor mínimo aceito
     - max: valor máximo aceito
   Retorno: float validado
    */
float lerFloat(const char *prompt, float min, float max)
{
  float x; // Variável para armazenar entrada
  int res; // Resultado da leitura com scanf

  while (1)
  {
    printf("%s", prompt);
    res = scanf("%f", &x);

    /* Valida se a leitura foi bem-sucedida */
    if (res != 1)
    {
      printf("  [ERRO] Entrada invalida. Digite um numero decimal.\n");
      limparBuffer();
      continue;
    }

    limparBuffer();

    /* Valida se o número está no intervalo permitido */
    if (x < min || x > max)
    {
      printf("  [ERRO] Valor fora do intervalo (%.2f - %.2f). Tente novamente.\n", min, max);
      continue;
    }

    return x; /* Retorna o float válido */
  }
}

/*
   FUNÇÃO: configurarJogo
   Descrição: Configura o jogo permitindo que o usuário
              insira os números vencedores
   Parâmetros: cfg - ponteiro para estrutura GameConfig
    */
void configurarJogo(GameConfig *cfg)
{
  int i, j; // Variáveis de iteração

  /* Valida se o ponteiro não é nulo */
  if (cfg == NULL)
    return;

  /* Limpa o terminal */
  limparTela();

  printf("\n");
  printf("+========================================+\n");
  printf("|       CONFIGURE O JOGO                |\n");
  printf("+========================================+\n");

  /* Define valores fixos do jogo */
  cfg->intervaloMax = 100; // Números de 0 a 100

  printf("  - Intervalo: 0 a 100\n\n");

  /* Lê a quantidade de números vencedores */
  int tamanhoListaVencedores = lerInteiro(
      "  Quantos numeros vencedores deseja? (1-100): ",
      1,
      cfg->intervaloMax + 1);

  /* Libera configuração anterior, se existir */
  liberarConfig(cfg);

  /* Aloca espaço em memória para os números vencedores */
  cfg->listaVencedores = (int *)malloc(sizeof(int) * (size_t)tamanhoListaVencedores);

  /* Valida se a alocação foi bem-sucedida */
  if (cfg->listaVencedores == NULL)
  {
    fprintf(stderr, "  [ERRO] Falha na alocacao de memoria!\n");
    cfg->tamanhoLista = 0;
    return;
  }

  printf("\n  Digite os %d numeros vencedores (sem repeticoes):\n\n", tamanhoListaVencedores);

  /* Loop para ler cada número vencedor */
  for (i = 0; i < tamanhoListaVencedores; i++)
  {
    bool ok = false; // Flag para validar número duplicado
    int num = 0;

    /* Loop até conseguir um número válido e único */
    while (!ok)
    {
      char prompt[80];
      snprintf(prompt, sizeof(prompt), "  Numero %d: ", i + 1);
      num = lerInteiro(prompt, 0, cfg->intervaloMax);

      ok = true; /* Assume que o número é válido */

      /* Verifica se o número já foi inserido */
      for (j = 0; j < i; j++)
      {
        if (cfg->listaVencedores[j] == num)
        {
          printf("  [AVISO] Numero ja foi inserido. Tente outro.\n");
          ok = false;
          break;
        }
      }
    }

    cfg->listaVencedores[i] = num;
  }

  cfg->tamanhoLista = tamanhoListaVencedores;
  printf("\n  [OK] Configuracao salva com sucesso!\n");
  printf("\n  Pressione ENTER para continuar...");
  getchar();
}

/*
   FUNÇÃO: estaNaListaVencedora
   Descrição: Verifica se um número está na lista de vencedores
   Parâmetros:
     - numero: número a buscar
     - lista: array de números vencedores
     - tamanho: tamanho da lista
   Retorno: true se encontrado, false caso contrário
    */
bool estaNaListaVencedora(int numero, int lista[], int tamanho)
{
  int i; // Variável de iteração

  /* Valida se a lista não é nula */
  if (lista == NULL)
    return false;

  /* Percorre toda a lista procurando o número */
  for (i = 0; i < tamanho; i++)
  {
    if (lista[i] == numero)
      return true; /* Encontrou! */
  }

  return false; /* Não encontrou */
}

/*
   FUNÇÃO: jogarUmaVez
   Descrição: Executa uma rodada do jogo
   Parâmetros:
     - cfg: configuração do jogo
     - numeroSorteado: ponteiro para armazenar número sorteado
   Retorno: 1 se ganhou, 0 se perdeu
    */
int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado)
{
  /* Sorteio do número inteiro (0 a intervaloMax) */
  int n = rand() % (cfg->intervaloMax + 1);

  /* Armazena o número sorteado se o ponteiro for válido */
  if (numeroSorteado)
    *numeroSorteado = n;

  if (estaNaListaVencedora(n, cfg->listaVencedores, cfg->tamanhoLista))
  {
    return 1; /* Ganhou! */
  }
  else
  {
    return 0; /* Número não está na lista */
  }
}
