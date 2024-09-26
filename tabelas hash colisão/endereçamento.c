#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma transação financeira
typedef struct {
    int indiciePopularidade;               // indiciePopularidade
    float Preco;          // preço do produto
    char nome[100];       // nome do produto
    char categoria[20];      // categoria do produto
    int Disponibilidade;     // Disponibilidade do Produto
    int ocupada;          // Flag para indicar se o slot está ocupado
} Produto;

// Estrutura da Tabela Hash
typedef struct {
    Produto tabela[TAMANHO_HASH];  // Array de transações
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da transação
int funcao_hash(char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++){
        soma += nome[i];
    }
    return soma % TAMANHO_HASH;
  // Usa módulo para determinar a posição na tabela
}

// Função hash para duplo hashing
int hash2(int indiciePopularidade) {
    return 7 - (indiciePopularidade % 7);  // Segunda função hash para duplo hashing
}

// Sondagem linear
int sondagem_linear(TabelaHash *tabela, char *nome) {
    int indice = funcao_hash(nome);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH;  // Avança linearmente
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Sondagem quadrática
int sondagem_quadratica(TabelaHash *tabela, char *nome) {
    int indice = funcao_hash(nome);
    int i = 1;
    int tentativas = 0;

    while (tabela -> tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(nome) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Duplo hashing
int duplo_hashing(TabelaHash *tabela, char *nome, int indiciePopularidade) {
    int indice = funcao_hash(nome);
    int step = hash2(indiciePopularidade);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH;  // Usa duplo hashing
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Função para criar uma nova transação
Produto criar_produto(int indiciePopularidade, float Preco, const char *nome, const char *categoria, int Disponibilidade) {
    Produto novo_produto;
    novo_produto.indiciePopularidade = indiciePopularidade;
    novo_produto.Preco = Preco;
    strcpy(novo_produto.nome, nome);
    strcpy(novo_produto.categoria, categoria);
    novo_produto.Disponibilidade = Disponibilidade;
    novo_produto.ocupada = 1;  // Marca o slot como ocupado
    return novo_produto;
}

// Função para inserir uma transação na tabela hash usando sondagem linear
void inserir_linear(TabelaHash *tabela, Produto produto) {
    int indice = funcao_hash(produto.nome);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = produto;
    } else {
        // Se houver colisão, chama a sondagem linear
        int novo_indice = sondagem_linear(tabela, produto.nome);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = produto;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma transação na tabela hash usando sondagem quadrática
void inserir_quadratica(TabelaHash *tabela, Produto produto) {
    int indice = funcao_hash(produto.nome);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = produto;
    } else {
        // Se houver colisão, chama a sondagem quadrática
        int novo_indice = sondagem_quadratica(tabela, produto.nome);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = produto;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma transação na tabela hash usando duplo hashing
void inserir_duplo_hashing(TabelaHash *tabela, Produto produto) {
    int indice = funcao_hash(produto.nome);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = produto;
    } else {
        // Se houver colisão, chama o duplo hashing
        int novo_indice = duplo_hashing(tabela, produto.nome, produto.indiciePopularidade);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = produto;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para exibir todas as transações
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i].ocupada) {
            printf("Produto indiciePopularidade: %d, Preco: %.2f, nome: %s, categoria: %s, Disponibilidade: %i (Índice: %d)\n",
                   tabela->tabela[i].indiciePopularidade, tabela->tabela[i].Preco, tabela->tabela[i].nome, tabela->tabela[i].categoria, tabela->tabela[i].Disponibilidade, i);
        }
    }
}


// Função de busca
Produto *buscar_linear(TabelaHash *tabela, char *nome, int indiciePopularidade) {
    int indice = funcao_hash(nome);  // Calcula o índice para busca
    Produto *produto = tabela -> tabela[indice];
    
    if (produto.indiciePopularidade == indiciePopularidade){
        return produto;
    }
    return NULL;  // Retorna NULL se não for encontrada
}

Produto *buscar_duploHashing(TabelaHash *tabela, char *nome, int indiciePopularidade) {
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

Produto *buscar_quadrática(TabelaHash *tabela, char *nome, int indiciePopularidade) {
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

// Função de exclusão


// Função principal para demonstrar o uso da tabela hash com sondagem
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela_linear = {0};  // Todos os slots começam desocupados

    // Inserir transações na tabela hash usando sondagem linear
    printf("\nInserção com Sondagem Linear:\n");
    inserir_linear(&tabela_linear, criar_produto(1, 10000.50, "Geladeira Smart Sony T-300X Deluxe", "Eletrodomésticos", 35));
    inserir_linear(&tabela_linear, criar_produto(2, 250.75, "Carregador Samsung 220V Long Cable Saída 3.16A", "Periféricos", 990));
    inserir_linear(&tabela_linear, criar_produto(3, 50000.00, "MacBook Air Pro 2000", "Notebook", 5));
    inserir_linear(&tabela_linear, criar_produto(4, 1200.00, "Smartphone Motorola Edge 20", "Celulares", 50));
    inserir_linear(&tabela_linear, criar_produto(5, 450.99, "Teclado Mecânico Logitech G413", "Periféricos", 200));

    exibir_todas(&tabela_linear);

    // Inserir transações na tabela hash usando sondagem quadrática
    printf("\nInserção com Sondagem Quadrática:\n");
    TabelaHash tabela_quadratica = {0};
    inserir_quadratica(&tabela_quadratica, criar_produto(6, 3000.50, "Impressora HP DeskJet 2676", "Impressoras", 15));
    inserir_quadratica(&tabela_quadratica, criar_produto(7, 900.45, "Monitor LG UltraWide 29", "Monitores", 30));
    inserir_quadratica(&tabela_quadratica, criar_produto(8, 1250.60, "Câmera Canon EOS M50", "Câmeras", 8));
    inserir_quadratica(&tabela_quadratica, criar_produto(9, 800.00, "Fone de Ouvido Sony WH-1000XM4", "Áudio", 100));
    inserir_quadratica(&tabela_quadratica, criar_produto(10, 200.90, "Mouse Razer DeathAdder V2", "Periféricos", 250));

    exibir_todas(&tabela_quadratica);

    // Inserir transações na tabela hash usando duplo hashing
    printf("\nInserção com Duplo Hashing:\n");
    TabelaHash tabela_duplo = {0};
    inserir_duplo_hashing(&tabela_duplo, criar_produto(11, 1750.30, "Notebook Dell Inspiron 15", "Notebooks", 12));
    inserir_duplo_hashing(&tabela_duplo, criar_produto(12, 3200.75, "TV 4K Samsung 55", "Eletrônicos", 25));
    inserir_duplo_hashing(&tabela_duplo, criar_produto(13, 600.40, "Projetor Epson Home Cinema", "Projetores", 7));
    inserir_duplo_hashing(&tabela_duplo, criar_produto(14, 1800.99, "Console Xbox Series S", "Games", 20));
    inserir_duplo_hashing(&tabela_duplo, criar_produto(15, 999.00, "Tablet Apple iPad Air", "Tablets", 10));

    exibir_todas(&tabela_duplo);

    return 0;
}
