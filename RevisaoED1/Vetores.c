#include <stdio.h>

int main() {
    // Declara as variaveis necessárias
    int i, temp, n;
    
    // Obtem input do usuário para o tamanho do vetor, e cria um vetor daquele tamanho
    scanf("%i", &n);
    int vetor[n];
    
    // Preenche o vetor com uma série crescente de numeros baseado em seu tamanho
    for (i = 0; i < n; i++){
        vetor[i] = i;
    }

    // Inverte o vetor
    for (i = 0; i < n/2; i++) {
        // salva o valor de uma posição do vetor
        temp = vetor[i];
        // Substitui o valor daquela posição pelo valor da posição "oposta"
        vetor[i] = vetor[(n - 1) - i];
        // Substitui o valor da posição oposta pelo valor da posição "inicial"
        vetor[(n - 1) - i] = temp;
    }
    
    // Printa o vetor
    printf("Vetor invertido:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}
