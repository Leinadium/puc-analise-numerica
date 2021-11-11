# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "metiter.h"
# include "matriz.h"


void gera_teste_1(double **A, double *x, double *b) {
    A[0][0] = 3;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 2;
    b[0] = 5;
    b[1] = 5;
    x[0] = 0;
    x[1] = 0;
}

void gera_teste_2(double **A, double *x, double *b) {
    A[0][0] = 3.0;
    A[0][1] = -1.0;
    A[0][2] = 0.0;
    A[0][3] = 0.0;
    A[0][4] = 0.0;
    A[0][5] = 0.5;

    A[1][0] = -1.0;
    A[1][1] = 3.0;
    A[1][2] = -1.0;
    A[1][3] = 0.0;
    A[1][4] = 0.5;
    A[1][5] = 0.0;

    A[2][0] = 0.0;
    A[2][1] = -1.0;
    A[2][2] = 3.0;
    A[2][3] = -1.0;
    A[2][4] = 0.0;
    A[2][5] = 0.0;

    A[3][0] = 0.0;
    A[3][1] = 0.0;
    A[3][2] = -1.0;
    A[3][3] = 3.0;
    A[3][4] = -1.0;
    A[3][5] = 0.0;

    A[4][0] = 0.0;
    A[4][1] = 0.5;
    A[4][2] = 0.0;
    A[4][3] = -1.0;
    A[4][4] = 3.0;
    A[4][5] = -1.0;

    A[5][0] = 0.5;
    A[5][1] = 0.0;
    A[5][2] = 0.0;
    A[5][3] = 0.0;
    A[5][4] = -1.0;
    A[5][5] = 3.0;

    b[0] = 2.5;
    b[1] = 1.5;
    b[2] = 1;
    b[3] = 1;
    b[4] = 1.5;
    b[5] = 2.5;

    x[0] = 0;
    x[1] = 0;
    x[2] = 0;
    x[3] = 0;
    x[4] = 0;
    x[5] = 0;
}

void teste_1() {
    double **A = criamat(2, 2);
    double *b = criavet(2);
    double *x1 = criavet(2);
    double *x2 = criavet(2);
    gera_teste_1(A, x1, b);
    for (int i = 0; i < 2; i ++) {x2[i] = x1[i];}

    int q1, q2;
    q1 = gauss_seidel(2, A, b, x1, 1e-7);
    q2 = SOR(2, A, b, x2, 1e-7, 1.1);

    printf("teste 1:\n");
    printf("gauss_seidel: %d. Valores: %0.3f, %0.3f\n", q1, x1[0], x1[1]);
    printf("SOR: %d. Valores: %0.3f, %0.3f\n", q2, x2[0], x2[1]);
    printf("fim do teste 1\n\n");
    liberamat(2, A);
    liberavet(b);
    liberavet(x1);
    liberavet(x2);
    return;
}

void teste_2() {
    double **A = criamat(6, 6);
    double *b = criavet(6);
    double *x1 = criavet(6);
    double *x2 = criavet(6);
    gera_teste_2(A, x1, b);
    for (int i = 0; i < 6; i ++) {x2[i] = x1[i];}

    int q1, q2;
    q1 = gauss_seidel(6, A, b, x1, 1e-7);
    q2 = SOR(6, A, b, x2, 1e-7, 1.1);
    printf("teste 2: \n");
    printf("gauss_seidel: %d. Valores: %0.3f, %0.3f, %0.3f, %0.3f, %0.3f, %0.3f\n", q1, x1[0], x1[1], x1[2], x1[3], x1[4], x1[5]);
    printf("SOR: %d. Valores: %0.3f, %0.3f, %0.3f, %0.3f, %0.3f, %0.3f\n", q2, x2[0], x2[1], x2[2], x2[3], x2[4], x2[5]);
    printf("fim do teste 2\n\n");
    liberamat(6, A);
    liberavet(b);
    liberavet(x1);
    liberavet(x2);
    return;
}

void teste_3() {
    double **A = criamat(2, 2);
    double *b = criavet(2);
    double *x1 = criavet(2);
    double *x2 = criavet(2);
    gera_teste_1(A, x1, b);
    for (int i = 0; i < 2; i ++) {x2[i] = x1[i];}

    // permuta a primeira linha com a segunda
    double *linha = A[0];
    A[0] = A[1];
    A[1] = linha;
    double bb = b[0];
    b[0] = b[1];
    b[1] = bb;

    printf("teste 3: deve haver dois erros abaixo \n");
    int q1, q2;
    q1 = gauss_seidel(6, A, b, x1, 1e-7);
    q2 = SOR(6, A, b, x2, 1e-7, 1.1);
    printf("fim do teste 3\n\n");
    liberamat(2, A);
    liberavet(b);
    liberavet(x1);
    liberavet(x2);
    return;
}

void teste_4() {
    double **A = criamat(6, 6);
    double *b = criavet(6);
    double *x1 = criavet(6);
    double *x2 = criavet(6);
    gera_teste_2(A, x1, b);
    for (int i = 0; i < 6; i ++) {x2[i] = x1[i];}

    // permuta a primeira linha com a segunda
    double *linha = A[0];
    A[0] = A[1];
    A[1] = linha;
    double bb = b[0];
    b[0] = b[1];
    b[1] = bb;

    printf("teste 4: deve haver dois erros abaixo \n");
    int q1, q2;
    q1 = gauss_seidel(6, A, b, x1, 1e-7);
    q2 = SOR(6, A, b, x2, 1e-7, 1.1);
    printf("fim do teste 4\n\n");
    liberamat(6, A);
    liberavet(b);
    liberavet(x1);
    liberavet(x2);
    return;
}

int main() {
    teste_1();
    teste_2();
    teste_3();
    teste_4();
    return 0;
}