/*
    Feito por Daniel Guimaraes - 1910462
*/

#include <stdio.h>
#include <math.h>
#include "matriz.h"

#define vetor_t double *
#define matriz_t double **

void teste1e2()
{
    // testa se criou o vetor sem erros, e
    // se o espaco alocado foi correto
    // e depois, se consegue ser liberado com sucesso
    vetor_t v = criavet(3);

    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    liberavet(v);
    return;
}

void teste3()
{
    // testando o escalar
    vetor_t v = criavet(3);
    vetor_t vv = criavet(3);

    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;

    vv[0] = M_PI;
    vv[1] = 0;
    vv[2] = -123.999;

    double x = escalar(3, v, vv);
    double esperado = (M_PI) + (-3 * 123.999);
    if (fabs(x - esperado) > 0.01)
    {
        printf("Erro no teste3!\n");
        printf("%f | %f\n", x, esperado);
    }
    return;
}

void teste4()
{
    vetor_t v = criavet(4);
    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;
    v[3] = 4.0;

    int x = norma2(4, v);
    if (fabs(x - sqrt(30) > 0.01))
    {
        printf("Erro no teste3!\n");
    }
    return;
}

void teste5()
{
    vetor_t v = criavet(2);
    vetor_t vv = criavet(2);
    v[0] = -9.0;
    v[1] = 9.0;

    multvs(2, v, 1.0 / 9.0, vv);

    if ((fabs(vv[0] + 1) > 0.01) | (fabs(vv[1] - 1) > 0.01))
    {
        printf("Erro no teste 4!\n");
    }
}

void teste6e8()
{
    // testando se a criacao de uma matriz funciona
    // com a quantidade correta de espacos
    // e se consegue fechar corretamente

    matriz_t mat = criamat(2, 2);
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
    mat[1][0] = 3.0;
    mat[1][1] = 4.0;
    liberamat(2, mat);
}

void teste7()
{
    // tentando se a criacao de uma matriz triangular funciona
    matriz_t mat = criamattri(3);
    mat[0][0] = 0.0;
    mat[1][0] = 1.0;
    mat[1][1] = 2.0;
    mat[2][0] = 3.0;
    mat[2][1] = 4.0;
    mat[2][2] = 5.0;
    liberamat(3, mat);
}

void teste9()
{
    // testando a transposicao de matriz
    matriz_t A = criamat(2, 3);
    matriz_t T = criamat(3, 2);

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;

    transposta(2, 3, (const matriz_t)A, T);

    if (A[0][0] != T[0][0])
    {
        printf("Erro no teste9!\n");
    }
    if (A[0][1] != T[1][0])
    {
        printf("Erro no teste9!\n");
    }
    if (A[0][2] != T[2][0])
    {
        printf("Erro no teste9!\n");
    }
    if (A[1][0] != T[0][1])
    {
        printf("Erro no teste9!\n");
    }
    if (A[1][1] != T[1][1])
    {
        printf("Erro no teste9!\n");
    }
    if (A[1][2] != T[2][1])
    {
        printf("Erro no teste9!\n");
    }

    liberamat(2, A);
    liberamat(3, T);

    return;
}

void teste10()
{
    vetor_t v = criavet(3);
    vetor_t w = criavet(3);

    matriz_t A = criamat(3, 3);

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;
    A[2][0] = 7.0;
    A[2][1] = 8.0;
    A[2][2] = 9.0;

    v[0] = 10.0;
    v[1] = 20.0;
    v[2] = 30.0;

    multmv(3, 3, (const matriz_t)A, v, w);

    if (fabs(w[0] - 140.0) > 0.01)
    {
        printf("Erro no teste10!\n");
        printf("%f\n", w[0]);
    }
    if (fabs(w[1] - 320.0) > 0.01)
    {
        printf("Erro no teste10!\n");
        printf("%f\n", w[1]);
    }
    if (fabs(w[2] - 500.0) > 0.01)
    {
        printf("Erro no teste10!\n");
        printf("%f\n", w[2]);
    }

    liberamat(3, A);
    liberavet(v);
    liberavet(w);
}

void teste11()
{
    matriz_t A = criamat(2, 2);
    matriz_t B = criamat(2, 2);
    matriz_t C = criamat(2, 2);

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[1][0] = 3.0;
    A[1][1] = 4.0;

    B[0][0] = 4.0;
    B[0][1] = 5.0;
    B[1][0] = 6.0;
    B[1][1] = 7.0;

    /* 
    1 2     4 5    16 19
    3 4  x  6 7  = 36 43
    */

    multmm(2, 2, 2, (const matriz_t)A, (const matriz_t)B, C);

    if (fabs(C[0][0] - 16.0) > 0.01)
    {
        printf("Erro no teste11!\n");
        printf("%f\n", C[0][0]);
    }
    if (fabs(C[0][1] - 19.0) > 0.01)
    {
        printf("Erro no teste11!\n");
        printf("%f\n", C[0][1]);
    }
    if (fabs(C[1][0] - 36.0) > 0.01)
    {
        printf("Erro no teste11!\n");
        printf("%f\n", C[1][0]);
    }
    if (fabs(C[1][1] - 43.0) > 0.01)
    {
        printf("Erro no teste11!\n");
        printf("%f\n", C[1][1]);
    }
    liberamat(2, A);
    liberamat(2, B);
    liberamat(2, C);
}

int main()
{
    printf("iniciando testes. \n");
    printf("se houver algum erro, sera impresso abaixo\n-----\n");

    teste1e2();
    teste3();
    teste4();
    teste5();
    teste6e8();
    teste7();
    teste9();
    teste10();
    teste11();

    printf("\n-----\nfinalizado\n");

    return 0;
}