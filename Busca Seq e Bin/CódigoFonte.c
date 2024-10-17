#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 1000  // Número de produtos
#define MAX_NAME_LENGTH 50 // Tamanho máximo do nome do produto

// Estrutura que representa um produto no e-commerce
typedef struct {
    int id;                  // ID único do produto
    char name[MAX_NAME_LENGTH];  // Nome do produto
    float price;             // Preço do produto
} Product;

// Lista de nomes de produtos reais para e-commerce
const char *productNames[] = {
    "Smartphone Samsung Galaxy",
    "Notebook Dell Inspiron",
    "Geladeira Brastemp Frost Free",
    "Cafeteira Nespresso",
    "Fritadeira Airfryer Mondial",
    "TV LED 50 Polegadas LG",
    "Console Playstation 5",
    "Headset Gamer HyperX",
    "Máquina de Lavar Electrolux",
    "Ventilador Arno Turbo",
    "Teclado Mecânico Razer",
    "Impressora Multifuncional HP",
    "Relógio Smartwatch Apple",
    "Câmera DSLR Canon",
    "Micro-ondas Panasonic",
    "Bicicleta Caloi Aro 29",
    "Perfume Chanel No 5",
    "Sapato Social Masculino",
    "Bolsa Feminina de Couro",
    "Óculos de Sol Ray-Ban"
};

// Função para gerar um nome de produto aleatório a partir da lista predefinida
void generateProductName(char *name) {
    int index = rand() % (sizeof(productNames) / sizeof(productNames[0]));
    strncpy(name, productNames[index], MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0'; // Garante que a string termina corretamente
}

// Função para gerar uma lista de produtos com preços aleatórios
void generateProductList(Product products[], int numProducts) {
    for (int i = 0; i < numProducts; ++i) {
        products[i].id = i + 1; // ID sequencial
        generateProductName(products[i].name); // Nome aleatório
        products[i].price = (rand() % 10000) / 100.0; // Preço aleatório entre $0 e $100
    }
}

// Função para imprimir um produto
void printProduct(Product product) {
    printf("ID: %d, Nome: %s, Preço: $%.2f\n", product.id, product.name, product.price);
}

// Função para imprimir a lista de produtos
void printProductList(Product products[], int numProducts) {
    printf("\nLista de produtos gerados:\n");
    for (int i = 0; i < numProducts; ++i) {
        printProduct(products[i]);
    }
}

// Espaço para implementar a busca sequencial
int sequentialSearch(Product products[], int numProducts, const char* target) {
    
	for (int i = 0; i < numProducts; i++){
	    if (strcmp(products[i].name, target) == 0){
	        return i;
	    }
	}
    
	return -1; // Produto não encontrado (modificar conforme a implementação)
}

// Espaço para implementar a busca binária
int binarySearch(Product products[], int low, int high, const char* target) {
    
    while((high - low) != 1){
    	int mid = (high + low)/2;
    	if (strcmp(products[mid].name, target) == 0){
    	    return mid;
    	}
    	else if (strcmp(products[mid].name, target) < 0){
    	    low = mid;
    	}
    	else{
    	    high = mid;
    	}
    } 
    
    if ((high - low) == 1){
        if(strcmp(products[low + 1].name, target) == 0){
            return low + 1;
        }
    }
	
    return -1; // Produto não encontrado (modificar conforme a implementação)
}

int compareByName(const void* a, const void* b) {
    Product* productA = (Product*)a;
    Product* productB = (Product*)b;
    return strcmp(productA->name, productB->name);
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios
    clock_t t;
    double time_taken;

    Product products[MAX_PRODUCTS]; // Array de produtos
    int numProducts = MAX_PRODUCTS; // Quantidade de produtos a serem gerados
    
    // Gera a lista de produtos
    generateProductList(products, numProducts);
    
    // Imprime a lista de produtos
    printProductList(products, 10); // Exibe apenas os 10 primeiros produtos

    // Define o produto alvo para busca
    char target[MAX_NAME_LENGTH] = "Notebook Dell Inspiron";

    // Espaço para realizar a busca sequencial
    printf("\nBusca sequencial pelo produto '%s':\n", target);
    t = clock();
    int seqResult = sequentialSearch(products, numProducts, target);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    if (seqResult != -1) {
        printf("Produto encontrado na posição %d:\n", seqResult);
        printProduct(products[seqResult]);
        printf("Tempo levado: %fms\n", time_taken);
    } else {
        printf("Produto não encontrado na busca sequencial.\n");
        printf("Tempo levado: %fms\n", time_taken);
    }

	// Ordenar a lista de produtos por nome usando qsort
    // A função qsort é nativa da biblioteca <stdlib.h>
	qsort(products, MAX_PRODUCTS, sizeof(Product), compareByName);

    // Espaço para o realizar a busca binária
    printf("\nBusca binária pelo produto '%s':\n", target);
    t = clock();
    int binResult = binarySearch(products, 0, numProducts - 1, target);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    if (binResult != -1) {
        printf("Produto encontrado na posição %d:\n", binResult);
        printProduct(products[binResult]);
        printf("Tempo levado: %fms\n", time_taken);
    } else {
        printf("Produto não encontrado na busca binária.\n");
        printf("Tempo levado: %fms\n", time_taken);
    }
    

    return 0;
}
