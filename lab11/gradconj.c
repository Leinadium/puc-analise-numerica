# include "gradconj.h"
# include "matriz.h"

# define TRUE 1
# define FALSE 0
# define LOOP(I, N) for (I = 0; I < N; I++)


/* cria M a partir da precondicao */
double **cria_m(int n, double **A, int precond) {
    double **ret = criamat(n, n);
    int i, j;

    LOOP(i, n) {
        LOOP(j, n) { ret[i][j] = 0.0; }
        ret[i][i] = precond ? (1/A[i][i]) : 1.0;
    }
    return ret;
}

/* copia o vetor origem no destino */
void copia(int n, double *dest, double *ori) {
    int i;
    LOOP(i, n) {dest[i] = ori[i];}
}


/* 
    faz a operação:
    ret = vet1 + escalar * vet2 (se soma > 0)
    ret = vet1 - escalar * vet2 (se soma = 0)
*/

void operacao(int n, double* vet1, double escalar, double* vet2, double *ret, int soma) {
    int i;
    double *temp_ret = criavet(n);

    LOOP(i, n) {
        temp_ret[i] = vet1[i];
    }
    double *temp = criavet(n);
    multvs(n, vet2, escalar, temp);
    LOOP(i, n) {
        temp_ret[i] += (soma ? 1.0 : -1.0) * temp[i];
    }
    copia(n, ret, temp_ret);
    liberavet(temp_ret);
    liberavet(temp);

    return;
}

/*
    Função que resolve um sistema linear pelo método Gradientes Conjugados, dada uma estimativa
    inicial da solução x. Quando a norma-2 do resíduo for menor que a tolerância especificada,
    a solução é considerava válida e as iterações devem ser interrompidas.
    A função deve sobreescrever a solução final x e retornar o número de iterações efetuado.
    A função também recebe um parâmetro indicando qual pré-condicionador deve ser usado.

*/
int gradconj(int n, double **A, double *b, double *x, double tol, int precond) {
    
    int i, k, iteracoes = 0;
    double esc_alfa, esc_beta, base_beta;
    double *vet_r = criavet(n);
    double *vet_temp = criavet(n);
    double *vet_d = criavet(n);
    double *vet_z = criavet(n);
    double **mat_m1 = criamat(n, n);
    // x0 = estimativa inicial
    
    // r0 = b - A x0
    multmv(n, n, (const double **) A, x, vet_temp);
    LOOP(i, n) {vet_r[i] = b[i] - vet_temp[i];}

    // d0 = z0 = M-1 r0
    mat_m1 = cria_m(n, A, precond);
    multmv(n, n, (const double **) mat_m1, vet_r, vet_z);
    copia(n, vet_d, vet_z);

    // for k = 0..n-1 do
    while (norma2(n, vet_r) >= tol) {
        // if ||rk||2 < tol then
        //  stop
        // end
        iteracoes ++;

        base_beta = escalar(n, vet_r, vet_z);       // fazendo uma parte de beta, antes das variaveis mudarem (vet_r e vet_z)

        // alfa[k] = ...
        multmv(n, n, (const double **) A, vet_d, vet_temp);
        esc_alfa = escalar(n, vet_r, vet_z) / escalar(n, vet_d, vet_temp);
        
        // x[k+1] = x[k] + a[k]*d[k]
        operacao(n, x, esc_alfa, vet_d, x, TRUE);
        
        // r[k+1] = r[k] - a[k]*Ad[k]
        multmv(n, n, (const double **) A, vet_d, vet_temp);
        operacao(n, vet_r, esc_alfa, vet_temp, vet_r, FALSE);

        // z[k+1] = M-1 r[k+1]
        multmv(n, n, (const double **) mat_m1, vet_r, vet_z);

        // beta[k] = ...
        esc_beta = escalar(n, vet_r, vet_z) / base_beta;

        //d[k+1] = z[k+1] + B[k]*d[k]
        operacao(n, vet_z, esc_beta, vet_d, vet_d, TRUE);
    }
    liberavet(vet_r);
    liberavet(vet_temp);
    liberavet(vet_d);
    liberavet(vet_z);
    liberamat(n, mat_m1);

    return iteracoes;
}