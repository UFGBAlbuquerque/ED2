#include <stdio.h>
#include <stdlib.h>

// Declara a estrutura dos nodes
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Declara a estrutura da fila
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Cria a fila
Queue* createQueue() {
    // Aloca espaço na memória para a fila
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Falha na alocação de memória para a fila.\n");
        return NULL;
    }
    // Cria a fila vazia
    q->front = q->rear = NULL;
    return q;
}

// Adiciona um elemento à fila
void enqueue(Queue* q, int value) {
    // Cria um novo node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Falha na alocação de memória para o novo nó.\n");
        return;
    }
    // Insere os valores desejados neste node
    newNode->data = value;
    newNode->next = NULL;
    // Trata de casos em que não tenham elementos na fila
    if (q->rear == NULL) { 
        q->front = q->rear = newNode;
    } 
    // Trata de casos em que já tenha elementos na fila
    else { 
        q -> rear -> next = newNode;
        q -> rear = newNode;
    }
}

// Retira um elemento da fila
int dequeue(Queue* q) {
    // Verifica se a fila já não está vazia
    if (q -> front == NULL) { 
        printf("Fila está vazia.\n");
        return -1;
    }
    // Cria um node temporário para segurar a posição
    Node* temp = q -> front;
    // Usa uma variável para segurar o valor do node
    int data = temp -> data;
    // move o inicio da fila
    q -> front = q -> front -> next;
    if (q -> front == NULL) {
        q -> rear = NULL;
    }
    // Libera a memória que vai ser retirada
    free(temp);
    // Retorna o valor do node retirado
    return data;
}

// Checa se o inicio da fila está vazio
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Printa a fila
void printQueue(Queue* q) {
    // Verifica se a fila está vazia
    if (isEmpty(q)) {
        printf("A fila está vazia.\n");
        return;
    }
    // usa um node para iterar sobre a fila
    Node* temp = q->front;
    printf("Elementos da fila: ");
    // loop que printa os elementos
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Conta a quantia de elementos na fila
int contar(Queue *q){
    // Node para iterar sobre a fila
    Node *r = q -> front;
    // Verifica se a fila já não está vazia
    if (q -> front == NULL){
        return 0;
    }
    // Variavel que segura o valor
    int c = 1;
    // Loop que itera sobre a fila
    if(r -> next != NULL){
        do{
            c++;
            r = r -> next;
        } while(r -> next != NULL);
        return c;
    }
    // Caso só haja um elemento, retorna 1
    else{
        return 1;
    }
}

// Esvazia a fila
void empty(Queue *q){
    // Node que itera sobre a fila
    Node *r = q -> front;
    // Verifica se a fila já não está vazia
    if (q -> front == NULL){
        printf("A fila já está vazia.\n");
        return;
    }
    // Esvazia a "frente" da fila
    q -> front = NULL;
    Node *temp = r;
    // loop que libera a memória de cada node individualmente
    do{
        Node *temp = r;
        r = r -> next;
        temp -> next = NULL;
        free(temp);
    }while(r != q -> rear);
    // Esvazia o "final" da fila
    q -> rear = NULL;
    free(r);
}

// Função main que chama as funções para demonstrar funcionalidade.
int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);

    int c = contar(q);
    printf("%i\n", c);
    empty(q);
    c = contar(q);
    printf("%i\n", c);

    return 0;
}
