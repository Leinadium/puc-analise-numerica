/* Daniel Guimarães - 1910462 */

#include <math.h>
#include <stdio.h>

double _T(double a, double b, double (*f)(double x))
{
    return (b - a) / 2 * (f(a) + f(b));
}

/*
    Função para Integração Adaptativa segundo a Regra do Trapézio.
    Recebe o intervalo de integração, a função e a tolerância de erro desejada,
    e retornar o valor total da derivada no intervalo dentro da tolerância.
 */
double adaptativa(double a, double b, double (*f)(double x), double tol)
{
    double c = (a + b) / 2.0;
    double Tab = _T(a, b, f);
    double Tac = _T(a, c, f);
    double Tcb = _T(c, b, f);
    double delta = Tab - Tac - Tcb;
    double delta3 = delta / 3.0;

    if (fabs(delta3) < tol)
    {
        return Tac + Tcb - (delta / 3.0);
    }
    else
    {
        double tol2 = tol / 2.0;
        return adaptativa(a, c, f, tol2) + adaptativa(c, b, f, tol2);
    }
}

double _F(double x)
{
    return exp(-(x * x) / 2);
}

/*
    Funcao que recebe como parâmetro o valor de sigma e retorna a probabilidade,
    usando a função do item anterior, com precisão de 8 dígitos.
 */
double probabilidade(double sigma)
{
    double tol = 0.5e-8;
    double cons = 1 / sqrt(2 * M_PI);

    return cons * adaptativa(-sigma, sigma, _F, tol);
}