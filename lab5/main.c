#include "mmq.h"
#include "matriz.h"

#include <stdio.h>

void teste_mmq_simples()
{
    double **A = criamat(3, 2);
    A[0][0] = 1.0;
    A[0][1] = 1.0;
    A[1][0] = 1.0;
    A[1][1] = -1.0;
    A[2][0] = 1.0;
    A[2][1] = 1.0;

    double *b = criavet(3);
    b[0] = 2;
    b[1] = 1;
    b[2] = 3;

    double *x = mmq(3, 2, A, b);
    printf("x0 = %0.2f, x1 = %0.2f\n", x[0], x[1]);
    double e = mmq_norma2(3, 2, A, b, x);
    printf("erro pela norma2: %0.3f\n", e);
    return;
}

void teste_2_a_a()
{
    double **A = criamat(4, 3);
    A[0][0] = 0.0;
    A[0][1] = 0.0;
    A[0][2] = 1.0;

    A[1][0] = 1.0;
    A[1][1] = 1.0;
    A[1][2] = 1.0;

    A[2][0] = 4.0;
    A[2][1] = 2.0;
    A[2][2] = 1.0;

    A[3][0] = 25.0;
    A[3][1] = 5.0;
    A[3][2] = 1.0;

    double *b = criavet(4);
    b[0] = 0.0;
    b[1] = 3.0;
    b[2] = 3.0;
    b[3] = 6.0;

    double *x = mmq(4, 3, A, b);
    double e = mmq_norma2(4, 3, A, b, x);
    printf("Questao 2a (a)\n");
    printf("Vetor x = [%0.5f, %0.5f, %0.5f]\n", x[0], x[1], x[2]);
    printf("erro pela norma2: %0.5f\n", e);
    return;
}

void teste_2_a_b()
{
    double **A = criamat(5, 4);
    A[0][0] = 4.0;
    A[0][1] = 2.0;
    A[0][2] = 3.0;
    A[0][3] = 0.0;

    A[1][0] = -2.0;
    A[1][1] = 3.0;
    A[1][2] = -1.0;
    A[1][3] = 1.0;

    A[2][0] = 1.0;
    A[2][1] = 3.0;
    A[2][2] = -4.0;
    A[2][3] = 2.0;

    A[3][0] = 1.0;
    A[3][1] = 0.0;
    A[3][2] = 1.0;
    A[3][3] = -1.0;

    A[4][0] = 3.0;
    A[4][1] = 1.0;
    A[4][2] = 3.0;
    A[4][3] = -2.0;

    double *b = criavet(5);
    b[0] = 10.0;
    b[1] = 0.0;
    b[2] = 2.0;
    b[3] = 0.0;
    b[4] = 5.0;

    double *x = mmq(5, 4, A, b);
    double e = mmq_norma2(5, 4, A, b, x);
    printf("Questao 2a (b)\n");
    printf("Vetor x = [%0.3f, %0.3f, %0.3f, %0.3f]\n", x[0], x[1], x[2], x[3]);
    printf("erro pela norma2: %0.3f\n", e);
    return;
}

void teste_2_b()
{
    double *t = criavet(8);
    double *c = criavet(8);

    for (int i = 0; i < 8; i++)
    {
        t[i] = i + 1;
    }

    c[0] = 8.0;
    c[1] = 12.3;
    c[2] = 15.5;
    c[3] = 16.8;
    c[4] = 17.1;
    c[5] = 15.8;
    c[6] = 15.2;
    c[7] = 14.0;

    double a, b;
    ajuste(8, t, c, &a, &b);

    printf("Questao 2 b\n");
    printf("a, b = %0.5f, %0.5f\n", a, b);
    return;
}

int main()
{
    // teste_mmq_simples();
    teste_2_a_a();
    teste_2_a_b();
    teste_2_b();

    return 0;
}