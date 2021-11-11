void regular (
    int n, double a, double b,
    double (*f) (double x),
    double *xi, double *yi
);

void chebyshev(
    int n, double a, double b, 
    double (*f)(double x), 
    double *xi, double *yi
);

double lagrange(int n, double *xi, double *yi, double x);

