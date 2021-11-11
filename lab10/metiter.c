# include <stdio.h>
# include <stdlib.h>
# include "metiter.h"
# include "matriz.h"


double absoluto(double x) {
    return (x > 0)? x : -x;
}

/*
    Verifica se uma dada matriz A de dimensao n x n é 
    estritamente diagonal dominante.
    Recebe como parâmetro a matriz, e deve retornar 1 se a
    matriz foi estritamente diagonal dominante ou 0, 
    caso contrário
*/
int diagonal_dominante(int n, double **A) {
    double Aii;
    for (int i = 0; i < n; i ++) {
        Aii = absoluto(A[i][i]);
        for (int j = 0; j < n; j ++) {
            if (i == j)
                continue;
            if (A[i][i] <= absoluto(A[i][j]))
                return 0;
        }
    }
    return 1;
}

/* funcao auxiliar para calcular o residuo */
double residuo(int n, double **A, double *b, double *x, double tol) {
    double *r = criavet(n);
    double *Ax = criavet(n);
    double res;
    // faz os calculos
    multmv(n, n, (const double **) A, x, Ax);
    for (int i = 0; i < n; i++) { r[i] = b[i] - Ax[i]; }
    res = norma2(n, r);
    // libera as alocacoes
    liberavet(r);
    liberavet(Ax);

    return res;
}

/* faz D-1 * (b - U * x[k] + L * x[k+1]) para uma linha i */ 
double calcula(int n, double **A, double *b, double *x, int i) {
    double temp;
    int j;
    temp = b[i];

    // - U * x[k] + L * x[k+1]
    for (j = 0; j < n; j ++) {
        if (i == j) continue;
        temp -= A[i][j] * x[j];
    }
    // D-1 * (...)
    temp *= 1/A[i][i];
    
    return temp;

}
/*
    Função que recebe como parâmetros a dimensão do problema n,
    a matriz A, o vetor independente b, a aproximação inicial da solução x,
    e a tolerância de erro aceitável. A iteração deve terminar quando a norma-2
    do vetor resíduo tiver valor menor ou igual à tolerância.
    A função deve armazenar a solução final em x, e retornar o número de iterações efeutado.
    Se a matriz A não for estritamente diagonal dominante, a função deve retornar zero.

 */
int gauss_seidel(int n, double **A, double *b, double *x, double tol) {
    if (!diagonal_dominante(n, A)) {
        printf("Nao eh diagonal estritamente dominante. Abortando.\n");
        return 0;
    }

    int i, q = 0;
    while (residuo(n, A, b, x, tol) > tol) {
        for (i = 0; i < n; i ++) {
            x[i] = calcula(n, A, b, x, i);
        }
        q++;
    }
    return q;
}

/*
    Funcao que implementa o metodo iterativo de Gauss-Seidel com 
    sobre-relaxamento (w > 1.0). A função avalia inicialmente x[k+1]
    com o método, e então ajusta x[k+1] com a fórmula.
*/

int SOR(int n, double **A, double *b, double *x, double tol, double w) {
    if (!diagonal_dominante(n, A)) {
        printf("Nao eh diagonal estritamente dominante. Abortando\n");
        return 0;
    }
    int i, q = 0;
    double temp;
    while (residuo(n, A, b, x, tol) > tol) {
        for (i = 0; i < n; i ++) {
            temp = calcula(n, A, b, x, i);
            x[i] = (1 - w) * x[i] + w * temp;
        }
        q++;
    }
    return q;
}