# include <stdio.h>
# include "gradconj.h"
# include "matriz.h"

double **gera_mat() {
    double **ret = criamat(10, 10);
    for (int i = 0; i < 10; i++) {
        if (i > 0) {
            ret[i][i-1] = 0.4;
        }
        ret[i][i] = (double) i + 1;
        if (i < 9) {
            ret[i][i+1] = 0.4;
        }
    }
    return ret;
}

void teste() {
    double **A = gera_mat();
    double b[10] = {
        1.4, 2.8, 3.8, 4.8, 5.8, 6.8, 7.8, 8.8, 9.8, 10.4
    };
    double x1[10] = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    };
    double x2[10] = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    };

    int iteracoes1 = gradconj(10, A, b, x1, 1e-7, 0);
    int iteracoes2 = gradconj(10, A, b, x2, 1e-7, 1);

    printf("sem precond: iter=[%02d], v=[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f]\n",
         iteracoes1, x1[0],x1[1],x1[2],x1[3],x1[4],x1[5],x1[6],x1[7],x1[8],x1[9]);
    printf("com precond: iter=[%02d], v=[%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f,%0.1f]\n",
         iteracoes2, x2[0],x2[1],x2[2],x2[3],x2[4],x2[5],x2[6],x2[7],x2[8],x2[9]);

    liberamat(10, A);
}

int main() {
    teste();
    return 0;
}