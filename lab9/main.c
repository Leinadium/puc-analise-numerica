#include <stdio.h>
#include "massamola.h"

void teste()
{
    double vetor_x[1000];
    double vetor_y[1000];

    simula(200.0, 0.0, 100.0, 1000, vetor_x, vetor_y);

    for (int i = 0; i < 1000; i++)
    {
        printf("%f %f\n", vetor_x[i], vetor_y[i]);
    }
}

int main()
{
    teste();
    return 0;
}