#include <stdio.h>
#include <stdlib.h>
#include "sistlinear.h"
#include "matriz.h"

/* troca todos os elementos entre os vetores de tamanho igual a n */
void _troca_vetores(int n, double *u, double *v)
{
    double t;
    for (int i = 0; i < n; i++)
    {
        t = u[i];
        u[i] = v[i];
        v[i] = t;
    }
    return;
}

/* troca os elementos i e j do vetor v*/
void _troca_elementos(int *v, int i, int j)
{
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
    return;
}

void _print_matriz(const char *nome, int n, double **A)
{
    printf("Matriz %s [%d]:\n", nome, n);
    for (int l = 0; l < n; l++)
    {
        printf("%d: ", l);
        for (int c = 0; c < n; c++)
        {
            printf("%0.3f ", A[l][c]);
        }
        printf("\n");
    }
}

void _print_vetor(const char *nome, int n, double *V)
{
    printf("Vetor %s: ", nome);
    for (int i = 0; i < n; i++)
    {
        printf("%0.3f ", V[i]);
    }
    printf("\n");
}

void _print_vetor_int(const char *nome, int n, int *V)
{
    printf("Vetor %s: ", nome);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", V[i]);
    }
    printf("\n");
}

/*
    Funcao para fazer a fatoração A = LU

    L e U serão escritas devolta na matriz A, sobreescrevendo os seus elementos.
    O vetor de permutação p (dimensao n, já alocado) será preenchido.

    Params:
        int n: dimensao da matriz e do vetor
        double **A: matriz quadrada n x n
        int *p: vetor de permutação
 */
void fatoracao(int n, double **A, int *p)
{
    int coluna;
    int linha;
    int pivot;
    int k;
    double fator_eliminacao;
    for (coluna = 0; coluna < n - 1; coluna++)
    {
        // antes da eliminacao de uma coluna, fazer o pivoteamento
        pivot = coluna;
        for (k = coluna + 1; k < n; k++)
        {
            if (A[k][coluna] > A[pivot][coluna])
            {
                pivot = k;
            }
        }
        // trocando as linhas j e p
        _troca_vetores(n, A[coluna], A[pivot]);
        // salva no vetor p
        _troca_elementos(p, coluna, pivot);

        // eliminacao
        for (linha = coluna + 1; linha < n; linha++)
        {
            if (A[coluna][coluna] == 0)
            {
                printf("0 ou infinitas soluções detectada na fatoracao\n");
                return;
            }
            fator_eliminacao = A[linha][coluna] / A[coluna][coluna];
            // salva o fator de eliminacao
            A[linha][coluna] = fator_eliminacao;
            // diminui o resto
            for (k = coluna + 1; k < n; k++)
            {
                A[linha][k] -= A[coluna][k] * fator_eliminacao;
            }
        }
    }
    // _print_vetor_int("p", n, p);
    // _print_matriz("fatoracao", n, A);
    return;
}

/*
    Função que recebe a LU, o vetor de permutação e o vetor independente, e preenche
    o vetor de solucao x.

    Params:
        int n: dimensao da matriz LU e p
        double **A: matriz LU
        int *p: vetor de permutação
        double *b: vetor independente
        double *x: vetor solucao (ja alocado) 
 */
void substituicao(int n, double **A, int *p, double *b, double *x)
{
    int coluna, linha;
    double base;
    double *y = criavet(n);

    // achando y
    for (linha = 0; linha < n; linha++)
    {
        base = 0;
        for (coluna = 0; coluna < linha; coluna++)
            base += A[linha][coluna] * y[coluna];
        y[linha] = b[p[linha]] - base;
    }

    // printf("vetor b': ");
    // for (int iii = 0; iii < n; iii++)
    // {
    //     printf("%f ", b[p[iii]]);
    // }
    // printf("\n");

    // _print_vetor("y", n, y);

    // achando x
    for (linha = n - 1; linha >= 0; linha--)
    {
        if (A[linha][linha] == 0)
        {
            printf("0 ou infinitas soluções detectada na substituicao\n");
            return;
        }

        base = 0;
        for (coluna = n - 1; coluna > linha; coluna--)
            base += A[linha][coluna] * x[coluna];
        x[linha] = (y[linha] - base) / A[linha][linha];
    }

    free(y);
    // _print_vetor("x", n, x);

    return;
}

/*
    Funcao que resolve um sistema linear.
    Utiliza 'fatoracao' e 'substituicao'

    Params:
        int n: dimensao da matriz A
        double **A: matriz A para resolver
        double *b: vetor independente b
        double *x: vetor de solucao (ja alocado)
 */
void gauss(int n, double **A, double *b, double *x)
{
    int *p = (int *)malloc(sizeof(int) * n);
    if (p == NULL)
    {
        printf("Erro na alocacao do vetor p\n");
        exit(-1);
    }
    for (int i = 0; i < n; i++)
        p[i] = i;
    fatoracao(n, A, p);
    substituicao(n, A, p, b, x);
    free(p);
    return;
}