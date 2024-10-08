#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar um produto
typedef struct {
	int indiciePopularidade;               // indiciePopularidade
	float Preco;          // preo do produto
	char nome[100];       // nome do produto
	char categoria[20];      // categoria do produto
	int Disponibilidade;     // Disponibilidade do Produto
	int ocupada;          // Flag para indicar se o slot está ocupado
} Produto;

// Estrutura da Tabela Hash
typedef struct {
	Produto tabela[TAMANHO_HASH];  // Array de produtos
} TabelaHash;

// Função Hash: Retorna o Índice baseado no ID da transação
int funcao_hash(char *nome) {
	int soma = 0;
	for (int i = 0; nome[i] != '\0'; i++) {
		soma += nome[i];
	}
	return soma % TAMANHO_HASH;
	// Usa nome para determinar índice na tabela
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

	return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o Índice ou -1 se a tabela estiver cheia
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

	return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o Índice ou -1 se a tabela estiver cheia
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

	return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o Índice ou -1 se a tabela estiver cheia
}

// Função para criar um novo produto
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

// Função para inserir um produto na tabela hash usando sondagem linear
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

// Função para inserir um produto na tabela hash usando sondagem quadrática
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

// Função para inserir um produto na tabela hash usando duplo hashing
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

// Função para exibir todos os produtos
void exibir_todas(TabelaHash *tabela) {
	for (int i = 0; i < TAMANHO_HASH; i++) {
		if (tabela -> tabela[i].ocupada) {
			printf("Produto indiciePopularidade: %d, Preco: %.2f, nome: %s, categoria: %s, Disponibilidade: %i (Índice: %d)\n",
			       tabela->tabela[i].indiciePopularidade, tabela->tabela[i].Preco, tabela->tabela[i].nome, tabela->tabela[i].categoria, tabela->tabela[i].Disponibilidade, i);
		}
	}
}


// Funções de busca
int buscar_linear(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o índice para busca
	Produto produto = tabela -> tabela[indice];
	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			return indice;
		}
	}
	return -1;  // Retorna NULL se não for encontrada
}

int buscar_duploHashing(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o Índice para busca
	Produto produto = tabela -> tabela[indice];
	if (tabela -> tabela[indice].ocupada != 0) { // Garante que a localização do indície não está nula ou ocupada por outra memória não desejada
		if (produto.indiciePopularidade == indiciePopularidade) {
			return indice;
		}
	}
    // Caso não tenha sido encontrado tenta a segunda função de hashing 
	indice = hash2(indiciePopularidade);
	produto = tabela -> tabela[indice];
	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			return indice;
		}
	}

	return -1;  // Retorna NULL se não for encontrada
}

int buscar_quadratica(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o Índice para busca
	Produto produto = tabela -> tabela[indice];
	int i = 1, tentativas = 0;
	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			return indice;
		}
	}
	// Caso não tenha sido encontrado, busca por ele por sondagem quadrática.
	else {
		while (produto.indiciePopularidade != indiciePopularidade && tentativas < TAMANHO_HASH) {
			indice = (funcao_hash(nome) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
			produto = tabela -> tabela[indice];
			i++;
			tentativas++;
		}
		if (tabela -> tabela[indice].ocupada != 0) {
			if (produto.indiciePopularidade == indiciePopularidade) {
				return indice;
			}
		}
	}
	return -1;  // Retorna NULL se não for encontrada
}

// Funções de exclusão
int exclusao_linear(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o Índice para busca
	Produto produto = tabela -> tabela[indice];

	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			tabela -> tabela[indice].ocupada = 0; // Assinala que a posição não está ocupada, impedindo de ser imprimida
			return 1;
		}
	}

	return -1;  // Retorna NULL se não for encontrada
}

int exclusao_duploHashing(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o Índice para busca
	Produto produto = tabela -> tabela[indice];

	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			tabela -> tabela[indice].ocupada = 0;
			return 1;
		}
	}

	indice = hash2(indiciePopularidade);
	produto = tabela -> tabela[indice];

	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			tabela -> tabela[indice].ocupada = 0;
			return 1;
		}
	}

	return -1;  // Retorna NULL se não for encontrada
}

int exclusao_quadratica(TabelaHash *tabela, char *nome, int indiciePopularidade) {
	int indice = funcao_hash(nome);  // Calcula o Índice para busca
	Produto produto = tabela -> tabela[indice];
	int i = 1, tentativas = 0;
	if (tabela -> tabela[indice].ocupada != 0) {
		if (produto.indiciePopularidade == indiciePopularidade) {
			tabela -> tabela[indice].ocupada = 0;
			return 1;
		}
	}
	else {
		while (produto.indiciePopularidade != indiciePopularidade && tentativas < TAMANHO_HASH) {
			indice = (funcao_hash(nome) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
			produto = tabela -> tabela[indice];
			i++;
			tentativas++;
		}
		if (tabela -> tabela[indice].ocupada != 0) {
			if (produto.indiciePopularidade == indiciePopularidade) {
				tabela -> tabela[indice].ocupada = 0;
				return 1;
			}
		}
	}
	return -1;  // Retorna NULL se não for encontrada
}

// Função principal para demonstrar o uso da tabela hash com sondagem
int main() {
	// Inicializa a tabela hash
	TabelaHash tabela_linear = {0};  // Todos os slots começam desocupados
	int indice, sucesso;

	// Inserir transações na tabela hash usando sondagem linear
	printf("\nInserção com Sondagem Linear:\n");
	inserir_linear(&tabela_linear, criar_produto(1, 10000.50, "Geladeira Smart Sony T-300X Deluxe", "Eletrodomesticos", 35));
	inserir_linear(&tabela_linear, criar_produto(2, 250.75, "Carregador Samsung 220V Long Cable saída 3.16A", "Perifericos", 990));
	inserir_linear(&tabela_linear, criar_produto(3, 50000.00, "MacBook Air Pro 2000", "Notebook", 5));
	inserir_linear(&tabela_linear, criar_produto(4, 1200.00, "Smartphone Motorola Edge 20", "Celulares", 50));
	inserir_linear(&tabela_linear, criar_produto(5, 450.99, "Teclado Mecanico Logitech G413", "Perifericos", 200));
	indice = buscar_linear(&tabela_linear, "Geladeira Smart Sony T-300X Deluxe", 1);
	if (indice != -1) {
		printf("produto encontrado. Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_linear);
    
    // Demonstrando que funções de busca e exclusão funcionam
	printf("Excluindo Geladeira Smart Sony T-300X Deluxe.\n");
	sucesso = exclusao_linear(&tabela_linear, "Geladeira Smart Sony T-300X Deluxe", 1);
	if (sucesso != -1) {
		printf("Produto excluido.\n");
	}
	else {
		printf("Houve uma falha na exclusão.\n");
	}
	indice = buscar_linear(&tabela_linear, "Geladeira Smart Sony T-300X Deluxe", 1);
	if (indice != -1) {
		printf("produto encontrado.Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_linear);

	// Inserir transações na tabela hash usando sondagem quadrática
	printf("\nInserção com Sondagem Quadrática:\n");
	TabelaHash tabela_quadratica = {0};
	inserir_quadratica(&tabela_quadratica, criar_produto(6, 3000.50, "Impressora HP DeskJet 2676", "Impressoras", 15));
	inserir_quadratica(&tabela_quadratica, criar_produto(7, 900.45, "Monitor LG UltraWide 29", "Monitores", 30));
	inserir_quadratica(&tabela_quadratica, criar_produto(8, 1250.60, "Câmera Canon EOS M50", "Câmeras", 8));
	inserir_quadratica(&tabela_quadratica, criar_produto(9, 800.00, "Fone de Ouvido Sony WH-1000XM4", "Áudio", 100));
	inserir_quadratica(&tabela_quadratica, criar_produto(10, 200.90, "Mouse Razer DeathAdder V2", "Periféricos", 250));
	indice = buscar_quadratica(&tabela_quadratica, "Impressora HP DeskJet 2676", 6);
	if (indice != -1) {
		printf("produto encontrado. Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_quadratica);
    
    // Demonstrando que funções de busca e exclusão funcionam
	printf("Excluindo Impressora HP DeskJet 2676.\n");
	sucesso = exclusao_quadratica(&tabela_quadratica, "Impressora HP DeskJet 2676", 6);
	if (sucesso != -1) {
		printf("Produto excluido.\n");
	}
	else {
		printf("Houve uma falha na exclusC#o.\n");
	}
	indice = buscar_quadratica(&tabela_quadratica, "Impressora HP DeskJet 2676", 6);
	if (indice != -1) {
		printf("produto encontrado. Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_quadratica);

	// Inserir transações na tabela hash usando duplo hashing
	printf("\nInserção com Duplo Hashing:\n");
	TabelaHash tabela_duplo = {0};
	inserir_duplo_hashing(&tabela_duplo, criar_produto(11, 1750.30, "Notebook Dell Inspiron 15", "Notebooks", 12));
	inserir_duplo_hashing(&tabela_duplo, criar_produto(12, 3200.75, "TV 4K Samsung 55", "Eletrônicos", 25));
	inserir_duplo_hashing(&tabela_duplo, criar_produto(13, 600.40, "Projetor Epson Home Cinema", "Projetores", 7));
	inserir_duplo_hashing(&tabela_duplo, criar_produto(14, 1800.99, "Console Xbox Series S", "Games", 20));
	inserir_duplo_hashing(&tabela_duplo, criar_produto(15, 999.00, "Tablet Apple iPad Air", "Tablets", 10));
	indice = buscar_duploHashing(&tabela_duplo, "TV 4K Samsung 55", 12);
	if (indice != -1) {
		printf("produto encontrado. Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_duplo);

    // Demonstrando que funções de busca e exclusão funcionam
	printf("Excluindo TV 4K Samsung 55.\n");
	sucesso = exclusao_duploHashing(&tabela_duplo, "TV 4K Samsung 55", 12);
	if (sucesso != -1) {
		printf("Produto excluido.\n");
	}
	else {
		printf("Houve uma falha na exclusão.\n");
	}
	indice = buscar_duploHashing(&tabela_duplo, "TV 4K Samsung 55", 12);
	if (indice != -1) {
		printf("produto encontrado. Índice: %i\n", indice);
	}
	else {
		printf("Produto não encontrado.\n");
	}
	printf("Exibindo todos os produtos.\n");
	exibir_todas(&tabela_duplo);

	return 0;
}
