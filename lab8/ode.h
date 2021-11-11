double RungeKutta(double t0, double t1, double h, double y0, double (*f)(double t, double y));
double RungeKuttaAcoplado(double t0, double t1, double y0, double (*f)(double t, double y), double tol);

