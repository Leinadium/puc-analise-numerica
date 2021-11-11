#include <stdio.h>
#include <math.h>
#include "integral.h"
#define PI 3.1415926535897932

double f(double x){
	return cos(x) - (2*sin(x));
}
double f_derivada(double x){
	return -sin(x) - (2*cos(x));
}

double f1(double x){
	return x/(sqrt(x*x+9));
}

double f2(double x){
	return x*x*log(x);
}

double f3(double x){
	return x*x*sin(x);
}

int main(void) {

  printf("Teste a: \n");
	for(int n =2;n<7;n++){
		double res_verdadeiro_d = f_derivada(PI/4);
		double h = 1;
		double resultado_d = derivada (n, f, PI/4, h);
		printf("n = %d, h = %0.16lf\n", n, h);
		printf("\nderivada = %0.16lf\n resposta certa = %0.16lf\n~~~~~~~~~~~~~~~~~~~~~\n",resultado_d,res_verdadeiro_d);
		h = 0.1;
		resultado_d = derivada (n, f, PI/4, h);
		printf("n = %d, h = %0.16lf\n", n, h);
		printf("\nderivada = %0.16lf\n resposta certa = %0.16lf\n~~~~~~~~~~~~~~~~~~~~~\n",resultado_d,res_verdadeiro_d);
		h = 0.01;
		resultado_d = derivada (n, f, PI/4, h);
		printf("n = %d, h = %0.16lf\n", n, h);
		printf("\nderivada = %0.16lf\n resposta certa = %0.16lf\n~~~~~~~~~~~~~~~~~~~~~\n",resultado_d,res_verdadeiro_d);
		h = 0.001;
		resultado_d = derivada (n, f, PI/4, h);
		printf("n = %d, h = %0.16lf\n", n, h);
		printf("\nderivada = %0.16lf\n resposta certa = %0.16lf\n~~~~~~~~~~~~~~~~~~~~~\n",resultado_d,res_verdadeiro_d);
	}
	printf("Teste b:\n");
	printf("\nprimeira função:\n resposta certa: 2.0 \n");
	double res_T_16 = trapezio (f1, 0, 4, 16);
	double res_T_32 = trapezio (f1, 0, 4, 32);
	double res_S_16 = simpson (f1, 0, 4, 16);
	double res_S_32 = simpson (f1, 0, 4, 32);
	printf("\ntrapézio com n = 16 : %0.16lf\n",res_T_16);
	printf("trapézio com n = 32 : %0.16lf\n",res_T_32);
	printf("simpson com n = 16 : %0.16lf\n",res_S_16);
	printf("simpson com n = 32 : %0.16lf\n",res_S_32);

	printf("\nsegunda função:\n resposta certa: 6.9986217091241\n");
	res_T_16 = trapezio (f2, 1, 3, 16);
	res_T_32 = trapezio (f2, 1, 3, 32);
	res_S_16 = simpson (f2, 1, 3, 16);
	res_S_32 = simpson (f2, 1, 3, 32);
	printf("\ntrapézio com n = 16 : %0.16lf\n",res_T_16);
	printf("trapézio com n = 32 : %0.16lf\n",res_T_32);
	printf("simpson com n = 16 : %0.16lf\n",res_S_16);
	printf("simpson com n = 32 : %0.16lf\n",res_S_32);

	printf("\nterceira função:\n resposta certa:  5.8696044010894\n");
	res_T_16 = trapezio (f3, 0, PI, 16);
	res_T_32 = trapezio (f3, 0, PI, 32);
	res_S_16 = simpson (f3, 0, PI, 16);
	res_S_32 = simpson (f3, 0, PI, 32);
	printf("\ntrapézio com n = 16 : %0.16lf\n",res_T_16);
	printf("trapézio com n = 32 : %0.16lf\n",res_T_32);
	printf("simpson com n = 16 : %0.16lf\n",res_S_16);
	printf("simpson com n = 32 : %0.16lf\n",res_S_32);

  return 0;
}