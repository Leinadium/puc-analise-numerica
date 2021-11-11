#include <math.h>
#include "massamola.h"

#define K_MOLA 0.5
#define R_MOLA 200.0
#define M_CORPO 2.0
#define GRAVIDADE 9.8
#define VENTO_INICIAL 20.0
#define AMORTECIMENTO 0.002

/*
    Função que receba como parâmetros o tempo t e a posição corrente do corpo (x, y).
    Calcula os valores da força total (gravidade + vento + mola) atuante e preencher os ponteiros
    também passados como parâmetros.
*/
void forca(double t, double x, double y, double *fx, double *fy)
{
    double forca_x = 0.0;
    double forca_y = 0.0;
    double forca_mola, comp;

    // considerando gravidade
    forca_y += M_CORPO * GRAVIDADE;

    // considerando vento
    forca_x += (VENTO_INICIAL * exp(-t / 20.0));

    // considerando a mola
    comp = sqrt(x * x + y * y);
    forca_mola = -K_MOLA * (comp - R_MOLA);
    forca_x += forca_mola * x / comp;
    forca_y += forca_mola * y / comp;

    *fx = forca_x;
    *fy = forca_y;
    return;
}

/*
    Usando o método de Verlet, dada uma configuração no instante t, calcula a nova posição
    do corpo no instante t + h.
    Recebe como parâmetros o tempo corrente t, o passo de integração h, a posição corrente (x, y) e 
    a posição anterior (xp, yp).
    Preenche a nova posição nos endereços de memória também passados como parâmetros e retorna o tempo
    atualizado (t + h)
*/
double evolui(double t, double h, double x, double y, double xp, double yp, double *xn, double *yn)
{
    double fx, fy;
    forca(t, x, y, &fx, &fy);
    *xn = x + (1 - AMORTECIMENTO) * (x - xp) + h * h * fx / M_CORPO;
    *yn = y + (1 - AMORTECIMENTO) * (y - yp) + h * h * fy / M_CORPO;
    return t + h;
}

/*
    Função que preenche um vetor de posições do corpo ao longo do tempo.
    Recebe como parâmetros a posição inicial (x0, y0), o tempo total de simulação t_final,
    e o número de iterações n, fazendo o passo de integração valer h = t_final / n.
    A função preenche os vetores x e y, previamente alocados, de dimensão n,
    com as posições do corpo nos instantes h, 2h, ... , nh
*/
void simula(double x0, double y0, double t_final, int n, double *x, double *y)
{
    double h = t_final / n;

    double x_atual = x0;
    double y_atual = y0;
    double x_anterior = x0;
    double y_anterior = y0;
    double x_proximo, y_proximo;
    double t_atual = 0.0;

    for (int i = 0; i < n; i++)
    {
        t_atual = evolui(t_atual, h, x_atual, y_atual, x_anterior, y_anterior, &x_proximo, &y_proximo);
        x[i] = x_proximo;
        y[i] = y_proximo;
        x_anterior = x_atual;
        y_anterior = y_atual;
        x_atual = x_proximo;
        y_atual = y_proximo;
    }
}