#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma transação financeira
typedef struct {
    int indiciePopularidade;  // Indicie de popularidade
    float Preco;          // Valor do  Produto
    char nome[100];       // Nome do Produto
    char categoria[20]; // categoria do Produto
    int Disponibilidade;      // Quantas unidades restam
} Produto;

// Estrutura da Tabela Hash
typedef struct {
    Produto *tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar transações
} TabelaHash;

// Função Hash: Retorna o índice baseado no nome do produto
int funcao_hash(char *nome) {
  int soma = 0;
  for (int i = 0; nome[i] != '\0'; i++){
    soma += nome[i];
  }
  return soma % TAMANHO_HASH;
  // Usa módulo para determinar a posição na tabela
}

// Função para inserir um produto na tabela hash
void inserir(TabelaHash *tabela, Produto *produto) {
    int indice = funcao_hash(produto -> nome);  // Calcula o índice baseado no nome
    tabela -> tabela[indice] = produto;  // Insere o produto na tabela
}

// Função para buscar um Produto na tabela hash pelo nome
Produto *buscar(TabelaHash *tabela, char *nome) {
    int indice = funcao_hash(nome);  // Calcula o índice para busca
    return tabela -> tabela[indice];  // Retorna o produto encontrado
}

// Remove um elemento da tabela hash sem considerar conflito
void remover_hash (TabelaHash *tabela, char *nome){
    int indice = funcao_hash(nome);
    tabela -> tabela[indice] = NULL;
}

// Função principal para demonstrar o uso da tabela hash com e-commerce
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Criação de alguns produtos
    Produto produto1 = {1, 10000.50, "Geladeira Smart Sony T-300X Deluxe", "Eletrodomésticos", 35};
    Produto produto2 = {2, 250.75, "Carregador Samsung 220V Long Cable Saída 3.16A", "Periféricos", 990};
    Produto produto3 = {3, 50000.00, "MacBook Air Pro 2000", "Notebook", 5};

    // Insere os produtos na tabela hash
    inserir(&tabela, &produto1);
    inserir(&tabela, &produto2);
    inserir(&tabela, &produto3);

    // Busca por um Produto específico
    Produto *t = buscar(&tabela, "Geladeira Smart Sony T-300X Deluxe");
    if (t != NULL) {
        printf("Produto encontrado: Nome: %s, Preço: %.2f, Indicie de Popularidade: %i, Categoria: %s, Disponibilidade: %i\n",
                 t -> nome, t -> Preco, t -> indiciePopularidade, t -> categoria, t -> Disponibilidade);
    } else {
        printf("Produto não encontrado.\n");
    }

    // Remove elemento
    remover_hash(&tabela, "Carregador Samsung 220V Long Cable Saída 3.16A");
    t = buscar(&tabela, "Carregador Samsung 220V Long Cable Saída 3.16A");
    if (t != NULL) {
        printf("Produto encontrado: Nome: %s, Preço: %.2f, Indicie de Popularidade: %i, Categoria: %s, Disponibilidade: %i\n",
                 t -> nome, t -> Preco, t -> indiciePopularidade, t -> categoria, t -> Disponibilidade);
    } else {
        printf("Produto não encontrado.\n");
    }

    return 0;
}
