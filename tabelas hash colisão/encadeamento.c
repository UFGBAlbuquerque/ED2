#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar um produto
typedef struct Produto {
    int indiciePopularidade;               // indiciePopularidade
    float Preco;          // preço do produto
    char nome[100];       // nome do produto
    char categoria[20];      // categoria do produto
    int Disponibilidade;     // Disponibilidade do Produto
    struct Produto *proximo; // Ponteiro para a próxima transação (lista ligada)
} Produto;

// Estrutura da Tabela Hash
typedef struct {
    Produto *tabela[TAMANHO_HASH];  // Array de ponteiros para o início da lista ligada
} TabelaHash;

// Função Hash: Retorna o índice baseado no indiciePopularidade do Produto
int funcao_hash(char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++){
        soma += nome[i];
    }
    return soma % TAMANHO_HASH;
  // Usa módulo para determinar a posição na tabela
}

// Função para criar um novo Produto
Produto *criar_produto(int indiciePopularidade, float Preco, const char *nome, const char *categoria, int Disponibilidade) {
    Produto *novo_produto = (Produto *)malloc(sizeof(Produto));
    if (novo_produto == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo_produto -> indiciePopularidade = indiciePopularidade;
    novo_produto -> Preco = Preco;
    strcpy(novo_produto -> nome, nome);
    strcpy(novo_produto -> categoria, categoria);
    novo_produto -> Disponibilidade = Disponibilidade;
    novo_produto -> proximo = NULL;
    return novo_produto;
}

// Função para inserir um produto na tabela hash (usando listas ligadas para colisões)
void inserir(TabelaHash *tabela, Produto *produto) {
    int indice = funcao_hash(produto -> nome);  // Calcula o índice baseado no nome
    produto -> proximo = tabela -> tabela[indice];  // Insere no início da lista ligada
    tabela -> tabela[indice] = produto;
}

// Função para exibir todos os produtos
void exibir_todos(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Produto *atual = tabela -> tabela[i];
        while (atual != NULL) {
            printf("Produto indiciePopularidade: %d, Preco: %.2f, nome: %s, categoria: %s, Disponibilidade: %i (Índice: %d)\n",
                   atual -> indiciePopularidade, atual -> Preco, atual -> nome, atual -> categoria, atual  -> Disponibilidade, i);
            atual = atual -> proximo;  // Avança para o próximo produto
        }
    }
}

// Função para buscar um produto na tabela hash pelo indiciePopularidade
Produto *buscar(TabelaHash *tabela, char *nome, int indiciePopularidade) {
    int indice = funcao_hash(nome);  // Calcula o índice para busca
    Produto *atual = tabela -> tabela[indice];
    
    while (atual != NULL) {
        if (atual -> indiciePopularidade == indiciePopularidade) {
            return atual;  // Retorna o produto se encontrado
        }
        atual = atual -> proximo;  // Vai para o próximo produto na lista ligada
    }
    return NULL;  // Retorna NULL se não for encontrada
}

// Função para excluir um produto na tabela hash pelo ID
void excluir(TabelaHash *tabela, char *nome, int indiciePopularidade) {
    int indice = funcao_hash(nome);  // Calcula o índice para exclusão
    Produto *atual = tabela -> tabela[indice];
    Produto *anterior = NULL;

    while (atual != NULL) {
        if (atual -> indiciePopularidade == indiciePopularidade) {
            // Se o elemento a ser removido for o primeiro da lista
            if (anterior == NULL) {
                tabela -> tabela[indice] = atual -> proximo;  // Remove o primeiro elemento
            } else {
                anterior -> proximo = atual -> proximo;  // Remove o elemento no meio ou fim
            }
            free(atual);  // Libera a memória do produto
            printf("Produto com Indicie de popularidade %d foi excluído.\n", indiciePopularidade);
            return;
        }
        anterior = atual;
        atual = atual -> proximo;
    }
    printf("Produto com indiciePopularidade %d não encontrado para exclusão.\n", indiciePopularidade);
}

// Função para contar o número total de elementos (produtos) na tabela hash
int contar_elementos(TabelaHash *tabela) {
    int total = 0;

    // Percorre todas as posições da tabela hash
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Produto *atual = tabela -> tabela[i];

        // Percorre a lista ligada em cada posição
        while (atual != NULL) {
            total++;  // Incrementa o contador para cada produto encontrado
            atual = atual -> proximo;  // Vai para o próximo elemento na lista
        }
    }

    return total;
}


// Função para inserir 20 transações predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela) {
    // Inserindo transações diretamente
    inserir(tabela, criar_produto(1, 10000.50, "Geladeira Smart Sony T-300X Deluxe", "Eletrodomésticos", 35));
    inserir(tabela, criar_produto(2, 250.75, "Carregador Samsung 220V Long Cable Saída 3.16A", "Periféricos", 990));
    inserir(tabela, criar_produto(3, 50000.00, "MacBook Air Pro 2000", "Notebook", 5));
    inserir(tabela, criar_produto(4, 1200.00, "Smartphone Motorola Edge 20", "Celulares", 50));
    inserir(tabela, criar_produto(5, 450.99, "Teclado Mecânico Logitech G413", "Periféricos", 200));
    inserir(tabela, criar_produto(6, 3000.50, "Impressora HP DeskJet 2676", "Impressoras", 15));
    inserir(tabela, criar_produto(7, 900.45, "Monitor LG UltraWide 29", "Monitores", 30));
    inserir(tabela, criar_produto(8, 1250.60, "Câmera Canon EOS M50", "Câmeras", 8));
    inserir(tabela, criar_produto(9, 800.00, "Fone de Ouvido Sony WH-1000XM4", "Áudio", 100));
    inserir(tabela, criar_produto(10, 200.90, "Mouse Razer DeathAdder V2", "Periféricos", 250));
    inserir(tabela, criar_produto(11, 1750.30, "Notebook Dell Inspiron 15", "Notebooks", 12));
    inserir(tabela, criar_produto(12, 3200.75, "TV 4K Samsung 55", "Eletrônicos", 25));
    inserir(tabela, criar_produto(13, 600.40, "Projetor Epson Home Cinema", "Projetores", 7));
    inserir(tabela, criar_produto(14, 1800.99, "Console Xbox Series S", "Games", 20));
    inserir(tabela, criar_produto(15, 999.00, "Tablet Apple iPad Air", "Tablets", 10));
    inserir(tabela, criar_produto(16, 4500.00, "Cadeira Gamer DXRacer", "Mobiliário", 18));
    inserir(tabela, criar_produto(17, 275.60, "Suporte para TV Articulado", "Acessórios", 300));
    inserir(tabela, criar_produto(18, 550.25, "Caixa de Som JBL Flip 5", "Áudio", 150));
    inserir(tabela, criar_produto(19, 1500.00, "Roteador TP-Link Archer C6", "Redes", 40));
    inserir(tabela, criar_produto(20, 700.80, "Bicicleta Aro 26", "Esportes", 5));

    printf("Transações foram inseridas com sucesso.\n");
}


// Função principal para demonstrar o uso da tabela hash com produtos de e-commerce
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Inserir os dados predefinidos na tabela hash
    inserir_dados_predefinidos(&tabela);
    
    // Exibir todas os produtos inseridos
    printf("\nTodos os produtos inseridos: %d\n", contar_elementos(&tabela));
    exibir_todos(&tabela);

    
    // Busca por um produto específico
    printf("\nBuscar um Produto:\n");
    Produto *t = buscar(&tabela, "Geladeira Smart Sony T-300X Deluxe", 1);
    if (t != NULL) {
        printf("Produto encontrado: indiciePopularidade: %d, Preco: %.2f, nome: %s, categoria: %s, Disponibilidade: %i ",
               t -> indiciePopularidade, t -> Preco, t -> nome, t -> categoria, t -> Disponibilidade);
    } else {
        printf("Produto não encontrado.\n");
    }
    
    
    // Excluir os produtos selecionados
    printf("\nProdutos excluidos:\n");
    excluir(&tabela, "Geladeira Smart Sony T-300X Deluxe", 1);
    
    
    // Exibir todos os produtos inseridos
    printf("\nProdutos Atualizados: %d\n", contar_elementos(&tabela));
    exibir_todos(&tabela);
    

    return 0;
}
