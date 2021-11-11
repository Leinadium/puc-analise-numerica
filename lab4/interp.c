#include <math.h>

/*
    Função que retorna n amostras espaçadas regularmente no intervalo [a, b], 
    onde xi[0] = a, xi[n-1] = b, e os demais valores são regularmente distribuidos no intervalo.
    A função deve calcular as amostras xi e os valores yi = f(xi), preenchendo os vetores xi e yi pré-alocados.
 */
void regular(int n, double a, double b, double (*f)(double x), double *xi, double *yi)
{
    double dif = (b - a) / (n - 1);
    double c = a;

    for (int i = 0; i < n; i++)
    {
        xi[i] = c;
        yi[i] = f(c);
        c += dif;
    }
    return;
}

/*
    Função que retorna as n amostras de Chebyshev para a aproximação de uma função,
    dentro do intervalo [a, b]
    A função deve calcular as amostras xi e os valores yi = f(xi), preenchendo os vetores xi e yi pré-alocados.
 */
void chebyshev(int n, double a, double b, double (*f)(double x), double *xi, double *yi)
{
    double c;
    double ba2 = (b - a) / 2;
    double ab2 = (a + b) / 2;
    int beta = 1;

    for (int i = 0; i < n; i++)
    {
        c = ba2 * cos(beta * M_PI / (2 * n)) + ab2;
        xi[i] = c;
        yi[i] = f(c);
        beta += 2;
    }
}

double lagrange(int n, double *xi, double *yi, double x)
{
    double ret = 0;
    double lk;

    for (int k = 0; k < n; k++)
    {
        lk = 1;
        for (int i = 0; i < n; i++)
        {
            if (k == i)
                continue;

            lk *= x - xi[i];
            lk /= xi[k] - xi[i];
        }
        ret += yi[k] * lk;
    }

    return ret;
}
