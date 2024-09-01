#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 3

//Iinicializa vetor e declata variaveis
int pilha[MAX_SIZE];
int topo = -1, N;

void push(int elemento) {
    if (topo < MAX_SIZE - 1) {
        pilha[++topo] = elemento;
    } 
    else {
        N = topo + 2;
        pilha[N];
        pilha[++topo] = elemento;
;    }
}

// Remove o primeiro elemento
int pop() {
    //verifica se a fila está vazia
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    }
    // Retorna o vetor sem o primeiro item
    else {
        return pilha[topo--];
    }
}

// retorna o primeiro item
int top() {
    // checa se a pilha está vazia
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } 
    // caso contrário retorna o primeiro item
    else {
        return pilha[topo];
    }
}

// Imprime todos os itens do vetor
void imprimir() {
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--) {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

// Checa se a lista está vazia
void Vazia(){
    //caso o topo seja -1, nada foi inserido
    if (topo == -1){
        printf("Está vazia\n");
    }    
    else{
        printf("Não está vazia\n");
    }
}

// Main, chama as funções para demonstrar funcionalidade
int main() {
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);
    imprimir();
    printf("Elemento no topo: %d\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    return 0;
}
