#include "ode.h"
#include <math.h>
#include <stdio.h>

/* 
    Função do metodo de Runge Kutta com passo constante
    Recebe o tempo inicial t0, o tempo final t1, passo de integração h, valor inicial y(t0) e a funcao derivada.
    Retorna o valor no tempo final y(t1)
 */
double RungeKutta(double t0, double t1, double h, double y0, double (*f)(double t, double y))
{
    double t = t0;
    double y = y0;
    double k1, k2, k3, k4, passo2, ynovo;

    char ultima = 'f';
    unsigned int iteracoes = 0;
    while (t < t1)
    {
        iteracoes += 1;
        if (t + h >= t1)
        {
            h = t1 - t;
            ultima = 't';
        }

        k1 = h * f(t, y);
        k2 = h * f(t + h / 2.0, y + k1 / 2.0);
        k3 = h * f(t + h / 2.0, y + k2 / 2.0);
        k4 = h * f(t + h, y + k3);

        t += h;
        y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;

        // printf("y = %0.3f, t = %0.3f\n", y, t);
        if (ultima == 't' || t == t1)
            break;
    }
    printf("%e\n", h);
    printf("RangeKutta: %e [iter:%d]\n", y, iteracoes);
    return y;
}

double RungeKuttaAcoplado(double t0, double t1, double y0, double (*f)(double t, double y), double tol)
{

    double ai[6] = {0.0, 0.2, 0.3, 0.6, 1.0, 0.875};
    double bij[6][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {1.0 / 5.0, 0.0, 0.0, 0.0, 0.0},
        {3.0 / 40.0, 9.0 / 40, 0.0, 0.0, 0.0},
        {3.0 / 10.0, -9.0 / 10.0, 6.0 / 5.0, 0.0, 0.0},
        {-11.0 / 54.0, 5.0 / 2.0, -70.0 / 27.0, 35.0 / 27.0, 0.0},
        {1631.0 / 55296.0, 175.0 / 512.0, 575.0 / 13824.0, 44275.0 / 110592.0, 253.0 / 4096.0},
    };

    double ci[6] = {37.0 / 378.0, 0.0, 250.0 / 621.0, 125.0 / 594.0, 0.0, 512.0 / 1771.0};
    double ci_star[6] = {2825.0 / 27648.0, 0.0, 18575.0 / 48384.0, 13525.0 / 55296.0, 277.0 / 14336.0, 1.0 / 4.0};

    double y, yi, yi_star, delta, fator, h_linha, passo, t;
    double vk[6];
    passo = 0.0000001;
    t = t0;
    y = y0;

    char ultima = 0;
    unsigned int iteracoes = 0;
    while (t < t1)
    {
        iteracoes += 1;
        if (t + passo > t1)
        {
            passo = t1 - t;
        }

        if (iteracoes % 1000000 == 0)
        {
            printf("iteracao: %u, passo: %e, t: %e\n", iteracoes, passo, t);
        }

        vk[0] = passo * f(t, y);
        vk[1] = passo * f(t + ai[1] * passo, y + (bij[1][0] * vk[0]));
        vk[2] = passo * f(t + ai[2] * passo, y + (bij[2][0] * vk[0]) + (bij[2][1] * vk[1]));
        vk[3] = passo * f(t + ai[3] * passo, y + (bij[3][0] * vk[0]) + (bij[3][1] * vk[1]) + (bij[3][2] * vk[2]));
        vk[4] = passo * f(t + ai[4] * passo, y + (bij[4][0] * vk[0]) + (bij[4][1] * vk[1]) + (bij[4][2] * vk[2]) + (bij[4][3] * vk[3]));
        vk[5] = passo * f(t + ai[5] * passo, y + (bij[5][0] * vk[0]) + (bij[5][1] * vk[1]) + (bij[5][2] * vk[2]) + (bij[5][3] * vk[3]) + (bij[5][4] * vk[4]));

        yi = ci[0] * vk[0] + ci[1] * vk[1] + ci[2] * vk[2] + ci[3] * vk[3] + ci[4] * vk[4] + ci[5] * vk[5];
        yi_star = ci_star[0] * vk[0] + ci_star[1] * vk[1] + ci_star[2] * vk[2] + ci_star[3] * vk[3] + ci_star[4] * vk[4] + ci_star[5] * vk[5];
        delta = fabs(yi - yi_star);
        yi += y; // para evitar erros de arredondamento ?

        /*
        for (int x = 0; x < 6; x++)
        {
            yi += ci[x] * vk[x];
            delta += vk[x] * (ci[x] - ci_star[x]);
        }
        delta = fabs(delta);
        */

        fator = pow(tol / delta, 0.2);
        // printf("tol:%e, delta: %e, fator: %e\n", tol, delta, fator);

        if (fator >= 1.0)
        {
            y = yi;
            t = t + passo;
            passo = passo * fmin(1.2, fator);
        }
        else
        {
            passo *= (0.9 * fator);
        }
    }
    printf("RangeKuttaAcoplado: %e [iter:%d]\n", y, iteracoes);
    return y;
}
