/*
    Feito por Daniel Guimaraes - 1910462
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

/* Questao 1 */
double *criavet(int n)
{
    double *vet = (double *)malloc(sizeof(double) * n);
    if (vet == NULL)
    {
        printf("Erro de memoria na criacao do vetor!\n");
        exit(-1);
    }
    return vet;
}

/* Questao 2 */
void liberavet(double *v)
{
    free(v);
    return;
}

/* Questao 3 */
double escalar(int n, const double *v, const double *w)
{
    double ret = 0;
    for (int i = 0; i < n; i++)
    {
        ret += v[i] * w[i];
    }
    return ret;
}

/* Questao 4 */
double norma2(int n, const double *v)
{
    double ret = escalar(n, v, v);
    return sqrt(ret);
}

/* Questao 5 */
void multvs(int n, const double *v, double s, double *w)
{
    for (int i = 0; i < n; i++)
    {
        w[i] = v[i] * s;
    }
    return;
}

/* Questao 6 */
double **criamat(int m, int n)
{
    double **ret = (double **)malloc(sizeof(double *) * m);
    if (ret == NULL)
    {
        printf("Erro de memoria na criacao da matriz!\n");
        exit(-2);
    }
    for (int i = 0; i < m; i++)
    {
        ret[i] = criavet(n);
    }
    return ret;
}

/* Questao 7 */
double **criamattri(int n)
{
    double **ret = (double **)malloc(sizeof(double *) * n);
    if (ret == NULL)
    {
        printf("Erro de memoria na criacao da matriz retangular!\n");
        exit(-3);
    }
    for (int i = 0; i < n; i++)
    {
        ret[i] = criavet(i + 1);
    }
    return ret;
}

/* Questao 8 */
void liberamat(int m, double **A)
{
    for (; m > 0; m--)
    {
        free(A[m - 1]);
    }
    free(A);
    return;
}

/* Questao 9*/
void transposta(int m, int n, const double **A, double **T)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            T[j][i] = A[i][j];
        }
    }
    return;
}

/* Questao 10 */
void multmv(int m, int n, const double **A, const double *v, double *w)
{
    for (int i = 0; i < m; i++)
    {
        w[i] = escalar(n, A[i], v);
    }
    return;
}

/* Questao 11 */
void multmm(int m, int n, int q, const double **A, const double **B, double **C)
{
    double temp;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            temp = 0;
            for (int k = 0; k < n; k++)
            {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
    return;
}