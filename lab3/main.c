#include <stdio.h>
#include <stdlib.h>

#include "sistlinear.h"
#include "matriz.h"

void print_matriz(int n, double **A)
{
    printf("Matriz: \n");
    for (int linha = 0; linha < n; linha++)
    {
        printf("%d: ", linha);
        for (int coluna = 0; coluna < n; coluna++)
        {
            printf("%0.2f  ", A[linha][coluna]);
        }
        printf("\n");
    }
    printf("\n");
}

void teste_fatoracao()
{
    double **v = criamat(3, 3);
    v[0][0] = 1;
    v[0][1] = 2;
    v[0][2] = -1;
    v[1][0] = 2;
    v[1][1] = 1;
    v[1][2] = -2;
    v[2][0] = -3;
    v[2][1] = 1;
    v[2][2] = 1;

    int p[] = {0, 1, 2};

    printf("Fatorando...\n");
    fatoracao(3, v, p);
    printf("Fatorado\n");

    print_matriz(3, v);

    printf("vetor: %d | %d | %d\n", p[0], p[1], p[2]);

    liberamat(3, v);
    return;
}

void teste_1()
{
    double **v = criamat(3, 3);
    v[0][0] = 1;
    v[0][1] = 2;
    v[0][2] = -1;
    v[1][0] = 2;
    v[1][1] = 1;
    v[1][2] = -2;
    v[2][0] = -3;
    v[2][1] = 1;
    v[2][2] = 1;

    double b[3] = {3.0, 3.0, -6.0};
    double x[3];

    gauss(3, v, b, x);

    printf("====\nteste 1 (primeiro exemplo do enunciado)\n");
    printf("vetor resposta da 1: [");
    for (int i = 0; i < 3; i++)
    {
        printf("%f ", x[i]);
    }
    printf("]\n");
    liberamat(3, v);
}

void teste_2()
{
    double **v = criamat(6, 6);
    v[0][0] = 3;
    v[0][1] = -1;
    v[0][2] = 0;
    v[0][3] = 0;
    v[0][4] = 0;
    v[0][5] = 0.5;

    v[1][0] = -1;
    v[1][1] = 3;
    v[1][2] = -1;
    v[1][3] = 0;
    v[1][4] = 0.5;
    v[1][5] = 0;

    v[2][0] = 0;
    v[2][1] = -1;
    v[2][2] = 3;
    v[2][3] = -1;
    v[2][4] = 0;
    v[2][5] = 0;

    v[3][0] = 0;
    v[3][1] = 0;
    v[3][2] = -1;
    v[3][3] = 3;
    v[3][4] = -1;
    v[3][5] = 0;

    v[4][0] = 0;
    v[4][1] = 0.5;
    v[4][2] = 0;
    v[4][3] = -1;
    v[4][4] = 3;
    v[4][5] = -1;

    v[5][0] = 0.5;
    v[5][1] = 0;
    v[5][2] = 0;
    v[5][3] = 0;
    v[5][4] = -1;
    v[5][5] = 3;

    double b[6] = {2.5, 1.5, 1.0, 1.0, 1.5, 2.5};
    double x[6];

    gauss(6, v, b, x);

    printf("====\nteste 2 (segundo exemplo do enunciado)\n");
    printf("vetor resposta da 2: [");
    for (int i = 0; i < 6; i++)
    {
        printf("%f ", x[i]);
    }
    printf("]\n");
    liberamat(6, v);
}

void teste_3()
{
    double **v = criamat(2, 2);
    v[0][0] = 1;
    v[0][1] = 1;
    v[1][0] = 1;
    v[1][1] = 1;

    double **vv = criamat(2, 2);
    vv[0][0] = 1;
    vv[0][1] = 1;
    vv[1][0] = 1;
    vv[1][1] = 1;

    double **vvv = criamat(3, 3);
    vvv[0][0] = 1;
    vvv[0][1] = 1;
    vvv[0][2] = 1;
    vvv[1][0] = 1;
    vvv[1][1] = 1;
    vvv[1][2] = 1;
    vvv[2][0] = 1;
    vvv[2][1] = 2;
    vvv[2][2] = 3;

    double b[2] = {1, 1};
    double b2[2] = {1, 2};
    double b3[3] = {1, 2, 3};
    double x[2];
    double x3[3];

    printf("====\nteste 3 (testando sistemas sem solucao)\n");
    printf("as tres proximas execucoes devem dar erro:\n");
    gauss(2, v, b, x);
    gauss(2, vv, b2, x);
    gauss(3, vvv, b3, x3);

    liberamat(2, v);
}

void teste_4()
{
    double **v = criamat(2, 2);
    v[0][0] = 1;
    v[0][1] = 1;
    v[1][0] = 1;
    v[1][1] = -1;

    double b[2] = {2, 0};
    double x[2];
    gauss(2, v, b, x);

    printf("====\nteste 4 (testando matriz 2x2)\n");
    printf("vetor x do teste 4: ");
    for (int i = 0; i < 2; i++)
    {
        printf("%f ", x[i]);
    }
    printf("\n");
    liberamat(2, v);
    return;
}

int main()
{
    teste_1();
    teste_2();
    teste_3();
    teste_4();
    return 0;
}