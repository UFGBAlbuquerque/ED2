#include <stdio.h>
#include <stdlib.h>

// Cria a estrutura de nodes que compõem a lista duplamente encadeada
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Cria uma variavel que sempre aponta para o começo da lista
Node* head = NULL;

// Insere um número no começo da lista
void insertFront() {
    //declara as variáveis necessárias
    int i = 0, r;
    printf("Insira quantos elementos deseja adicionar à lista: ");
    // Somente aceita numeros positivos.
    while (i <= 0){
        scanf("%i", &i);
    }
    // Insere uma quantia de numeros na lista equivalente àquela ditada pelo usuário
    for (int x = 0; x < i; x++){
        // Obtem o numero
        scanf("%i", &r);
        // Cria um novo node;
        Node* newNode = (Node*)malloc(sizeof(Node));
        // Insere os elementos (o número), e aponta para o antigo primeiro numero como seu vizinho posterior 
        newNode -> data = r;
        newNode -> next = head;
        newNode -> prev = NULL;
        // Muda o antecessor do antigo primeiro para este
        if (head != NULL)
            head -> prev = newNode;
        // muda o vetor que aponta para o primeiro para agora apontar para este
        head = newNode;
    }
}

// Deleta o numero desejado.
void deleteNode(Node* node) {
    // Cuida do caso em que o node é o inicio.
    if (node == head){
        head = node -> next;
    }
    // Cuida do caso em que o sucessor não é NULL
    if (node -> next != NULL){
        node -> next -> prev = node -> prev;
    }
    // Cuida do caso em que on antecessor não é NULL
    if (node -> prev != NULL){
        node -> prev -> next = node -> next;
    }
    // Deleta o node.
    free(node);
}

void printList() {
    // Cria um node que aponta para outros nodes
    Node* temp = head;
    // Faz ele iterar por cada elemento da lista e imprimir cada um deles.
    while (temp != NULL) {
        printf("%d ", temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}

void Encontrar(){
    // Declara variaveis necessárias, e cria um node que iterará pela lista, iniciando pelo começo.
    int y;
    Node* r = (Node*)malloc(sizeof(Node));
    r = head;
    // Obtem o numero que deseja ser encontrado
    printf("Insira o numero buscado: ");
    scanf("%i", &y);
    // Um loop que continua até ou o final da lista ou até o numero ser encontrado
    while (r -> next != NULL && r -> data != y){
        if (r -> data != y){
            r = r -> next;
        }
    }
    // Caso o numero tenha sido encontrado, printa o numero
    if (r -> data == y){
        printf("Encontrado, vizinho anterior: ");
        // Cuida do caso em que o vizinho anterior seja NULL
        if (r -> prev == NULL){
            printf("NULL");
        }
        else{
            printf("%i", r -> prev -> data);
        }
        // Cuida do caso em que o vizinho posterior seja NULL
        printf(", vizinho posterior: ");
        if (r -> next == NULL){
            printf("NULL\n");
        }
        else{
            printf("%i\n", r -> next -> data);
        }
    }
    // Caso o numero não tenha sido encontrado, printa "Não encontrado"
    else{
        printf("Não encontrado.\n");
    }
}

// Função main, chama as funções
int main() {
    insertFront();
    printList();
    Encontrar();
    return 0;
}
