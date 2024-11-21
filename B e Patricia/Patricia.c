#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da Árvore Patricia
typedef struct PatriciaNode {
    char *key;                     // Chave armazenada (parte da palavra ou palavra inteira)
    int isEndOfWord;               // Indica se é o final de uma palavra
    struct PatriciaNode *left;     // Subárvore à esquerda
    struct PatriciaNode *right;    // Subárvore à direita
} PatriciaNode;

// Função para criar um novo nó
PatriciaNode* createNode(const char *key, int isEndOfWord) {
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->key = strdup(key); // Copia a chave
    node->isEndOfWord = isEndOfWord;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para encontrar o primeiro índice onde duas strings divergem
int findMismatchIndex(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

// Função para inserir uma palavra na Árvore Patricia
PatriciaNode* insertPatricia(PatriciaNode *root, const char *word) {
    if (!root) {
        return createNode(word, 1); // Novo nó para a palavra
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Caso 1: A palavra é um prefixo do nó atual
    if (mismatchIndex == strlen(root->key)) {
        // Se a palavra é igual ao prefixo, marcamos o nó como fim de palavra
        if (mismatchIndex == strlen(word)) {
            root->isEndOfWord = 1;
        } else {
            // Inserir o restante da palavra na subárvore direita
            root->right = insertPatricia(root->right, word + mismatchIndex);
        }
        return root;
    }

    // Caso 2: O nó atual é um prefixo da palavra
    if (mismatchIndex == strlen(word)) {
        // Criar um novo nó com a palavra
        PatriciaNode *newNode = createNode(word, 1);
        newNode->right = root;
        return newNode;
    }

    // Caso 3: Há uma divergência (split)
    PatriciaNode *splitNode = createNode(root->key + mismatchIndex, root->isEndOfWord);
    splitNode->left = root->left;
    splitNode->right = root->right;

    // Modificar o nó atual para armazenar apenas o prefixo comum
    char *tempKey = strdup(root->key); // Salva a chave original
    tempKey[mismatchIndex] = '\0'; // Divide a chave do nó atual
    root->key = tempKey;
    root->isEndOfWord = 0;
    root->left = splitNode;
    root->right = createNode(word + mismatchIndex, 1);

    return root;
}

// Função para buscar uma palavra na Árvore Patricia
int searchPatricia(PatriciaNode *root, const char *word) {
    if (!root) {
        return 0; // Palavra não encontrada
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Caso 1: A palavra é um prefixo do nó atual
    if (mismatchIndex == strlen(word)) {
        return root->isEndOfWord;
    }

    // Caso 2: Continuar na subárvore direita
    if (mismatchIndex == strlen(root->key)) {
        return searchPatricia(root->right, word + mismatchIndex);
    }

    return 0; // Palavra não encontrada
}

// Função para exibir as palavras na Árvore Patricia
void printPatricia(PatriciaNode *root, char *buffer, int depth) {
    if (!root) {
        return;
    }

    // Copiar a chave atual no buffer
    strncpy(buffer + depth, root->key, strlen(root->key));
    depth += strlen(root->key);

    // Se for o fim de uma palavra, imprimir a palavra
    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    // Recursão para as subárvores
    printPatricia(root->left, buffer, depth);
    printPatricia(root->right, buffer, depth);
}

// Função principal para testar a Árvore Patricia
int main() {
    PatriciaNode *root = NULL;
    char buffer[100]; // Buffer para exibição das palavras

    // Exemplo inserção de palavras
    root = insertPatricia(root, "carro");
    root = insertPatricia(root, "car");
    root = insertPatricia(root, "cat");
    root = insertPatricia(root, "dog");
    root = insertPatricia(root, "cart");

    // Busca de palavras
    printf("Busca por 'car': %s\n", searchPatricia(root, "car") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'dog': %s\n", searchPatricia(root, "dog") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'bat': %s\n", searchPatricia(root, "bat") ? "Encontrada" : "Não encontrada");

    // Exibir todas as palavras
    printf("\nPalavras na árvore:\n");
    printPatricia(root, buffer, 0);

    return 0;
}
