#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "interp.h"

#define SIGMA 0.5
#define MI 0.0

void verifica_vetor(double *v)
{
    if (v == NULL)
    {
        printf("Erro alocando vetor!\n");
        exit(-1);
    }
}

double f_normal(double x)
{
    return exp((x - MI) * (x - MI) / (SIGMA * SIGMA * (-2))) / (SIGMA * sqrt(2 * M_PI));
}

double erro(double correto, double amostra)
{
    return fabs(amostra - correto); // / correto;
}

void print_v(int n, double *v)
{
    printf("Vetor: ");
    for (int i = 0; i < n; i++)
    {
        printf("%0.4f ", v[i]);
    }
    printf("\n");
}

void teste(int n)
{
    double *x_reg = (double *)malloc(sizeof(double) * n);
    double *x_cheb = (double *)malloc(sizeof(double) * n);
    double *y_reg = (double *)malloc(sizeof(double) * n);
    double *y_cheb = (double *)malloc(sizeof(double) * n);
    verifica_vetor(x_reg);
    verifica_vetor(x_cheb);
    verifica_vetor(y_reg);
    verifica_vetor(y_cheb);

    regular(n, -2, 2, f_normal, x_reg, y_reg);
    chebyshev(n, -2, 2, f_normal, x_cheb, y_cheb);

    // print_v(n, x_reg);
    // print_v(n, x_cheb);
    // print_v(n, y_reg);
    // print_v(n, y_cheb);

    double erro_med_regular = 0;
    double erro_max_regular = 0;
    double erro_med_cheb = 0;
    double erro_max_cheb = 0;
    double temp;
    double temp_regular;
    double temp_cheb;
    double rand_x;

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        rand_x = 2 - (rand() % 10000) / 2500.0;
        temp = f_normal(rand_x);
        temp_regular = lagrange(n, x_reg, y_reg, rand_x);
        temp_cheb = lagrange(n, x_cheb, y_cheb, rand_x);

        // printf("correto: %0.3f, reg: %0.3f, cheb: %0.3f\n", temp, temp_regular, temp_cheb);

        temp_regular = erro(temp, temp_regular);
        if (temp_regular > erro_max_regular)
            erro_max_regular = temp_regular;
        erro_med_regular += temp_regular;

        temp_cheb = erro(temp, temp_cheb);
        if (temp_cheb > erro_max_cheb)
            erro_max_cheb = temp_cheb;
        erro_med_cheb += temp_cheb;

        // printf("correto: %0.3f, reg: %0.3f\n\n", temp_regular, temp_cheb);
    }

    printf("Regular\n\tmax: %0.5f, med: %0.5f\n", erro_max_regular, erro_med_regular / n);
    printf("Chebyshev\n\tmax: %0.5f, med: %0.5f\n", erro_max_cheb, erro_med_cheb / n);
}

int main()
{
    teste(10);
    // teste(20);
    // teste(30);
    return 0;
}