#include "matriz.h"
#include "sistlinear.h"
#include "mmq.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* funcao retirada de sistlinear.c */
void _print_matriz(const char *nome, int m, int n, double **A)
{
    printf("Matriz %s [%d x %d]:\n", nome, m, n);
    for (int l = 0; l < m; l++)
    {
        printf("%d: ", l);
        for (int c = 0; c < n; c++)
        {
            printf("%0.3f ", A[l][c]);
        }
        printf("\n");
    }
}

/* funcao retirada de sistlinear.c */
void _print_vetor(const char *nome, int n, double *V)
{
    printf("Vetor %s: ", nome);
    for (int i = 0; i < n; i++)
    {
        printf("%0.3f ", V[i]);
    }
    printf("\n");
}

/* 
    Função que calcula a norma-2 do residuo
 */
double mmq_norma2(int m, int n, double **A, double *b, double *x)
{
    // encontrando Ax
    double *Ax = criavet(m);
    multmv(m, n, (const double **)A, x, Ax);

    // encotrando r
    double *r = criavet(m);
    for (int i = 0; i < m; i++)
    {
        r[i] = b[i] - Ax[i];
    }

    // encontrando a norma2
    double e = norma2(m, r);
    liberavet(r);
    liberavet(Ax);
    return e;
}

/*
    Função que resolve o sistema
    A[m x n] x[n] = b[m]
    Cria e retorna o vetor que representa a solução aproximada.
 */
double *mmq(int m, int n, double **A, double *b)
{
    // encontrando a matriz transposta
    double **At = criamat(n, m);
    transposta(m, n, (const double **)A, At);
    // _print_matriz("At", n, m, At);

    // encontrando At * A
    double **AtA = criamat(n, n);
    multmm(n, m, n, (const double **)At, (const double **)A, AtA);
    // _print_matriz("AtA", 2, 2, AtA);

    // encontrando At * b
    double *Atb = criavet(n);
    multmv(n, m, (const double **)At, b, Atb);
    // _print_vetor("Atb", n, Atb);

    // encontrando a resposta aproximada
    double *x = criavet(n);
    gauss(n, AtA, Atb, x);

    liberamat(n, At);
    liberamat(n, AtA);
    liberavet(Atb);
    return x;
}

/*
    Funcao que recebe um conjunto de medicoes (t[i], c[i]) e calcula
    os coeficientes a e b, preenchendo seus valores nos enderecos de memoria recebidos como parâmetros.

    Modelo: c = a * t * e^(bt)
    Linearizacao: 
        ln(c) = ln(a) + ln(t) + bt
        bt + k = (ln(c) - ln(t)) onde k = ln(a)
    
    ou seja, a funcao recebe conjunto de pontos (x:=t, y:=ln(c/t))
    e calcula os valores de a:=e^k e b
 */
void ajuste(int n, double *t, double *c, double *a, double *b)
{

    /*
    criando uma matriz A modelada por:
        |x[0]| 1|
        |x[1]| 1|
        |x[2]| 1|
    onde x[i] = t[i]
    */
    int i;
    double **A = criamat(n, 2);
    for (i = 0; i < n; i++)
    {
        A[i][0] = t[i];
        A[i][1] = 1;
    }

    // criando o vetor independente contendo os valores de y:=ln(c/t)
    double *vet = criavet(n);
    for (i = 0; i < n; i++)
    {
        if (t[i] == 0)
        {
            printf("Impossível de linearizar? t[%d] = 0\n", i);
            exit(-1);
        }
        vet[i] = log(c[i] / t[i]);
    }

    // criando o vetor resposta contendo a:=e^k e b
    double *ret = mmq(n, 2, A, vet);
    *a = exp(ret[1]);
    *b = ret[0];
    return;
}