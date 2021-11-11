/*
    Feito por Daniel Guimaraes - 1910462
*/

#include <stdio.h>
#include <stdlib.h>

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
