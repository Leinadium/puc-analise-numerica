#include <stdio.h>
#include <math.h>

// para rand
#include <stdlib.h>
#include <time.h>

#include "otimizacao.h"


double f1(double x) {
    return x*x + sin(x);
}

double f2(double x) {
    return x*x*x*x*x*x - 11*x*x*x + 17*x*x - 7*x + 1;
}


double numrand(double mult, double minus) {
    double x = (double) rand() / RAND_MAX;
    return x * mult - minus;
}


void teste1() {
    double xmin, r, s, t;
    int i;
    printf("\n\nTeste da funcao 1 (todos com tol = 1e-5)\n");

    printf("  Secao Aurea: \n");
    i = SecaoAurea(-2.0, 1.0, f1, 1e-5, &xmin);
    printf("    intervalo [-2.0, 1.0] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(-1.5, 0, f1, 1e-5, &xmin);
    printf("    intervalo [-1.5, 0.0] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(-1.0, 5.0, f1, 1e-5, &xmin);
    printf("    intervalo [-1.0, 5.0] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(-1.5, 1.5, f1, 1e-5, &xmin);
    printf("    intervalo [-1.5, 1.5] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(-0.5, 0.0, f1, 1e-5, &xmin);
    printf("    intervalo [-0.5, 0.0] -> %0.5f com %d iterações\n", xmin, i);

    printf("  MIPS: \n");
    for (int j = 0; j < 5; j ++) {
        r = numrand(4.0, 2.0);
        s = numrand(4.0, 2.0);
        t = numrand(4.0, 2.0);
        i = MIPS(r, s, t, f1, 1e-5, &xmin);
        printf("    rst [%0.2f, %0.2f, %0.2f] -> %0.5f com %d iteracoes\n", r, s, t, xmin, i);
        
    }
}

void teste2() {
    double xmin, r, s, t;
    int i;
    printf("\n\nTeste da funcao 2 (todos com tol = 1e-5)\n");

    printf("  Secao Aurea: \n");
    i = SecaoAurea(-0.5, 1.5, f2, 1e-5, &xmin);
    printf("    intervalo [-0.5, 1.5] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(-1.0, 1.5, f2, 1e-5, &xmin);
    printf("    intervalo [-1.0, 1.5] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(0.5, 1.5, f2, 1e-5, &xmin);
    printf("    intervalo [0.5, 1.5] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(0.0, 1.0, f2, 1e-5, &xmin);
    printf("    intervalo [0.0, 1.0] -> %0.5f com %d iterações\n", xmin, i);

    i = SecaoAurea(0.0, 0.5, f2, 1e-5, &xmin);
    printf("    intervalo [0.0, 0.5] -> %0.5f com %d iterações\n", xmin, i);

    printf("  MIPS: \n");
    for (int j = 0; j < 5; j ++) {
        xmin = 0;
        r = numrand(2.0, 0.5);
        s = numrand(2.0, 0.5);
        t = numrand(2.0, 0.5);
        i = MIPS(r, s, t, f2, 1e-5, &xmin);
        printf("    rst [%0.2f, %0.2f, %0.2f] -> %0.5f com %d iteracoes\n", r, s, t, xmin, i);
        
    }
}


int main() {
    // srand(time(NULL));

    teste1();
    teste2();

    return 0;

}