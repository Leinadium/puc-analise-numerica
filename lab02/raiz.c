#include <math.h> // para o fabs somente

#include "raiz.h"

#define LIMITE_ITER 50

double erro(double novo, double anterior)
{
    return (fabs(novo - anterior)) / fabs(novo);
}

/*
    Determina uma raiz da funcao entre as estimativas iniciais,
    com um erro relativo de precisao de 8 digitos.

    Retorna o numero de iterações para determinar a raiz
    Se não houver convergência, a função deve retornar zero
 */
int secante(double x0, double x1, double (*f)(double x), double *r)
{
    int i = 0;
    double t, fx0, fx1;
    while (i <= LIMITE_ITER)
    {
        // verificando se encontrei os valores corretos
        if (erro(x1, x0) < 0.5e-8)
        {
            *r = x1;
            return i;
        }
        // descobrindo o proximo valor
        fx1 = f(x1);
        fx0 = f(x0);
        // salvando o valor em t
        if (fabs(fx1 - fx0) < 1e-15)
        {
            t = (x0 + x1) / 2;
        }
        else
        {
            t = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);
        }
        // atualizando x0 e x1
        x0 = x1;
        x1 = t;
        i++;
    }
    return 0;
}

int IQI(double x0, double x1, double x2, double (*f)(double x), double *r)
{
    int i = 0;
    double c, fx0, fx1, fx2, fx0_2, fx1_2, fx2_2, det_A, det_Ac;
    while (i <= LIMITE_ITER)
    {
        // verificando se encontrei os valores corretos
        if (erro(x2, x1) < 0.5e-8)
        {
            *r = x2;
            return i;
        }
        // criando as constantes
        fx0 = f(x0);
        fx0_2 = fx0 * fx0;
        fx1 = f(x1);
        fx1_2 = fx1 * fx1;
        fx2 = f(x2);
        fx2_2 = fx2 * fx2;

        // resolvendo a det da matriz A

        // se A =   | A | B | C |
        //          | D | E | F |
        //          | G | H | I |
        // det =
        //  A(EI - FH) - B(DI - FG) + C(DH - EG)

        det_A = fx0_2 * (fx1 - fx2);
        det_A -= fx0 * (fx1_2 - fx2_2);
        det_A += (fx1_2 * fx2 - fx1 * fx2_2);

        // resolvendo a det da matriz Ac
        det_Ac = fx0_2 * (fx1 * x2 - fx2 * x1);
        det_Ac -= fx0 * (fx1_2 * x2 - x1 * fx2_2);
        det_Ac += x0 * (fx1_2 * fx2 - fx1 * fx2_2);

        c = det_Ac / det_A;

        // atualizando as variaveis
        x0 = x1;
        x1 = x2;
        x2 = c;
        i++;
    }
    return 0;
}