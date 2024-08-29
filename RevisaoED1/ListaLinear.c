#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

void inserir(int elemento) {
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento;
    } else {
        printf("Lista cheia!\n");
    }
}

void remover(int index) {
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n");
    } else {
        for (int i = index; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
    }
}

void imprimir() {
    printf("Elementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

void buscar(int elemento){
    int r, a = 0;
    for (r = 0; r < tamanho; r++){
        if (lista[r] == elemento){
            printf("Posição: %i\n", r);
            a++;
        }
    }
    if (a == 0){
        printf("Elemento não encontrado\n");
    }
}

void maximo(){
    int r, m;
    m = lista[0];
    for (r = 0; r < tamanho; r++){
        if (lista[r] > m){
            m = lista[r];
        }
    }
    printf("Tamanho máximo: %i\n", m);
}

void minimo(){
    int r, m;
    m = lista[0];
    for (r = 0; r < tamanho; r++){
        if (lista[r] < m){
            m = lista[r];
        }
    }
    printf("Tamanho minimo: %i\n", m);
}

void ordenar(){
    int r, o, i, temp;
    for(r = 0; r < tamanho; r++){
        o = lista[r];
        for (i = r + 1; i < tamanho; i++){
            if (lista[i] < o){
                temp = lista[i];
                lista[i] = o;
                lista[r] = temp;
                o = temp;
            }
        }
    }
}

int main() {
    inserir(10);
    inserir(20);
    inserir(30);
    inserir(15);
    buscar(20);
    buscar(15);
    minimo();
    maximo();
    imprimir();
    ordenar();
    imprimir();
    buscar(20);
    buscar(15);
    minimo();
    maximo();
    remover(1);
    imprimir();
    return 0;
}
