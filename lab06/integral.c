#include <math.h>

double derivada(int n, double (*f)(double x), double x, double h)
{
    if (n == 1)
    {
        return (f(x + h) - f(x - h)) / (2 * h);
    }
    // double dois_n = pow(2, n);
    double dois_n = (1 << n);

    return (dois_n * derivada(n-1, f, x, h/2) - derivada(n - 1, f, x, h)) / (dois_n - 1);
}

double trapezio(double (*f)(double), double a, double b, int n)
{
    double passo = (b - a) / n;
    double xi = a;
    double ret = 0;
    double h_2 = passo / 2;

    for (int i = 0; i < n; i++)
    {
        ret += h_2 * (f(xi) + f(xi + passo));
        xi += passo;
    }
    return ret;
}

double simpson(double (*f)(double), double a, double b, int n)
{
    double passo = (b - a) / n;
    double xi = a;
    double ret = 0;
    double h_6 = passo / 6;
    double passo_2 = passo / 2;

    for (int i = 0; i < n; i++)
    {
        ret += h_6 * (f(xi) + 4 * f(xi + passo_2) + f(xi + passo));
        xi += passo;
    }
    return ret;
}