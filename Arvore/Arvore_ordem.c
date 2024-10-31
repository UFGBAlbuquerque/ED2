#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int Id;
    int idade;
    struct Node* esquerda;  // left
    struct Node* direita;   // right
} Node;

// Função para criar um novo nó
Node* createNode(int Id, int idade) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
   
    newNode->Id = Id;
    newNode->idade = idade;
    newNode->esquerda = NULL; // inicializa como NULL
    newNode->direita = NULL;  // inicializa como NULL
    return newNode;
}


// Função para inserir um nó na árvore usando o Id como critério
Node* insertNode(Node* root, int Id, int idade) {
    if (root == NULL) {
        return createNode(Id, idade);
    }
    
    if (idade < root->idade) {
        // Insere à esquerda se o Id é menor que o do nó atual
        root->esquerda = insertNode(root->esquerda, Id, idade);
    } else if (idade > root->idade) {
        // Insere à direita se o Id é maior que o do nó atual
        root->direita = insertNode(root->direita, Id, idade);
    } else {
        // Em caso de empate (mesmo Id), podemos ignorar ou fazer uma reinserção
        printf("Id %d já existe na árvore.\n", Id);
    }
    
    return root;
}



// Função para buscar um usuário pelo ID
Node* buscarID(Node* root, int Id) {
    if (root == NULL || root->Id == Id) {
        return root;
    }
    
    if (Id < root->Id) {
        return buscarID(root->esquerda, Id);
    } else {
        return buscarID(root->direita, Id);
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
Node* deleteUser(Node* root, int Id) {
    if (root == NULL) {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }
    
    // Procurando o nó a ser removido
    if (Id < root->Id) {
        root->esquerda = deleteUser(root->esquerda, Id);
    } else if (Id > root->Id) {
        root->direita = deleteUser(root->direita, Id);
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
            root->idade = temp->idade;
            
            // Removendo o sucessor da subárvore direita
            root->direita = deleteUser(root->direita, temp->Id);
        }
    }
    return root;
}

// Função para exibir a árvore em ordem decrescente de idade
void exibirEmOrdem(Node* root) {
    if (root != NULL) {
        exibirEmOrdem(root->esquerda);  // Visita a subárvore esquerda
        printf("ID: %d, Idade: %d\n", root->Id, root->idade);  // Imprime o nó atual
        exibirEmOrdem(root->direita);   // Visita a subárvore direita
    }
}

void listar(Node* r, int t){
    printf("ID: %i, Idade: %i\n", r -> Id, r -> idade);
    if (r -> esquerda != NULL){
        listar(r -> esquerda, t);
    }
    if (r -> direita != NULL){
        listar(r -> direita, t);
    }
}

// Função para exibir a árvore no percurso pré-ordem
void exibirPreOrdem(Node* root) {
    
    Node* q;
    q = root;
    printf("configuracao da arvore pre-ordem: \n");
    while (q -> direita != NULL){
        q = q -> direita;
    }
    listar(root, q -> idade);
    printf("\n");
}

void Enumerar(Node* r){
    if (r -> esquerda != NULL){
        Enumerar(r -> esquerda);
    }
    if (r -> direita != NULL){
        Enumerar(r -> direita);
    }
    printf("ID: %i, Idade: %i\n", r -> Id, r -> idade);
}

// Função para exibir a árvore no percurso pós-ordem
void exibirPosOrdem(Node* root) {
    printf("configuracao da arvore pos-ordem: \n");
    Enumerar(root);
    printf("\n");
}

// Função principal
int main() {
    Node* root = NULL;
    
    // Inserindo usuários
    root = insertNode(root, 101, 50);
    root = insertNode(root, 102, 40);
    root = insertNode(root, 103, 20);
    root = insertNode(root, 104, 30);
    root = insertNode(root, 105, 70);

    // Exibindo usuários em ordem
    printf("Usuários em ordem de idade:\n");
    exibirEmOrdem(root);
    printf("\n");
    exibirPosOrdem(root);
    exibirPreOrdem(root);
    

    // Removendo um usuário
    root = deleteUser(root, 105);
    printf("\nApós remoção do usuário:\n");
    exibirEmOrdem(root);
    printf("\n");
    exibirPosOrdem(root);
    exibirPreOrdem(root);

    return 0;
}
