#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore AVL
struct Node {
    int id;               // ID do cliente (chave de busca)
    char name[50];        // Nome do cliente
    struct Node *left;
    struct Node *right;
    int height;
};

// Função para criar um novo nó
struct Node* newNode(int id, char name[]) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->id = id;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // novo nó é inicialmente uma folha
    return node;
}

// Função para obter a altura de um nó
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Obter o fator de balanceamento do nó
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int id, char name[]) {
    if (node == NULL)
        return newNode(id, name);

    // Comparação com o ID do nó para decidir a posição na árvore
    if (id < node->id)
        node->left = insert(node->left, id, name);
    else if (id > node->id)
        node->right = insert(node->right, id, name);
    else  // IDs duplicados não são permitidos na árvore AVL
        return node;

    // Atualizar altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter fator de balanceamento
    int balance = getBalance(node);

    // Casos de rotação para balanceamento
    // Caso Esquerda-Esquerda
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para exibir a árvore AVL em ordem
void inOrder(struct Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("ID: %d, Nome: %s, Altura: %i\n", root->id, root->name, root -> height);
        inOrder(root->right);
    }
}

void ReBalance(struct Node* node){
    struct Node* temp;
    int height = 0;
    temp = node;
    while(temp -> right != NULL || temp -> left != NULL){
        if (temp -> right != NULL){
            temp = temp -> right;
        }
        else{
            temp = temp -> left;
        }
        height++;
    }
    node -> height = height + 1;
    if (node -> right != NULL){
        ReBalance(node -> right);
    }
    if (node -> left != NULL){
        ReBalance(node -> left);
    }
}

struct Node* minNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

//Função para remover um nó da árvore
struct Node* deleteUser(struct Node* root, int id) {
    if (root == NULL) {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }
    
    // Procurando o nó a ser removido
    if (id < root->id) {
        root->left = deleteUser(root->left, id);
    } else if (id > root->id) {
        root->right = deleteUser(root->right, id);
    } else {
        // Achamos o nó a ser removido

        // Caso 1: Nó sem filhos (nó folha)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Caso 2: Nó com apenas um filho
        else if (root->left == NULL) { // Tem apenas filho direito
            struct Node* temp = root->right;
            free(root);
            ReBalance(temp);
            // Obter fator de balanceamento
            int balance = getBalance(temp);
        
            // Casos de rotação para balanceamento
            // Caso Esquerda-Esquerda
            if (balance > 1 && id < temp->left->id)
                return rightRotate(temp);
        
            // Caso Direita-Direita
            if (balance < -1 && id > temp->right->id)
                return leftRotate(temp);
        
            // Caso Esquerda-Direita
            if (balance > 1 && id > temp->left->id) {
                temp->left = leftRotate(temp->left);
                return rightRotate(temp);
            }
        
            // Caso Direita-Esquerda
            if (balance < -1 && id < temp->right->id) {
                temp->right = rightRotate(temp->right);
                return leftRotate(temp);
            }
            return temp;
        } else if (root->right == NULL) { // Tem apenas filho esquerdo
            struct Node* temp = root->left;
            free(root);
            ReBalance(temp);
            // Obter fator de balanceamento
            int balance = getBalance(temp);
        
            // Casos de rotação para balanceamento
            // Caso Esquerda-Esquerda
            if (balance > 1 && id < temp->left->id)
                return rightRotate(temp);
        
            // Caso Direita-Direita
            if (balance < -1 && id > temp->right->id)
                return leftRotate(temp);
        
            // Caso Esquerda-Direita
            if (balance > 1 && id > temp->left->id) {
                temp->left = leftRotate(temp->left);
                return rightRotate(temp);
            }
        
            // Caso Direita-Esquerda
            if (balance < -1 && id < temp->right->id) {
                temp->right = rightRotate(temp->right);
                return leftRotate(temp);
            }
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        else {
            // Encontrando o sucessor em ordem (menor nó da subárvore direita)
            struct Node* temp = minNode(root->right);
            
            // Copiando os dados do sucessor para o nó atual
            root->id = temp->id;
            strcpy(root -> name, temp -> name);
            
            // Removendo o sucessor da subárvore direita
            root->right = deleteUser(root->right, temp->id);
            ReBalance(root);
        }
    }
    return root;
}

//Encontra um node baseado na ID
struct Node* busca(struct Node* root, int id){
    if (root == NULL){
        return root;
    }
    
    while(root -> id != id){
        if (root -> id < id && root -> right != NULL){
            root = root -> right;
        }
        else if(root -> id > id && root -> left != NULL){
            root = root -> left;
        }
        else if(root -> left == NULL && root -> right == NULL){
            break;
        }
    }
    
    if (root -> id == id){
        return root;
    }
    else{
        return NULL;
    }
}


// Função principal
int main() {
    struct Node *root = NULL;

    // Inserção de nós como exemplo
    root = insert(root, 10, "Alice");
    root = insert(root, 70, "Grace");
    root = insert(root, 20, "Bob");
    root = insert(root, 50, "Eve");    
    root = insert(root, 30, "Charlie");
    root = insert(root, 40, "Diana");
    root = insert(root, 60, "Frank");

    printf("Árvore AVL em ordem:\n");
    inOrder(root);
    
    deleteUser(root, 50);
    ReBalance(root);
    
    printf("\nÁrvore AVL em ordem pós-deleção:\n");
    inOrder(root);
    
    printf("\n");
    struct Node* buscado = busca(root, 70);
    printf("Node buscado: \nNome: %s, Id: %i\n", buscado -> name, buscado -> id);
    
    buscado = busca(root, 800);
    if (buscado == NULL){
        printf("\nNode de id 800 não encontrado.\n");
    }

    return 0;
}
