#include <stdio.h>
#include <math.h>

#include "integral.h"

double f_2a(double x)
{
    return cos(x) - 2 * sin(x);
}

double f_linha_2a(double x)
{
    return -sin(x) - 2 * cos(x);
}

double erro_medio_2a(int n, double h)
{
    return (
               fabs(f_linha_2a(-3.0) - derivada(n, f_2a, -3.0, h)) +
               fabs(f_linha_2a(-2.0) - derivada(n, f_2a, -2.0, h)) +
               fabs(f_linha_2a(-1.0) - derivada(n, f_2a, -1.0, h)) +
               fabs(f_linha_2a(1.0) - derivada(n, f_2a, 1.0, h)) +
               fabs(f_linha_2a(2.0) - derivada(n, f_2a, 2.0, h)) +
               fabs(f_linha_2a(3.0) - derivada(n, f_2a, 3.0, h))) /
           6;
}

void teste_2a()
{
    printf("=== QUESTAO 2(a) ===\n");
    printf("Tabela de erro medio\n");
    printf("Cada coluna é para um n diferente, cada linha é para um passo diferente\n");

    int n[5] = {2, 3, 4, 7, 9};
    double lista_passo[6] = {1e-2, 1e-4, 1e-5, 1e-7, 1e-8, 1e-9};

    printf("             |      %d      |      %d      |      %d      |      %d      |      %d      |\n", n[0], n[1], n[2], n[3], n[4]);
    for (int i = 0; i < 6; i++)
    {
        double h = lista_passo[i];
        printf(" %1.5e | %1.5e | %1.5e | %1.5e | %1.5e | %1.5e |\n",
               h, erro_medio_2a(n[0], h), erro_medio_2a(n[1], h), erro_medio_2a(n[2], h), erro_medio_2a(n[3], h), erro_medio_2a(n[4], h));
    }
    return;
}

double integral_1(double x) { return x / (sqrt(x * x + 9)); }

double integral_2(double x) { return x * x * log(x); }

double integral_3(double x) { return x * x * sin(x); }

void teste_2b()
{
    printf("=== QUESTAO 2(b) ===\n");

    printf(" integral x |      T(16)      |      T(32)      |      S(16)      |      S(32)      |     correto     |\n");
    printf(" integral 1 | %1.13f | %1.13f | %1.13f | %1.13f | %1.13f |\n",
           trapezio(integral_1, 0, 4, 16), trapezio(integral_1, 0, 4, 32), simpson(integral_1, 0, 4, 16), simpson(integral_1, 0, 4, 32), 2.0);

    printf(" integral 2 | %1.13f | %1.13f | %1.13f | %1.13f | %1.13f |\n",
           trapezio(integral_2, 1, 3, 16), trapezio(integral_2, 1, 3, 32), simpson(integral_2, 1, 3, 16), simpson(integral_2, 1, 3, 32), 6.9986217091241);

    printf(" integral 3 | %1.13f | %1.13f | %1.13f | %1.13f | %1.13f |\n",
           trapezio(integral_3, 0, M_PI, 16), trapezio(integral_3, 0, M_PI, 32), simpson(integral_3, 0, M_PI, 16), simpson(integral_3, 0, M_PI, 32), 5.8696044010894);
    return;
}

int main()
{
    teste_2a();
    teste_2b();
    // printf("%0.3f %0.3f\n", f_linha_2a(-3.0), derivada(5, f_2a, -3.0, 1e-3));

    return 0;
}