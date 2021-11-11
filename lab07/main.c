/* Daniel Guimarães - 1910462 */

#include <math.h>
#include <stdio.h>

#include "trapezio.h"

double integral1(double x)
{
    return x / (sqrt((x * x) + 9));
}

double integral2(double x)
{
    return exp(-(x * x));
}

double integral3(double x)
{
    return log(cos(x) + sin(x));
}

void teste1()
{
    double tols[5] = {1e-2, 1e-3, 1e-4, 1e-5, 1e-6};

    for (int i = 0; i < 5; i++)
    {
        printf(
            "tol: %0.4e -> %1.8f | %1.8f | %1.8f\n",
            tols[i],
            adaptativa(0, 1, integral1, tols[i]),
            adaptativa(0, 4, integral2, tols[i]),
            adaptativa(0, M_PI_2, integral3, tols[i]));
    }
    return;
}

void teste2()
{
    double sigmas[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++)
    {
        printf("sigma: %0.4e -> p(sigma): %1.8f\n", sigmas[i], probabilidade(sigmas[i]));
    }
    return;
}

int main()
{
    printf("\nFunção adaptativa: \n");
    teste1();
    printf("\nFuncao probabilidade: \n");
    teste2();
    return 0;
}