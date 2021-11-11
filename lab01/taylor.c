#include "taylor.h"

/* 
    Avalia a tangente de x utilizando a serie de taylor
    com tres termos, em torno da origem (x0 = 0)
*/
double tan1(double x) {
    // x0 = 0
    // primeiro termo: f(0) * 1 = 0
    // segundo termo:  f'(0)/1 * x = sec2(0) = 1
    // terceiro termo: f''(0)/2 * x^2 = 2sec2(0)tan(0)/2 = 0
    // quarto termo: f'''(0)/6 * x^3 = (4sec2(0)tan2(0) + 2sec4(x))/6 = 1/3
    // quinto termo: f''''(0)/24 * x^4 = 0
    // sexto termo: f'''''(0)/120 = 2/15

    return (x + x * x * x / 3 + 2 * x * x * x * x * x / 15);
}

/*
    Avalia a tangente de x utilizando a serie de taylor,
    calculando a serie para sen(x) e cos(x) em torno da origem com dois termos,
    e depois dividindo o resultado
*/
double tan2(double x) {
    // como mostrado nos slides:
    // sen(x) -> x - x^3/6
    // cos(x) -> 1 - x^2/2

    return (x - x*x*x/6) / (1-x*x/2);
}