# 🥩 Corrida dos Algoritmos — Casa de Carnes "Boi de Ouro"

Trabalho prático da disciplina de **Estrutura de Dados** — comparação de estratégias de ordenação implementadas em linguagem C, aplicadas a um sistema fictício de clientes de uma casa de carnes.

---

## 📋 Descrição do Projeto

Uma casa de carnes chamada **"Boi de Ouro"** possui uma base de dados de clientes desorganizada e precisa decidir qual algoritmo de ordenação utilizar para organizar seus registros por **total gasto**.

O programa implementa e compara três algoritmos clássicos de ordenação, contabilizando **comparações** e **trocas** em três cenários distintos, permitindo uma análise técnica de desempenho.

---

## 👥 Integrantes do Grupo

| Nome | Responsabilidade |
|------|-----------------|
| _Wesley Wiltuschnig_ | Bubble Sort + estrutura principal | Selection Sort + Insertion Sort |

---

## 🗂️ Estrutura do Repositório

```
corrida-dos-algoritmos/
│
├── corrida_algoritmos.c   # Código-fonte principal
└── README.md              # Este arquivo
```

---

## 🧱 Struct Utilizada

Os dados dos clientes são representados pela seguinte estrutura em C:

```c
typedef struct {
    int   codigo;        // Código único do cliente
    char  nome[50];      // Nome completo
    float totalGasto;    // Total gasto em reais (critério de ordenação)
    int   fidelidade;    // Pontos do programa de fidelidade
} Cliente;
```

O vetor de `Cliente` armazena **10 registros fictícios** de clientes da casa de carnes.

---

## ⚙️ Algoritmos Implementados

### 1. Bubble Sort

Percorre o vetor repetidamente, comparando pares adjacentes e trocando quando necessário.  
Inclui **otimização com flag**: se nenhuma troca ocorrer em uma passagem, o laço é interrompido antecipadamente — o que melhora significativamente o desempenho no cenário de dados já ordenados.

```c
void bubbleSort(Cliente v[], int n);
```

### 2. Selection Sort

A cada iteração, encontra o menor elemento da parte não-ordenada e o posiciona na posição correta. Realiza **no máximo n−1 trocas**, independente da ordem inicial — vantagem em contextos onde trocas físicas são custosas.

```c
void selectionSort(Cliente v[], int n);
```

### 3. Insertion Sort

Constrói o vetor ordenado elemento a elemento, inserindo cada novo item na posição correta entre os já ordenados. Excelente para listas **quasi-ordenadas** e tem complexidade **O(n)** no melhor caso.

```c
void insertionSort(Cliente v[], int n);
```

---

## 🧪 Cenários de Teste

| # | Cenário | Descrição |
|---|---------|-----------|
| 1 | **Aleatório** | Clientes em ordem misturada, sem padrão |
| 2 | **Já ordenado** | Clientes em ordem crescente de `totalGasto` |
| 3 | **Ordem inversa** | Clientes em ordem decrescente (pior caso) |

---

## 📊 Tabela Comparativa de Resultados

> Resultados obtidos com **n = 10 clientes**, ordenando pelo campo `totalGasto`.

### Comparações

| Algoritmo | Aleatório | Já Ordenado | Ordem Inversa |
|-----------|:---------:|:-----------:|:-------------:|
| Bubble Sort | 36 | 9 | 45 |
| Selection Sort | 45 | 45 | 45 |
| Insertion Sort | 24 | 9 | 45 |

### Trocas / Deslocamentos

| Algoritmo | Aleatório | Já Ordenado | Ordem Inversa |
|-----------|:---------:|:-----------:|:-------------:|
| Bubble Sort | 18 | 0 | 45 |
| Selection Sort | 7 | 0 | 9 |
| Insertion Sort | 21 | 0 | 45 |

> ✅ = menor valor no cenário (melhor desempenho)

---

## 📦 O Que Foi Entregue

| Entregável | Status |
|-----------|--------|
| Código-fonte em C (`corrida_algoritmos.c`) | ✅ |
| Struct `Cliente` com 4 campos | ✅ |
| Bubble Sort com contagem de comparações e trocas | ✅ |
| Selection Sort com contagem de comparações e trocas | ✅ |
| Insertion Sort com contagem de comparações e trocas | ✅ |
| 3 cenários de teste (aleatório, ordenado, inverso) | ✅ |
| Tabela comparativa de resultados | ✅ |
| Conclusão e justificativa técnica | ✅ |
| Repositório Git com commits separados por integrante | ✅ |

---

## 🏁 Como Compilar e Executar

Compile com `gcc` (ou qualquer compilador C padrão):

```bash
gcc corrida_algoritmos.c -o corrida
./corrida
```

Sem dependências externas — apenas a biblioteca padrão C (`stdio.h`, `string.h`, `stdlib.h`).

---

## 🧠 Conclusão Técnica

### Cenário: Dados Aleatórios
O **Insertion Sort** apresentou o menor número de comparações (24), sendo o mais eficiente para este cenário entre os três algoritmos. Bubble Sort e Selection Sort ficaram em 36 e 45 comparações, respectivamente.

### Cenário: Dados Já Ordenados
O **Insertion Sort** é o grande vencedor: realiza apenas **n−1 = 9 comparações** e **0 trocas**, aproveitando ao máximo a ordem preexistente. O Bubble Sort com flag de otimização também detecta rapidamente que o vetor está ordenado. O Selection Sort não aproveita a ordem e sempre executa O(n²) comparações — 45 neste caso.

### Cenário: Ordem Inversa (Pior Caso)
Todos os algoritmos atingem O(n²) comparações (45). A diferença está nas trocas: o **Selection Sort** realiza apenas **9 trocas** (no máximo n−1), enquanto Bubble Sort e Insertion Sort chegam a 45 deslocamentos. Em ambientes onde escrever na memória é custoso, o Selection Sort tem vantagem.

### Recomendação para a Casa de Carnes "Boi de Ouro"

> Para um sistema onde novos clientes são constantemente inseridos numa lista quasi-ordenada (situação mais realista), a recomendação é o **Insertion Sort**: ele é adaptativo, simples de implementar e eficiente no caso médio. Para listas que raramente mudam e onde a escrita é cara, o **Selection Sort** minimiza o número de trocas físicas.

---

## 📚 Referências

- SEDGEWICK, R.; WAYNE, K. *Algorithms*. 4. ed. Addison-Wesley, 2011.
- Notas de aula — Disciplina de Estrutura de Dados.
