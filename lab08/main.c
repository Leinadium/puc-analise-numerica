#include "ode.h"
#include <math.h>
#include <stdio.h>

double funcao(double t, double y)
{
    return (t * y + t * t * t);
}

double yt(double t)
{
    return (exp(t * t / 2.0) - t * t - 2.0);
}

void teste(double algum_valor)
{
    printf("\nTestando para t1 = %0.3f\n", algum_valor);
    double y = RungeKutta(0.0, algum_valor, 0.001, -1.0, funcao);
    // printf("y do RungeKutta: %0.3f\n", y);
    double y2 = RungeKuttaAcoplado(0.0, algum_valor, -1.0, funcao, 0.000000000001);
    // printf("y do RungeKuttaAcoplado: %0.3f\n", y2);
    printf("Valor correto: %e\n", yt(algum_valor));
}

int main()
{
    teste(2.4);
    teste(0.5);
    teste(1.0);

    return 0;
}