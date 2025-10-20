# 🎰 Roleta Russa - Documentação do Projeto

## 📋 Descrição Geral

**Roleta Russa** é um jogo de azar desenvolvido em **C** que combina probabilidade e sorte. O jogador configura números vencedores e tenta acertar através de um sorteio aleatório que passa por dois testes: um teste de **probabilidade** e uma verificação contra a **lista de números vencedores**.

O programa possui uma **interface limpa e intuitiva** com limpeza automática de terminal após cada ação.

---

## 🎯 Objetivo

O objetivo do jogo é ganhar acertando em números que foram configurados como vencedores. O jogo usa:
- **Probabilidade**: 50% de chance de passar na primeira etapa
- **Sorteio**: Números de 0 a 100
- **Validação**: Verificar se o número sorteado está na lista de vencedores

---

## 🏗️ Estrutura do Projeto

```
roleta-russa/
├── structs.h          # Definições de estruturas
├── structs.c          # (Arquivo vazio - não usar)
├── funcoes.h          # Protótipos de funções
├── funcoes.c          # Implementação das funções
├── main.c             # Programa principal
├── Makefile           # Compilação automática
├── README.md          # Este arquivo
└── roleta.exe         # Executável compilado
```

---

## 📊 Estrutura de Dados

### GameConfig

A estrutura principal que armazena toda a configuração do jogo:

```c
typedef struct GameConfig {
    int *listaVencedores;    // Ponteiro para array de números vencedores
    int tamanhoLista;        // Quantidade de números na lista
    int intervaloMax;        // Número máximo para sorteio (100)
    float probabilidade;     // Probabilidade de passar (0.5 = 50%)
} GameConfig;
```

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `listaVencedores` | `int *` | Array dinâmico contendo números que vencem |
| `tamanhoLista` | `int` | Número de elementos em `listaVencedores` |
| `intervaloMax` | `int` | Valor máximo para sorteio (padrão: 100) |
| `probabilidade` | `float` | Probabilidade de passar (padrão: 0.5) |

---

## 🔧 Funções Principais

### 1. `void limparTela(void)`
Limpa o terminal/console para exibir novos conteúdos de forma limpa.

**Uso:** Chamada automaticamente antes de:
- Mostrar o menu principal
- Configurar o jogo
- Exibir resultado da jogada
- Mostrar mensagens de erro

**Nota:** Usa `system("cls")` no Windows.

---

### 2. `void configurarJogo(GameConfig *cfg)`
Permite que o usuário defina os números vencedores.

**Parâmetros:**
- `cfg`: Ponteiro para a estrutura de configuração

**Fluxo:**
1. Limpa a tela
2. Solicita quantos números vencedores o usuário deseja
3. Aloca memória para esses números
4. Lê cada número com validação
5. Impede números duplicados
6. Exibe mensagem de sucesso
7. Aguarda pressionamento de ENTER

**Exemplo:**
```
Quantos numeros vencedores deseja? (1-101): 3
Digite os 3 numeros vencedores (sem repeticoes):
  Numero 1: 25
  Numero 2: 50
  Numero 3: 75

  [OK] Configuracao salva com sucesso!

  Pressione ENTER para continuar...
```

---

### 3. `int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado)`
Executa uma rodada do jogo.

**Parâmetros:**
- `cfg`: Configuração do jogo
- `numeroSorteado`: Ponteiro para armazenar o número sorteado

**Retorno:**
- `1`: Jogador ganhou
- `0`: Jogador perdeu

**Lógica:**
```
1. Sorteia um valor de probabilidade (0.0 a 1.0)
2. Sorteia um número inteiro (0 a 100)
3. Se probabilidade <= 0.5:
   - Verifica se o número está na lista vencedora
   - Retorna 1 se sim, 0 se não
4. Senão:
   - Retorna 0 (não passou no teste)
```

---

### 4. `bool estaNaListaVencedora(int numero, int lista[], int tamanho)`
Verifica se um número existe na lista de vencedores.

**Parâmetros:**
- `numero`: Número a procurar
- `lista`: Array de números vencedores
- `tamanho`: Tamanho do array

**Retorno:**
- `true`: Número encontrado
- `false`: Número não encontrado

---

### 5. `void liberarConfig(GameConfig *cfg)`
Libera toda a memória alocada dinâmicamente.

**Importante:** Deve ser chamada antes de encerrar o programa para evitar vazamento de memória.

---

### Funções Auxiliares

#### `void limparBuffer(void)`
Remove caracteres residuais do buffer de entrada após `scanf()`.

#### `int lerInteiro(const char *prompt, int min, int max)`
Lê um inteiro com validação de intervalo. Repete até conseguir uma entrada válida.

#### `float lerFloat(const char *prompt, float min, float max)`
Lê um float com validação de intervalo.

---

## 🎮 Como Usar

### Compilação
```bash
make
```
ou
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c funcoes.c -o roleta.exe
```

### Execução
```bash
.\roleta.exe
```

### Menu Interativo

1. **Configurar Jogo**: Defina os números vencedores
   - Escolha a quantidade de números
   - Digite cada número sem repetições
   - Pressione ENTER para confirmar

2. **Jogar Uma Vez**: Execute uma rodada
   - Veja o número sorteado
   - Resultado instantâneo
   - Pressione ENTER para voltar ao menu

3. **Sair**: Encerre o programa
   - Memória é liberada automaticamente

### Exemplo de Uso Completo

```
+========================================+
|   ROLETA RUSSA - Garotos do JOB       |
+========================================+
|  1. Configurar Jogo                    |
|  2. Jogar Uma Vez                      |
|  3. Sair                               |
+========================================+

Escolha uma opcao: 1

[Tela Limpa - Novo Menu de Configuração]

+========================================+
|       CONFIGURE O JOGO                |
+========================================+
  - Probabilidade: 50% (0.5)
  - Intervalo: 0 a 100

  Quantos numeros vencedores deseja? (1-101): 3

  Digite os 3 numeros vencedores (sem repeticoes):

  Numero 1: 10
  Numero 2: 50
  Numero 3: 90

  [OK] Configuracao salva com sucesso!

  Pressione ENTER para continuar...

[Tela Limpa - Volta ao Menu Principal]

+========================================+
|   ROLETA RUSSA - Garotos do JOB       |
+========================================+
|  1. Configurar Jogo                    |
|  2. Jogar Uma Vez                      |
|  3. Sair                               |
+========================================+

Escolha uma opcao: 2

[Tela Limpa - Resultado da Jogada]

+========================================+
|          RESULTADO DA JOGADA           |
+========================================+
|  Numero Sorteado: 50
|  Resultado: [VENCEU!]
+========================================+

  Pressione ENTER para continuar...

[Tela Limpa - Volta ao Menu Principal]
```

---

## 📈 Fluxo do Programa

```
┌──────────────────────────┐
│   INÍCIO DO PROGRAMA     │
│   (Limpa Tela)           │
└────────────┬─────────────┘
             │
             ▼
      ┌──────────────┐
      │  MENU LOOP   │ ◄─────────────────────┐
      │ (Limpa Tela) │                       │
      └──┬───────┬───┬──┘                    │
         │       │   │                       │
      1  │    2  │   │ 3                     │
         ▼       ▼   ▼                       │
      CONFIG   JOGAR SAIR                    │
        │        │     │                     │
        │        │     ▼                     │
        │        │   Encerra                 │
        │        │   (Libera Memória)        │
        │        │   Fim                     │
        │        │                           │
        ▼        ▼                           │
     [Limpa]  [Limpa]                        │
      Tela     Tela                          │
        │        │                           │
        │        ├─────────────────┤         │
        │                          │         │
        └──────────────────────────┼─────────┘
                                   │
                           [Pausa ENTER]
```
````

---

## 🔐 Gerenciamento de Memória

O projeto utiliza **alocação dinâmica** através de `malloc()` e `free()`:

- **Alocação**: Realizada em `configurarJogo()` quando o usuário define quantos números vencedores deseja
- **Liberação**: Realizada em `liberarConfig()` antes do programa encerrar

0**Evita vazamentos de memória** chamando `liberarConfig(&cfg)` na função `main()`.

---

## ⚠️ Validações Implementadas

✅ Números fora do intervalo são rejeitados
✅ Números duplicados não são permitidos
✅ Entradas inválidas (não-numéricas) são tratadas
✅ Verificação de alocação de memória
✅ Ponteiros nulos são validados
✅ Interface de erro quando jogo não configurado

---

## �️ Interface do Usuário

### Melhorias de UX

✅ **Limpeza automática de tela** - Cada ação limpa o terminal
✅ **Mensagens de status claras** - `[OK]`, `[ERRO]`, `[AVISO]`
✅ **Pausa com ENTER** - Usuário pode ler antes de continuar
✅ **Caracteres ASCII simples** - Compatível com todos os terminais Windows
✅ **Menu decorado** - Bordas ASCII `+` e `|` para melhor visualização

### Codificação de Caracteres

- Sem emojis Unicode (compatibilidade total)
- Sem caracteres especiais (funciona em PowerShell)
- Interface 100% limpa e profissional

---

## �📚 Tecnologias Utilizadas

- **Linguagem**: C (C99)
- **Compilador**: GCC (`-std=c11`)
- **Build System**: Makefile
- **IDE**: Visual Studio Code
- **Terminal**: Windows PowerShell

---

## 🐛 Correções Realizadas

| Versão | Correção |
|--------|----------|
| v1.0 | Estrutura base do projeto |
| v2.0 | Remoção de Unicode, caracteres ASCII simples |
| v3.0 | **Limpeza automática de tela** |
| v3.0 | **Pausa com ENTER entre ações** |
| v3.0 | **Mensagens de erro melhoradas** |
| v3.0 | **README.md atualizado** |

---

## 👥 Autores

**Garotos do JOB**

---

## 📄 Licença

Este projeto é fornecido como material educacional.

---

## 🎓 Conceitos Aprendidos

- ✅ Alocação e desalocação dinâmica de memória
- ✅ Estruturas (structs) em C
- ✅ Ponteiros e arrays dinâmicos
- ✅ Geração de números aleatórios
- ✅ Validação de entrada de usuário
- ✅ Modularização de código com headers
- ✅ Limpeza de buffer de entrada
- ✅ Limpeza e controle de terminal
- ✅ Interface de usuário em console
- ✅ Boas práticas de documentação

---

## 📝 Notas de Desenvolvimento

### Estrutura do Código

- **Separação clara** entre `funcoes.c` e `main.c`
- **Headers bem documentados** em `funcoes.h`
- **Comentários detalhados** em cada função
- **Tratamento de erros** em todas as entradas

### Compilação

O projeto foi testado com:
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c funcoes.c -o roleta.exe
```

Sem avisos ou erros! ✅
