#include <stdio.h>
#include <math.h>

#include "taylor.h"

void calculaMelhor(double x)
{
    double valorCorreto = tan(x);
    double valor1 = tan1(x);
    double valor2 = tan2(x);

    double erro1 = fabs(valor1 - valorCorreto);
    double erro2 = fabs(valor2 - valorCorreto);

    if (erro1 <= erro2)
    {
        printf("tan1 foi melhor [v1: %f, v2: %f, vc:%f (e1: %f, e2: %f)]\n",
               valor1, valor2, valorCorreto, erro1, erro2);
    }
    else
    {
        printf("tan2 foi melhor [v1: %f, v2: %f, vc:%f (e1: %f, e2: %f)]\n",
               valor1, valor2, valorCorreto, erro1, erro2);
    }
}

void testes()
{
    double valores[5] = {
        M_PI / 10,
        M_PI / 8,
        M_PI / 6,
        M_PI / 4,
        M_PI / 3,
    };

    printf("Iniciando testes: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("Testando o valor %f -> ", valores[i]);
        calculaMelhor(valores[i]);
        printf("\n");
    }
    printf("Finalizando testes!\n");
}

int main()
{
    testes();
    return 0;
}