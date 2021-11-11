#ifndef MATRIZ_H
#define MATRIZ_H

// cria (aloca) um vetor de dimensão n, retornando seu ponteiro
double* criavet (int n);

// libera (a memória) de um vetor previamente criado
void liberavet (double* v);

// cria (aloca) uma matriz de dimensão m x n, retornando seu ponteiro;
// a matriz é representado por vetor de vetores linha
double** criamat (int m, int n);

// cria (aloca) uma matriz triangular inferior de dimensão n x n;
// a matriz é representado por vetor de vetores linha:
// o primeiro vetor linha tem dimensão 1, o segundo 2, e assim por diante
double** criamattri (int n);

// libera (a memória) de uma matriz previamente criada
void liberamat (int m, double** A);

#endif
