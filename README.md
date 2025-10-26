# 🎰 Roleta Russa - Documentação Completa do Projeto

## 📋 Descrição Geral

**Roleta Russa** é um **jogo educacional de azar** desenvolvido em linguagem **C**, projetado como trabalho acadêmico para demonstrar conceitos fundamentais de programação.

### O que é o jogo?

O jogo permite que o usuário:
1. **Configure** um conjunto de números vencedores (0 a 100)
2. **Jogue uma vez** e tente ganhar ao acertar o número sorteado
3. **Veja o resultado** imediatamente na tela

### Mecânica Simples

```
┌──────────────────────────────────────┐
│      JOGADOR CONFIGURA NÚMEROS       │
│          (Ex: 10, 50, 90)            │
└────────────────┬─────────────────────┘
                 │
                 ▼
┌──────────────────────────────────────┐
│    SISTEMA SORTEIA NÚMERO (0-100)    │
└────────────────┬─────────────────────┘
                 │
                 ▼
┌──────────────────────────────────────┐
│   VERIFICA SE NÚMERO ESTÁ NA LISTA   │
└────────────────┬─────────────────────┘
                 │
        ┌────────┴────────┐
        ▼                 ▼
     GANHOU!           PERDEU!
```

### Características Principais

- ✅ **Interface limpa e intuitiva** com ASCII simples
- ✅ **Limpeza automática** de terminal após cada ação
- ✅ **Validação robusta** de entradas do usuário
- ✅ **Gerenciamento dinâmico** de memória
- ✅ **Sem bugs de codificação** - funciona perfeitamente em Windows
- ✅ **Código comentado** e bem organizado para aprendizado

---

## 🎯 Objetivos Educacionais

Este projeto foi desenvolvido com objetivo de **demonstrar e aplicar** os seguintes conceitos de programação:

### Conceitos Aplicados ✓

| Conceito | Como é Usado |
|----------|-------------|
| **Structs** | `GameConfig` agrupa dados relacionados do jogo |
| **Ponteiros** | Passagem de parâmetros por referência para modificação |
| **Alocação Dinâmica** | `malloc()` para array de números vencedores |
| **Desalocação Segura** | `free()` para evitar vazamento de memória |
| **Validação de Entrada** | Verificação de ranges e tipos de dados |
| **Arrays Dinâmicos** | Flexibilidade no tamanho da lista de vencedores |
| **Modularização** | Separação clara em múltiplos arquivos .c e .h |
| **Geração Aleatória** | `rand()` e `srand()` para sorteios |
| **Tratamento de Erros** | NULL checks, validações, mensagens de erro claras |

### Mecânica do Jogo

O objetivo é **ganhar** acertando no número sorteado:

1. **Intervalo**: Números de 0 a 100 (101 possibilidades)
2. **Configuração**: Usuário escolhe quais números vencem
3. **Sorteio**: Sistema escolhe aleatoriamente um número
4. **Resultado**: Verifica se número sorteado está na lista vencedora
5. **Probabilidade**: Com 5 números vencedores = ~4.95% de chance de ganhar

---

## 🏗️ Estrutura do Projeto

### Arquivos e Responsabilidades

```
roleta-russa/
├── structs.h          ← Define a estrutura de dados (GameConfig)
├── funcoes.h          ← Declara as funções (protótipos)
├── funcoes.c          ← Implementa as funções (lógica do jogo)
├── main.c             ← Programa principal (menu e orquestração)
├── README.md          ← Este arquivo (documentação do usuário)
├── docs.md            ← Documentação técnica detalhada
└── roleta.exe         ← Executável compilado
```

### Padrão de Arquivos

```
┌─────────────────────────────────────────────┐
│ structs.h                                   │
│ typedef struct GameConfig { ... }           │
└─────────┬───────────────────────────────────┘
          │ #include "structs.h"
          ▼
┌─────────────────────────────────────────────┐
│ funcoes.h                                   │
│ void configurarJogo(GameConfig *cfg);       │
│ int jogarUmaVez(const GameConfig *cfg);     │
└─────────┬───────────────────────────────────┘
          │ #include "funcoes.h"
          ▼
┌─────────────────────────────────────────────┐
│ main.c                                      │
│ int main() { ... }                          │
└─────────────────────────────────────────────┘
```

---

## 📊 Estrutura de Dados - GameConfig

### O que é?

`GameConfig` é uma **estrutura (struct)** que encapsula toda a configuração do jogo em um único objeto. Isso facilita a passagem de dados entre funções.

### Definição

```c
typedef struct GameConfig {
    int *listaVencedores;    // Ponteiro para array dinâmico
    int tamanhoLista;        // Quantidade de números na lista
    int intervaloMax;        // Número máximo (sempre 100)
} GameConfig;
```

### Explicação Visual

```
GameConfig (em memória)
┌──────────────────────────────────┐
│ listaVencedores ────→ [10, 50, 90]  │
│ tamanhoLista: 3                    │
│ intervaloMax: 100                  │
└──────────────────────────────────┘
```

### Por que usar struct?

**SEM struct (desorganizado):**
```c
// Espalhado em múltiplas variáveis
int *vencedores = NULL;
int tamanho = 0;
int maximo = 100;
float prob = 0.5;
// 😞 Difícil de gerenciar
```

**COM struct (organizado):**
```c
GameConfig cfg;  // Uma variável contém tudo
// 😊 Fácil de passar, armazenar e modificar
```

### Campos Explicados

| Campo | Tipo | Inicial | Descrição |
|-------|------|---------|-----------|
| `listaVencedores` | `int*` | NULL | Aponta para array alocado dinamicamente com os números que ganham |
| `tamanhoLista` | `int` | 0 | Quantos números estão na lista (de 1 a 101) |
| `intervaloMax` | `int` | 100 | Limite máximo do sorteio (fixo em 100) |

---

## 🔧 Funções Principais Explicadas

### 1️⃣ `void limparTela(void)` - Limpa o Terminal

**O que faz?**
Remove tudo que estava na tela e exibe novo conteúdo de forma limpa.

**Por quê?**
Sem limpeza, dados antigos ficariam visíveis, deixando a interface confusa.

**Quando é usada:**
- ✓ Antes de mostrar o menu
- ✓ Antes de configurar jogo
- ✓ Antes de mostrar resultado

---

### 2️⃣ `void mostrarMenu(void)` - Exibe o Menu

**O que faz?**
Mostra as opções disponíveis para o usuário.

**Fluxo:**
```
1. Chama limparTela()
2. Exibe o menu decorado
3. Espera usuário escolher
```

**Saída na tela:**
```
+========================================+
|   ROLETA RUSSA - Garotos do JOB       |
+========================================+
|  1. Configurar Jogo                    |
|  2. Jogar Uma Vez                      |
|  3. Sair                               |
+========================================+

Escolha uma opcao:
```

---

### 3️⃣ `void configurarJogo(GameConfig *cfg)` - Configura Números Vencedores

**O que faz?**
Permite o usuário definir quais números vencem no sorteio.

**Parâmetros:**
- `cfg`: Endereço da estrutura GameConfig (passagem por referência)

**Fluxo em detalhes:**

```
┌─────────────────────────────────────┐
│ 1. Limpa a tela                     │
└────────┬────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ 2. Lê quantidade de números         │
│    Pergunta: "Quantos números?"     │
└────────┬────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ 3. Aloca memória com malloc()        │
│    malloc(sizeof(int) * quantidade) │
└────────┬────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ 4. Loop de leitura com validações   │
│    - Lê cada número                 │
│    - Verifica se não repetem        │
│    - Verifica se está 0-100         │
└────────┬────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ 5. Salva configuração e aguarda     │
│    usuário pressionar ENTER         │
└─────────────────────────────────────┘
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

**Validações implementadas:**
- ✓ Verifica se `cfg` não é NULL
- ✓ Valida quantidade (mínimo 1, máximo 101)
- ✓ Aloca memória com verificação de erro
- ✓ Impede números duplicados
- ✓ Valida se número está entre 0-100

---

### 4️⃣ `int jogarUmaVez(const GameConfig *cfg, int *numeroSorteado)` - Executa Uma Rodada

**O que faz?**
Sorteia um número aleatório e verifica se é um número vencedor.

**Parâmetros:**
- `cfg`: Configuração do jogo (não será modificada, por isso `const`)
- `numeroSorteado`: Endereço para guardar qual número foi sorteado

**Retorno:**
- `1` = Usuário GANHOU ✓
- `0` = Usuário PERDEU ✗

**Lógica em passos:**

```
Passo 1: Sorteia número (0 a 100)
┌────────────────────────────┐
│ n = rand() % 101           │
│ Resultado: 0 a 100         │
└────────────┬───────────────┘
             │
             ▼
Passo 2: Armazena o número sorteado
┌────────────────────────────┐
│ *numeroSorteado = n        │
└────────────┬───────────────┘
             │
             ▼
Passo 3: Verifica na lista
┌────────────────────────────┐
│ Está na lista vencedora?   │
└────────────┬───────────────┘
        ┌────┴────┐
        ▼         ▼
      SIM        NÃO
       │          │
       ▼          ▼
    Retorna    Retorna
       1          0
```

**Exemplo prático:**

```
Config: números vencedores = [10, 50, 90]
Sorteio: número = 50

// Verifica: 50 está em [10, 50, 90]? SIM!
Retorna: 1 (GANHOU!)

---

Config: números vencedores = [10, 50, 90]
Sorteio: número = 37

// Verifica: 37 está em [10, 50, 90]? NÃO!
Retorna: 0 (PERDEU!)
```

**Probabilidade de Ganhar:**

Com **5 números vencedores** e **101 possibilidades**:

$$P(\text{Ganhar}) = \frac{5}{101} \approx 4.95\%$$

---

### 5️⃣ `bool estaNaListaVencedora()` - Verifica Número

**O que faz?**
Procura um número no array de vencedores.

**Retorno:**
- `true` (1): Número encontrado ✓
- `false` (0): Número não encontrado ✗

---

### 6️⃣ `void liberarConfig()` - Libera Memória

**O que faz?**
Devolve ao sistema a memória que foi alocada com `malloc()`.

**Por quê?**
Se não fizer isso, a memória fica "perdida" (vazamento de memória).

**Visualização:**

```
ANTES DE liberarConfig():
Memória ┌──────────┐
Heap    │ 10,50,90 │  ← Perdido na memória!
        └──────────┘

DEPOIS DE liberarConfig():
Memória ┌──────────┐
Heap    │ (livre)  │  ← Devolvido ao SO
        └──────────┘
```

---

### 7️⃣ `int lerInteiro()` - Lê Inteiro com Validação

**O que faz?**
Lê um número inteiro do usuário **com validações**.

**Validações:**
- ✓ Verifica se entrada é realmente um número
- ✓ Verifica se está dentro do intervalo [min, max]
- ✓ Pede novamente se algo estiver errado

**Comportamento:**

```
Usuário digita: "abc"
Sistema: [ERRO] Entrada invalida!
Repete...

Usuário digita: "200"
Sistema: [ERRO] Digite entre 1 e 100!
Repete...

Usuário digita: "5"
Sistema: ✓ Aceita e continua
```

---

## 🎮 Como Usar - Passo a Passo
---

### Passo 1: Execução

```powershell
.\roleta.exe
```

Você verá o menu inicial.

---

### Passo 2: Usando o Menu

**Opção 1 - Configurar Jogo:**

```
+========================================+
|   ROLETA RUSSA - Garotos do JOB       |
+========================================+
|  1. Configurar Jogo                    |
|  2. Jogar Uma Vez                      |
|  3. Sair                               |
+========================================+

Escolha uma opcao: 1

[Tela limpa automaticamente]

+========================================+
|       CONFIGURE O JOGO                |
+========================================+
  - Intervalo: 0 a 100

  Quantos numeros vencedores deseja? (1-101): 3

  Digite os 3 numeros vencedores (sem repeticoes):

  Numero 1: 25
  Numero 2: 50
  Numero 3: 90

  [OK] Configuracao salva com sucesso!

  Pressione ENTER para continuar...
```

**Opção 2 - Jogar Uma Vez:**

```
Escolha uma opcao: 2

[Tela limpa]

+========================================+
|          RESULTADO DA JOGADA           |
+========================================+
|  Numero Sorteado: 50
|  Resultado: [VENCEU!]
+========================================+

  Pressione ENTER para continuar...
```

**Opção 3 - Sair:**

```
Escolha uma opcao: 3

Programa encerra com segurança
Memória é liberada automaticamente
```

---

## 📈 Fluxo Completo do Programa

```
INÍCIO
  │
  ├─ Inicializa srand() com time()
  ├─ Cria GameConfig vazio
  │
  ▼
┌─────────────────────────┐
│   EXIBE MENU PRINCIPAL  │
└────────────┬────────────┘
             │
    ┌────────┼────────┐
    │        │        │
    1        2        3
    │        │        │
    ▼        ▼        ▼
 CONFIG   JOGAR     SAIR
   │        │        │
   ▼        ▼        ▼
 Lê e     Verifica  Libera
 aloca    se jogou  memória
   │        │       Fim
   │        ▼
   └─────► Volta
          ao menu
```

---

## 🔐 Segurança de Memória

### O Problema

Quando usamos `malloc()` para alocar memória, devemos **sempre liberar** com `free()`, senão temos um **vazamento de memória**.

### Nossa Solução

No `main.c`, chamamos `liberarConfig(&cfg)` **sempre** antes de sair:

---

## ⚠️ Validações Implementadas

Nosso programa é **robusto** e valida tudo:

| Validação | Exemplo |
|-----------|---------|
| Entrada não-numérica | Digita "abc" → Rejeita |
| Número fora do intervalo | Digita 150 → Rejeita (máx: 100) |
| Número duplicado | Digita 50 duas vezes → Avisa |
| Jogar sem configurar | Escolhe opção 2 sem ter configurado → Erro |
| malloc falha | Memória insuficiente → Erro controlado |
| Ponteiro NULL | Proteção em todas as funções |

---

## 🎯 Pontos Fortes do Projeto

✅ **Código Modularizado** - Separado em múltiplos arquivos  
✅ **Bem Comentado** - Fácil entender o que faz cada parte  
✅ **Sem Bugs de Terminal** - Funciona perfeitamente em Windows  
✅ **Interface Limpa** - ASCII simples, sem caracteres estranhos  
✅ **Memória Segura** - Sem vazamentos com liberarConfig()  
✅ **Validações Completas** - Trata todos os erros  
✅ **Pronto para Apresentação** - Código profissional e documentado

---

## 📚 Tecnologias Utilizadas

- **Linguagem**: C
- **Compilador**: GCC
- **IDE**: Dev C++
- **Terminal**: Windows PowerShell

## 👥 Autores

**Garotos do JOB**  
Trabalho Acadêmico - Algoritmos e Programação em C

---

## 💡 Como Usar Este Projeto para Aprender

1. **Leia `structs.h`** - Entenda as estruturas de dados
2. **Leia `funcoes.h`** - Veja os protótipos
3. **Leia `funcoes.c`** - Estude a implementação linha a linha
4. **Leia `main.c`** - Veja como tudo se conecta
5. **Consulte `docs.md`** - Para detalhes técnicos profundos

---

## 📄 Licença

Este projeto é fornecido como material educacional para fins de aprendizado.

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

✅ **Sem avisos!** ✅ **Sem erros!** ✅ **Totalmente compatível com Windows!**

### Estrutura do Código

- **Separação clara** entre `funcoes.c` e `main.c`
- **Headers bem documentados** em `funcoes.h`
- **Comentários detalhados** em cada função
- **Tratamento de erros** em todas as entradas
- **Nomes descritivos** de variáveis e funções

**Última atualização:** 26 de outubro de 2025  
**Status:** ✅ Pronto para apresentação
