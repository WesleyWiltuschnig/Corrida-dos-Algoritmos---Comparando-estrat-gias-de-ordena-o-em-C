#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CLIENTES 10

// Cliente
typedef struct {
    int    codigo;
    char   nome[50];
    float  totalGasto; 
    int    fidelidade;   // pontos de fidelidade d clente
} Cliente;

long long comparacoes; //long long - 64 bits
long long trocas;

void copiarCliente(Cliente *dest, const Cliente *src) {
    dest->codigo     = src->codigo;
    dest->fidelidade = src->fidelidade;
    dest->totalGasto = src->totalGasto;
    strcpy(dest->nome, src->nome);
}

void trocarClientes(Cliente *a, Cliente *b) {
    Cliente temp;
    copiarCliente(&temp, a);
    copiarCliente(a, b);
    copiarCliente(b, &temp);
    trocas++;
}

void imprimirClientes(Cliente v[], int n) {
    printf("  %-4s  %-22s  %-12s  %-10s\n",
           "COD", "NOME", "TOTAL GASTO", "FIDELIDADE");
    printf("  %s\n", "-------------------------------------------------------");
    for (int i = 0; i < n; i++) {
        printf("  %-4d  %-22s  R$ %8.2f  %6d pts\n",
               v[i].codigo, v[i].nome,
               v[i].totalGasto, v[i].fidelidade);
    }
    printf("\n");
}

void copiarVetor(Cliente dest[], const Cliente src[], int n) {
    for (int i = 0; i < n; i++)
        copiarCliente(&dest[i], &src[i]);
}

void zerarContadores(void) {
    comparacoes = 0;
    trocas      = 0;
}

// bubble sort
void bubbleSort(Cliente v[], int n) {
    zerarContadores();
    for (int i = 0; i < n - 1; i++) {
        int trocouNaPassagem = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (v[j].totalGasto > v[j + 1].totalGasto) {
                trocarClientes(&v[j], &v[j + 1]);
                trocouNaPassagem = 1;
            }
        }
        if (!trocouNaPassagem) break;
    }
}

// selection sort
void selectionSort(Cliente v[], int n) {
    zerarContadores();
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].totalGasto < v[indiceMenor].totalGasto)
                indiceMenor = j;
        }
        if (indiceMenor != i)
            trocarClientes(&v[i], &v[indiceMenor]);
    }
}

// insertion sort
void insertionSort(Cliente v[], int n) {
    zerarContadores();
    for (int i = 1; i < n; i++) {
        Cliente chave;
        copiarCliente(&chave, &v[i]);
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (v[j].totalGasto > chave.totalGasto) {
                copiarCliente(&v[j + 1], &v[j]);
                trocas++; /* deslocamento conta como troca */
                j--;
            } else {
                break;
            }
        }
        copiarCliente(&v[j + 1], &chave);
    }
}

void carregarClientesAleatorios(Cliente v[], int n) {
    Cliente base[MAX_CLIENTES] = {
        {1001, "Carlos Mendonca",    450.75f, 220},
        {1002, "Fernanda Lima",      890.00f, 445},
        {1003, "Roberto Silva",      120.50f,  60},
        {1004, "Ana Paula Rocha",   1350.20f, 675},
        {1005, "Joao Batista",       670.00f, 335},
        {1006, "Marcia Teixeira",    230.80f, 115},
        {1007, "Pedro Alves",       1100.00f, 550},
        {1008, "Lucia Ferreira",     780.40f, 390},
        {1009, "Gilberto Costa",     340.60f, 170},
        {1010, "Tatiane Moura",      560.90f, 280}
    };
    copiarVetor(v, base, n);
}

void carregarClientesOrdenados(Cliente v[], int n) {
    Cliente base[MAX_CLIENTES] = {
        {1003, "Roberto Silva",      120.50f,  60},
        {1006, "Marcia Teixeira",    230.80f, 115},
        {1009, "Gilberto Costa",     340.60f, 170},
        {1001, "Carlos Mendonca",    450.75f, 220},
        {1010, "Tatiane Moura",      560.90f, 280},
        {1005, "Joao Batista",       670.00f, 335},
        {1008, "Lucia Ferreira",     780.40f, 390},
        {1002, "Fernanda Lima",      890.00f, 445},
        {1007, "Pedro Alves",       1100.00f, 550},
        {1004, "Ana Paula Rocha",   1350.20f, 675}
    };
    copiarVetor(v, base, n);
}

void carregarClientesInverso(Cliente v[], int n) {
    Cliente base[MAX_CLIENTES] = {
        {1004, "Ana Paula Rocha",   1350.20f, 675},
        {1007, "Pedro Alves",       1100.00f, 550},
        {1002, "Fernanda Lima",      890.00f, 445},
        {1008, "Lucia Ferreira",     780.40f, 390},
        {1005, "Joao Batista",       670.00f, 335},
        {1010, "Tatiane Moura",      560.90f, 280},
        {1001, "Carlos Mendonca",    450.75f, 220},
        {1009, "Gilberto Costa",     340.60f, 170},
        {1006, "Marcia Teixeira",    230.80f, 115},
        {1003, "Roberto Silva",      120.50f,  60}
    };
    copiarVetor(v, base, n);
}


// executando um algoritimo + resultados
typedef void (*FuncOrdenacao)(Cliente[], int);

void executarAlgoritmo(const char *nome, FuncOrdenacao func,
                       const Cliente original[], int n,
                       long long *outComp, long long *outTrocas) {
    Cliente copia[MAX_CLIENTES];
    copiarVetor(copia, original, n);

    printf("  >> Antes da ordenacao:\n");
    imprimirClientes(copia, n);

    func(copia, n);

    printf("  >> Depois da ordenacao (%s):\n", nome);
    imprimirClientes(copia, n);

    printf("  Comparacoes: %lld | Trocas/Deslocamentos: %lld\n\n",
           comparacoes, trocas);

    *outComp   = comparacoes;
    *outTrocas = trocas;
}

/* ============================================================
  TABELA COMPARATIVA
 ============================================================ 
void exibirTabelaComparativa(
    long long comp[3][3],   // [algoritmo][cenario] 
    long long swap[3][3])
{
    const char *algos[]    = {"Bubble Sort   ", "Selection Sort", "Insertion Sort"};
    const char *cenarios[] = {"Aleatorio", "Ordenado", "Inverso  "};

    printf("\n");
    printf("  +-----------------+-----------------------------+-----------------------------+\n");
    printf("  |                 |       COMPARACOES           |    TROCAS/DESLOCAMENTOS     |\n");
    printf("  |  ALGORITMO      +-----------+---------+-------+-----------+---------+-------+\n");
    printf("  |                 | Aleatorio | Ordenado| Inver.| Aleatorio | Ordenado| Inver.|\n");
    printf("  +-----------------+-----------+---------+-------+-----------+---------+-------+\n");

    for (int a = 0; a < 3; a++) {
        printf("  | %-15s | %9lld | %7lld | %5lld | %9lld | %7lld | %5lld |\n",
               algos[a],
               comp[a][0], comp[a][1], comp[a][2],
               swap[a][0], swap[a][1], swap[a][2]);
    }

    printf("  +-----------------+-----------+---------+-------+-----------+---------+-------+\n\n");
}
*/
int main(void) {

    /* Armazena os resultados: [algoritmo 0-2][cenario 0-2] */
    long long comp[3][3];
    long long swap[3][3];

    Cliente base[MAX_CLIENTES];
    int n = MAX_CLIENTES;

    printf("\n");
    printf("   Corrida dos Algoritmos - Ordenacao de Clientes    \n\n");

    printf("   CENARIO 1: DADOS EM ORDEM ALEATORIA               \n\n");

    carregarClientesAleatorios(base, n);

    printf("  BUBBLE SORT\n");
    executarAlgoritmo("Bubble Sort",    bubbleSort,    base, n, &comp[0][0], &swap[0][0]);

    printf("  SELECTION SORT\n");
    executarAlgoritmo("Selection Sort", selectionSort, base, n, &comp[1][0], &swap[1][0]);

    printf("  INSERTION SORT\n");
    executarAlgoritmo("Insertion Sort", insertionSort, base, n, &comp[2][0], &swap[2][0]);

    printf("   CENARIO 2: DADOS JA ORDENADOS                     \n\n");

    carregarClientesOrdenados(base, n);

    printf("  BUBBLE SORT\n");
    executarAlgoritmo("Bubble Sort",    bubbleSort,    base, n, &comp[0][1], &swap[0][1]);

    printf("  SELECTION SORT\n");
    executarAlgoritmo("Selection Sort", selectionSort, base, n, &comp[1][1], &swap[1][1]);

    printf("  INSERTION SORT\n");
    executarAlgoritmo("Insertion Sort", insertionSort, base, n, &comp[2][1], &swap[2][1]);

    printf("   CENARIO 3: DADOS EM ORDEM INVERSA (PIOR CASO)     \n\n");

    carregarClientesInverso(base, n);

    printf("  BUBBLE SORT\n");
    executarAlgoritmo("Bubble Sort",    bubbleSort,    base, n, &comp[0][2], &swap[0][2]);

    printf("  SELECTION SORT\n");
    executarAlgoritmo("Selection Sort", selectionSort, base, n, &comp[1][2], &swap[1][2]);

    printf("  INSERTION SORT\n");
    executarAlgoritmo("Insertion Sort", insertionSort, base, n, &comp[2][2], &swap[2][2]);

    printf("   TABELA COMPARATIVA - RESUMO DOS RESULTADOS        \n\n");
    exibirTabelaComparativa(comp, swap);

    printf("  =====================================================\n\n");
    printf("   CONCLUSAO \n\n");

    printf("  CENARIO ALEATORIO:\n");
    printf("    Insertion Sort tende a ser o mais eficiente em dados\n");
    printf("    parcialmente ordenados. Bubble e Selection apresentam\n");
    printf("    desempenho similar em n pequeno.\n\n");

    printf("  CENARIO JA ORDENADO:\n");
    printf("    Insertion Sort e EXCELENTE: faz apenas (n-1) comparacoes\n");
    printf("    e zero trocas. Bubble Sort (com otimizacao de flag) tambem\n");
    printf("    detecta o vetor ordenado rapidamente. Selection Sort nao\n");
    printf("    aproveita a ordem e sempre faz O(n^2) comparacoes.\n\n");

    printf("  CENARIO INVERSO (pior caso):\n");
    printf("    Todos os algoritmos atingem O(n^2). Bubble Sort realiza\n");
    printf("    o maior numero de trocas (move cada elemento passo a passo).\n");
    printf("    Selection Sort faz poucas trocas (no maximo n-1), mas muitas\n");
    printf("    comparacoes. Insertion Sort desloca muito, mas e previsivel.\n\n");

    printf("  RECOMENDACAO PARA A CASA DE CARNES \"BOI DE OURO\":\n");
    printf("    Para atualizacoes frequentes com insercao de novos clientes\n");
    printf("    numa lista quasi-ordenada: use INSERTION SORT.\n");
    printf("    Para listas que raramente mudam: SELECTION SORT minimiza\n");
    printf("    trocas fisicas, poupando escrita em disco.\n\n");

    printf("  =====================================================\n\n");

    return 0;
}
