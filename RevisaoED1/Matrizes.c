#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    printf("Insira a dimensão da matriz: ");
    scanf("%i", &m);
    n = m;
    int **matriz; 
    matriz = malloc (m * sizeof (int *));
    for (int i = 0; i < m; i++){
        matriz[i] = malloc (n * sizeof (int));   
    }
    int i, j, soma = 0;

    printf("Insira os elementos da matriz %ix%i:\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &matriz[i][j]);
            if (i == j) {
                soma += matriz[i][j];
            }
        }
    }

    printf("Soma dos elementos da diagonal principal: %d\n", soma);
    return 0;
}
