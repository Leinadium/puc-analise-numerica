#include <stdio.h>
#include <math.h>

#include "raiz.h"

double fa(double x)
{
    return x * x * x + x - 7;
}

double fb(double x)
{
    return x * x * x * x + x + 1;
}

double fc(double m)
{
    double g = 9.8;
    double c = 15.0;
    double v = 35.0;
    double t = 9.0;

    // funcao: v = f(m) = gm/c (1 - e^(-ct/m))
    // como v = 35, seja g(m) = f(m) - 35
    // logo, g(m) = gm/c (1-e^(-ct/m)) - 35
    // se g(m) = 0, entao f(m) = 35

    return (g * m / c) * (1 - exp(-c * t / m)) - v;
}

void testeA()
{
    double x_secante;
    double x_iqi;
    int r1, r2;

    r1 = secante(0, 3, fa, &x_secante);
    r2 = IQI(0, 2, 3, fa, &x_iqi);

    printf("\nletra A:\n");
    printf("x_secante: %f [%d]\n", x_secante, r1);
    printf("x_iqi: %f [%d]\n", x_iqi, r2);
    return;
}

void testeB()
{
    double ignore;
    int r;

    printf("\nLetra B:\n");
    if ((r = secante(-10, 20, fb, &ignore)) == 0)
    {
        printf("Nao converge (sucesso!)\n");
    }
    else
    {
        printf("Erro no testeB na funcao secante (%d, %f)\n", r, ignore);
    }

    if ((r = IQI(-10, 0, 10, fb, &ignore)) == 0)
    {
        printf("Nao converge (sucesso!)\n");
    }
    else
    {
        printf("Erro no testeB na funcao IQI (%d, %f)\n", r, ignore);
    }
}

void testeC()
{
    printf("\nLetra C\n");
    double x_secante;
    double x_iqi;
    int r1, r2;

    r1 = secante(0, 100, fc, &x_secante);
    r2 = IQI(0, 50, 100, fc, &x_iqi);

    printf("x_secante: %f [%d]\n", x_secante, r1);
    printf("x_iqi: %f [%d]\n", x_iqi, r2);
    return;
}

int main()
{
    printf("Iniciando testes\n");
    testeA();
    testeB();
    testeC();
    printf("\nTestes finalizados\n");
    return 0;
}