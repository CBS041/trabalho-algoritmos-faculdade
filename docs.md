# 📚 Documentação Técnica Detalhada - Roleta Russa

## 🎯 Visão Geral

**Roleta Russa** é um jogo de azar desenvolvido em **C** que implementa um sistema baseado em probabilidades e gerenciamento de memória dinâmica. O jogador configura números vencedores e tenta ganhar através de um sorteio aleatório que passa por **dois testes independentes**.

### Características Principais

- ✅ **Alocação dinâmica de memória** com `malloc()` e `free()`
- ✅ **Validação robusta** de entradas de usuário
- ✅ **Interface limpa** com limpeza automática de terminal
- ✅ **Tratamento de erros** em todas as operações críticas
- ✅ **Código modularizado** com separação clara de responsabilidades

---

## 🏗️ Estrutura de Dados

### GameConfig (Estrutura Principal)

```c
typedef struct GameConfig {
    int *listaVencedores;    // Ponteiro para array dinâmico
    int tamanhoLista;        // Quantidade de elementos
    int intervaloMax;        // Valor máximo para sorteio
    float probabilidade;     // Probabilidade de passar (0.0-1.0)
} GameConfig;
```

#### Campos Detalhados:

| Campo | Tipo | Descrição | Intervalo |
|-------|------|-----------|-----------|
| `listaVencedores` | `int*` | Array alocado dinamicamente com os números que ganham | N/A |
| `tamanhoLista` | `int` | Quantidade de números vencedores | 1 - 101 |
| `intervaloMax` | `int` | Limite superior do sorteio (inclusive) | Fixo: 100 |
| `probabilidade` | `float` | Probabilidade de passar no teste 1 | Fixo: 0.5 (50%) |

#### Exemplo de Uso:

```c
// Criar configuração
GameConfig cfg;
cfg.listaVencedores = NULL;
cfg.tamanhoLista = 0;
cfg.intervaloMax = 100;
cfg.probabilidade = 0.5f;

// Após configurar (exemplo com 3 números)
cfg.listaVencedores = malloc(sizeof(int) * 3);
cfg.listaVencedores[0] = 10;
cfg.listaVencedores[1] = 50;
cfg.listaVencedores[2] = 90;
cfg.tamanhoLista = 3;
```

---

## 📊 Fluxo Principal do Programa

### Inicialização

```
┌─────────────────────────────────────┐
│ 1. Inicializa srand() com time()    │
│ 2. Cria estrutura GameConfig        │
│ 3. Inicializa campos com NULL/0     │
│ 4. Limpa a tela                     │
└──────────────┬──────────────────────┘
               │
               ▼
          ┌────────┐
          │ MENU   │ ◄────────┐
          └───┬┬┬──┘          │
              │││             │
          1   ││ 2    3       │
          │   ││   │          │
          ▼   ▼▼   ▼          │
        CONFIG JOGAR SAIR     │
          │     │   │         │
          │     │   └─────────┤
          │     └─────────────┤
          └──────────────────┘
```

### Fluxo Detalhado de Execução

```mermaid
main() {
  ├─ srand(time(NULL))
  ├─ Inicializa GameConfig
  ├─ limparTela()
  └─ do-while loop:
     ├─ mostrarMenu()
     ├─ switch(opcao):
     │  ├─ '1': configurarJogo(&cfg)
     │  │   ├─ limparTela()
     │  │   ├─ Lê quantidade de números
     │  │   ├─ malloc para array
     │  │   └─ Loop de leitura com validação
     │  │
     │  ├─ '2': jogarUmaVez(&cfg)
     │  │   ├─ Valida se cfg foi configurado
     │  │   ├─ Sorteia número (0-100)
     │  │   ├─ Sorteia probabilidade (0.0-1.0)
     │  │   └─ Exibe resultado
     │  │
     │  └─ '3': sair = true
     │
     └─ liberarConfig(&cfg)
}
```

---

## 🔧 Documentação de Funções

### 1. `void limparTela(void)`

**Propósito:** Limpar o terminal/console para melhor legibilidade.

**Implementação:**
```c
void limparTela(void)
{
  system("cls");  // Windows específico
}
```

**Quando é chamada:**
- Antes de exibir o menu
- Antes de configurar jogo
- Antes de mostrar resultado
- Ao exibir erros

**Observação:** Usa `system("cls")` que é específico do Windows.

---

### 2. `void limparBuffer(void)`

**Propósito:** Remover caracteres residuais do buffer após `scanf()`.

**Por que é necessário:**
```
Entrada: "123abc\n"
scanf("%d", &x)  → x = 123
Buffer depois:   "abc\n"  ❌ Contaminado

Com limparBuffer():
Lê "abc\n" e descarta
Buffer depois:   ""  ✅ Limpo
```

**Implementação:**
```c
void limparBuffer(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    /* Descarta caracteres */
  }
}
```

---

### 3. `void mostrarMenu(void)`

**Propósito:** Exibir o menu principal com as opções.

**Fluxo:**
```
1. Chama limparTela()
2. Imprime cabeçalho formatado
3. Lista 3 opções:
   - 1. Configurar Jogo
   - 2. Jogar Uma Vez
   - 3. Sair
```

**Saída:**
```
+========================================+
|   ROLETA RUSSA - Garotos do JOB       |
+========================================+
|  1. Configurar Jogo                    |
|  2. Jogar Uma Vez                      |
|  3. Sair                               |
+========================================+
```

---

### 4. `void configurarJogo(GameConfig *cfg)`

**Propósito:** Permitir usuário definir os números vencedores.

**Parâmetros:**
- `cfg`: Ponteiro para estrutura de configuração (será modificada)

**Validações implementadas:**
1. ✅ Verifica se `cfg` não é NULL
2. ✅ Valida quantidade (1-101 números)
3. ✅ Aloca memória com verificação
4. ✅ Impede números duplicados
5. ✅ Valida range (0-100)

**Fluxo Detalhado:**

```
1. Validação de ponteiro nulo
   │
   ├─ if (cfg == NULL) return;
   │
2. Limpeza de tela
   │
   ├─ limparTela();
   │
3. Exibição de informações
   │
   ├─ Probabilidade: 50%
   ├─ Intervalo: 0 a 100
   │
4. Leitura de quantidade
   │
   ├─ lerInteiro("Quantos números?", 1, 101)
   │
5. Liberação de configuração anterior
   │
   ├─ liberarConfig(cfg);
   │
6. Alocação de memória
   │
   ├─ malloc(sizeof(int) * quantidade)
   ├─ if (malloc == NULL) 
   │   └─ Erro e return
   │
7. Loop de leitura
   │
   ├─ for (i = 0; i < quantidade; i++)
   │  ├─ Lê número com lerInteiro()
   │  ├─ Valida não-duplicação
   │  │  for (j = 0; j < i; j++)
   │  │  └─ if (já existe) pede novamente
   │  └─ Armazena em array
   │
8. Atualização de tamanho
   │
   ├─ cfg->tamanhoLista = quantidade
   │
9. Pausa
   │
   └─ getchar() aguarda ENTER
```

**Exemplo de Execução:**

```
Quantos numeros vencedores deseja? (1-101): 3

Digite os 3 numeros vencedores (sem repeticoes):

  Numero 1: 25
  Numero 2: 50
  Numero 3: 25
  [AVISO] Numero ja foi inserido. Tente outro.
  Numero 3: 75

  [OK] Configuracao salva com sucesso!

  Pressione ENTER para continuar...
```

---

### 5. `bool estaNaListaVencedora(int numero, int lista[], int tamanho)`

**Propósito:** Verificar se um número existe no array de vencedores.

**Parâmetros:**
- `numero`: Valor a procurar
- `lista`: Pointer ao array
- `tamanho`: Quantidade de elementos

**Retorno:**
- `true` (1): Número encontrado
- `false` (0): Número não encontrado

**Implementação:**
```c
bool estaNaListaVencedora(int numero, int lista[], int tamanho)
{
  int i;
  
  if (lista == NULL)
    return false;  // Proteção contra NULL
  
  for (i = 0; i < tamanho; i++) {
    if (lista[i] == numero)
      return true;  // Encontrou!
  }
  
  return false;  // Não encontrou
}
```

**Complexidade:** O(n) - linear

**Exemplo:**
```c
int vencedores[] = {10, 25, 50, 75, 90};
estaNaListaVencedora(50, vencedores, 5);  // true
estaNaListaVencedora(99, vencedores, 5);  // false
```

---

### 6. `int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado)`

**Propósito:** Executar uma rodada completa do jogo.

**Parâmetros:**
- `cfg`: Configuração (constante, não será modificada)
- `numeroSorteado`: Ponteiro para armazenar número sorteado

**Retorno:**
- `1`: Jogador GANHOU
- `0`: Jogador PERDEU

**Lógica do Sorteio (Dois Testes Independentes):**

```
┌─────────────────────────────────────────┐
│ TESTE 1: Probabilidade                  │
├─────────────────────────────────────────┤
│ r = rand() / RAND_MAX                   │
│ r = número aleatório entre 0.0 e 1.0    │
│                                         │
│ if (r <= 0.5) {  // 50% de chance       │
│   Passa para TESTE 2                    │
│ } else {                                │
│   Retorna 0 (PERDEU)                    │
│ }                                       │
└─────────────────────────────────────────┘
                  │
                  ▼ (Se passou)
┌─────────────────────────────────────────┐
│ TESTE 2: Verificar Lista Vencedora      │
├─────────────────────────────────────────┤
│ n = rand() % (intervaloMax + 1)         │
│ n = número sorteado 0-100               │
│                                         │
│ if (estaNaListaVencedora(n, lista)) {   │
│   Retorna 1 (GANHOU)                    │
│ } else {                                │
│   Retorna 0 (PERDEU)                    │
│ }                                       │
└─────────────────────────────────────────┘
```

**Implementação:**
```c
int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado)
{
  // Sorteio de probabilidade (0.0 a 1.0)
  float r = (float)rand() / (float)RAND_MAX;
  
  // Sorteio de número (0 a 100)
  int n = rand() % (cfg->intervaloMax + 1);
  
  // Armazena número sorteado
  if (numeroSorteado)
    *numeroSorteado = n;
  
  // Teste 1: Probabilidade
  if (r <= cfg->probabilidade) {
    // Teste 2: Verificar lista
    if (estaNaListaVencedora(n, cfg->listaVencedores, cfg->tamanhoLista)) {
      return 1;  // GANHOU!
    } else {
      return 0;  // PERDEU (número não na lista)
    }
  } else {
    return 0;  // PERDEU (não passou probabilidade)
  }
}
```

**Análise de Probabilidade:**

Com 5 números vencedores em 101 possíveis:

```
P(Ganhar) = P(passar prob) × P(acertar número)
         = 0.5 × (5/101)
         = 0.5 × 0.0495
         ≈ 2.48%

P(Perder) = 1 - 0.0248 ≈ 97.52%
```

---

### 7. `void liberarConfig(GameConfig *cfg)`

**Propósito:** Liberar toda memória alocada e prevenir vazamentos.

**Parâmetros:**
- `cfg`: Ponteiro para estrutura a ser liberada

**Implementação:**
```c
void liberarConfig(GameConfig *cfg)
{
  if (cfg == NULL)
    return;  // Proteção
  
  if (cfg->listaVencedores != NULL) {
    free(cfg->listaVencedores);
    cfg->listaVencedores = NULL;  // Evita use-after-free
  }
  
  cfg->tamanhoLista = 0;  // Reseta
}
```

**Importância:**
```
Sem liberarConfig():
┌──────────────┐
│ Memória Heap │
├──────────────┤
│ malloc()  ←──┼─── Alocado mas nunca liberado
│              │    VAZAMENTO DE MEMÓRIA! ❌
└──────────────┘

Com liberarConfig():
┌──────────────┐
│ Memória Heap │
├──────────────┤
│ free()    ←──┼─── Memória devolvida ao SO
│              │    CORRETO! ✅
└──────────────┘
```

---

### 8. `int lerInteiro(const char *prompt, int min, int max)`

**Propósito:** Ler inteiro com validação de intervalo.

**Parâmetros:**
- `prompt`: Mensagem a exibir
- `min`: Valor mínimo aceito (inclusive)
- `max`: Valor máximo aceito (inclusive)

**Retorno:** Inteiro validado

**Validações:**
1. Verifica se `scanf()` leu corretamente
2. Limpa buffer em caso de erro
3. Valida se está no intervalo [min, max]
4. Repete até sucesso

**Fluxo:**
```
Loop infinito:
  1. Exibe prompt
  2. Tenta ler com scanf
  3. if (leitura falhou)
     - Exibe erro
     - Limpa buffer
     - Continue (volta ao passo 1)
  4. if (valor fora do intervalo)
     - Exibe erro com range
     - Continue
  5. Retorna valor válido
```

**Exemplo:**
```c
int quantidade = lerInteiro(
  "Quantos números? ",
  1,    // mínimo
  101   // máximo
);
```

---

### 9. `float lerFloat(const char *prompt, float min, float max)`

**Propósito:** Ler float com validação de intervalo (similar a `lerInteiro`).

**Diferenças:**
- Usa `scanf("%f")` em vez de `"%d"`
- Valida com limites `float`
- Mensagens formatam com `"%.2f"`

---

## 📋 Tratamento de Erros

### Proteções Implementadas:

| Situação | Tratamento |
|----------|-----------|
| Entrada não-numérica | Rejeita e pede novamente |
| Número fora do intervalo | Mostra range e pede novamente |
| Número duplicado | Aviso e pede outro número |
| malloc() falha | Mensagem de erro e abort |
| NULL pointer access | Validação em todas as funções |
| Jogar sem configurar | Erro e volta ao menu |

---

## 🧪 Exemplos de Uso

### Cenário 1: Uso Normal

```c
GameConfig cfg;
cfg.listaVencedores = NULL;
cfg.tamanhoLista = 0;
cfg.intervaloMax = 100;
cfg.probabilidade = 0.5f;

// Usuário configura com 3 números: 10, 50, 90
// Usuário joga
int sorteado;
int resultado = jogarUmaVez(&cfg, &sorteado);
if (resultado == 1) {
  printf("GANHOU! Numero sorteado: %d\n", sorteado);
} else {
  printf("PERDEU! Numero sorteado: %d\n", sorteado);
}

// Limpa ao final
liberarConfig(&cfg);
```

### Cenário 2: Múltiplas Reconfigurations

```c
GameConfig cfg = {NULL, 0, 100, 0.5f};

// Primeira configuração
configurarJogo(&cfg);  // 3 números

// Segunda configuração (libera anterior)
configurarJogo(&cfg);  // 5 números
// liberarConfig() é chamado dentro automaticamente

// Limpeza final
liberarConfig(&cfg);
```

---

## 📈 Análise de Complexidade

| Função | Tempo | Espaço | Observações |
|--------|-------|--------|------------|
| `limparTela()` | O(1) | O(1) | Chamada de sistema |
| `mostrarMenu()` | O(1) | O(1) | Apenas prints |
| `configurarJogo()` | O(n) | O(n) | n = quantidade de números |
| `estaNaListaVencedora()` | O(n) | O(1) | Busca linear |
| `jogarUmaVez()` | O(n) | O(1) | Chama estaNaListaVencedora |
| `lerInteiro()` | O(k) | O(1) | k = tentativas do usuário |
| `liberarConfig()` | O(1) | O(1) | Apenas free() |

---

## 🔍 Notas de Implementação

### Segurança de Memória

```c
// ✅ CORRETO
int *array = malloc(sizeof(int) * n);
if (array == NULL) {
  fprintf(stderr, "Erro na alocação\n");
  return;
}
// ... usar array ...
free(array);
array = NULL;  // Bom prática

// ❌ ERRADO
int *array = malloc(sizeof(int) * n);
// ... sem verificação ...
// ... sem free() ...
```

### Casting de rand()

```c
// ✅ CORRETO - Evita truncamento
float r = (float)rand() / (float)RAND_MAX;

// ❌ ERRADO - Pode perder precisão
float r = rand() / RAND_MAX;
```

### Buffer de Entrada

```c
// ✅ CORRETO
scanf("%d", &x);
limparBuffer();  // Remove resíduo

// ❌ ERRADO
scanf("%d", &x);
// Próximo scanf() lerá resíduo
```

---

## 📚 Estrutura de Arquivos

```
├── structs.h
│   └── Define: GameConfig
│
├── funcoes.h
│   └── Protótipos de todas as funções
│
├── funcoes.c
│   ├── limparTela()
│   ├── limparBuffer()
│   ├── mostrarMenu()
│   ├── configurarJogo()
│   ├── estaNaListaVencedora()
│   ├── jogarUmaVez()
│   ├── lerInteiro()
│   ├── lerFloat()
│   └── liberarConfig()
│
└── main.c
    └── Coordena fluxo principal
```

---

## 🎓 Conceitos de C Utilizados

- ✅ **Structs**: Agrupar dados relacionados
- ✅ **Ponteiros**: Alocação dinâmica e passagem por referência
- ✅ **malloc/free**: Gerenciamento manual de memória
- ✅ **Arrays dinâmicos**: Flexibilidade de tamanho
- ✅ **Validação de entrada**: `scanf()` com error checking
- ✅ **Modularização**: Separação em múltiplos arquivos
- ✅ **Geração aleatória**: `srand()` e `rand()`

---

## ✨ Boas Práticas Aplicadas

1. **Documentação inline**: Comentários explicam o "por quê"
2. **Validação defensiva**: Checar NULL, ranges, etc
3. **Gerenciamento de memória**: Sempre liberar o que é alocado
4. **Separação de concerns**: Cada função faz uma coisa
5. **Tratamento de erros**: Mensagens claras ao usuário
6. **Interface limpa**: Limpeza de tela após cada ação
7. **Código legível**: Nomes descritivos e indentação clara