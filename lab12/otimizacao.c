# include "otimizacao.h"
# include <math.h>


int parar(double x1, double x2, double tol) {
    return ((x2 - x1) / 2.0) <= tol;
}

double calcula_x1(double a, double b, double g) {
    return a + (1 - g) * (b - a);
}

double calcula_x2(double a, double b, double g) {
    return a + g * (b - a);
}

int SecaoAurea(double a, double b, double (*f) (double x), double tol, double *xmin) {
    double golden_ratio = (sqrt(5) - 1) / 2;
    int iter = 0;
    double x1, x2, fx1, fx2;

    x1 = calcula_x1(a, b, golden_ratio);
    x2 = calcula_x2(a, b, golden_ratio);
    fx1 = f(x1);
    fx2 = f(x2);

    while (!parar(x1, x2, tol)) {
        iter ++;
        if (fx1 < fx2) {
            b = x2;
            
            x2 = x1;
            fx2 = fx1;

            x1 = calcula_x1(a, b, golden_ratio);
            fx1 = f(x1);
        }
        else {
            a = x1;

            x1 = x2;
            fx1 = fx2;

            x2 = calcula_x2(a, b, golden_ratio);
            fx2 = f(x2);
        }
    }

    *xmin = (x1 + x2) / 2;
    return iter;
}

int MIPS(double r, double s, double t, double (*f) (double x), double tol, double *xmin) {
    int i = 0;
    double x, fx, fs, fr, ft, den;

    fs = f(s);
    fr = f(r);
    ft = f(t);

    while (1) {
        if (i >= 5) {
            if (fabs(fs - ft) <= tol) {      
                *xmin = (s + t) / 2;
                return i;
            }
            else if (i == 50) {
                return 0;
            }
        }
        i++;

        den = 2 * ((s - r)*(ft - fs) - (fs - fr)*(t - s));
        
        if (den < 1e-10) {
            x = (r + s + t) / 3.0;
        } else {
            x = ((r + s) / 2) - ((fs - fr)*(t - r)*(t - s) / den);
        }
        fx = f(x);
        
        r = s;
        fr = fs;

        s = t;
        fs = ft;

        t = x;
        ft = fx;
    }
}