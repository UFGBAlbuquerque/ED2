#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int Id;
    int curtidas;
    int num_comentários;
    int tot_inter;
    struct Node* esquerda;  // left
    struct Node* direita;   // right
} Node;

// Função para criar um novo nó
Node* createNode(int Id, int curtidas, int num_comentários, int tot_inter) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
   
    newNode->Id = Id;
    newNode->curtidas = curtidas;
    newNode->num_comentários = num_comentários;
    newNode->tot_inter = tot_inter;
    newNode->esquerda = NULL; // inicializa como NULL
    newNode->direita = NULL;  // inicializa como NULL
    return newNode;
}


// Função para inserir um nó na árvore usando o Id como critério
Node* insertNode(Node* root, int Id, int curtidas, int num_comentários, int tot_inter) {
    if (root == NULL) {
        return createNode(Id, curtidas, num_comentários, tot_inter);
    }
    
    if (tot_inter < root->tot_inter) {
        // Insere à esquerda se o Id é menor que o do nó atual
        root->esquerda = insertNode(root->esquerda, Id, curtidas, num_comentários, tot_inter);
    } else if (tot_inter > root->tot_inter) {
        // Insere à direita se o Id é maior que o do nó atual
        root->direita = insertNode(root->direita, Id, curtidas, num_comentários, tot_inter);
    }
    
    return root;
}

// Função para buscar um usuário pelo ID
Node* buscarID(Node* root, int tot_inter) {
    if (root == NULL || root->tot_inter == tot_inter) {
        printf("Id encontrado.\n");
        return root;
    }
    
    if (tot_inter < root->tot_inter) {
        return buscarID(root->esquerda, tot_inter);
    } else {
        return buscarID(root->direita, tot_inter);
    }
}

// Função para encontrar o menor nó (usado na remoção)
Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->esquerda != NULL) {
        current = current->esquerda;
    }
    return current;
}

// Função para remover um usuário pelo ID
Node* deleteUser(Node* root, int tot_inter) {
    if (root == NULL) {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }
    
    // Procurando o nó a ser removido
    if (tot_inter < root->tot_inter) {
        root->esquerda = deleteUser(root->esquerda, tot_inter);
    } else if (tot_inter > root->tot_inter) {
        root->direita = deleteUser(root->direita, tot_inter);
    } else {
        // Achamos o nó a ser removido

        // Caso 1: Nó sem filhos (nó folha)
        if (root->esquerda == NULL && root->direita == NULL) {
            free(root);
            return NULL;
        }
        
        // Caso 2: Nó com apenas um filho
        else if (root->esquerda == NULL) { // Tem apenas filho direito
            Node* temp = root->direita;
            free(root);
            return temp;
        } else if (root->direita == NULL) { // Tem apenas filho esquerdo
            Node* temp = root->esquerda;
            free(root);
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        else {
            // Encontrando o sucessor em ordem (menor nó da subárvore direita)
            Node* temp = minNode(root->direita);
            
            // Copiando os dados do sucessor para o nó atual
            root->Id = temp->Id;
            root->curtidas = temp->curtidas;
            root->num_comentários =temp-> num_comentários;
            root->tot_inter = temp->tot_inter;
            
            // Removendo o sucessor da subárvore direita
            root->direita = deleteUser(root->direita, temp->Id);
        }
    }
    return root;
}


Node* atualizar(Node* root, int Id, int curtidas, int num_comentários){
    if (root == NULL || root->tot_inter == (curtidas + num_comentários)) {
        return root;
    }
    if (Id < root->tot_inter) {
        return atualizar(root->esquerda, Id, curtidas, num_comentários);
    } else if (Id > root->tot_inter){
        return atualizar(root->direita, Id, curtidas, num_comentários);
    }
    else{
        root->curtidas += curtidas;
        root->num_comentários += num_comentários;
        root->tot_inter += (curtidas + num_comentários);
        printf("Dados atualizados com sucesso\n");
        return root;
    }
}

void exibirDecrescente(Node* root) {
    if (root != NULL) {
        exibirDecrescente(root->direita);  // Visita a subárvore esquerda
        printf("ID: %i, curtidas: %i, comentários: %i, total de interações: %i\n", root -> Id, root -> curtidas, root -> num_comentários, root -> tot_inter); // Imprime o nó atual
        exibirDecrescente(root->esquerda);   // Visita a subárvore direita
    }
}

// Função principal
int main() {
    Node* root = NULL;
    
    // Inserindo usuários
    root = insertNode(root, 101, 50, 30, 80);
    root = insertNode(root, 102, 40, 10, 50);
    root = insertNode(root, 103, 60, 25, 85);

    // Exibindo usuários em ordem
    exibirDecrescente(root);
    printf("\n");
    
    atualizar(root, 80, 10, 5);
    deleteUser(root, 50);

    exibirDecrescente(root);
    printf("\n");
    return 0;
}
