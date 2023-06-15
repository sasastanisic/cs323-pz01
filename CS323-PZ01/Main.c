#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

	char name[30];
	char code[50];
	float price;
	int quantity;

} Product;

void enter_data(Product* product) {
	printf("Name -> ");
	gets(product->name);
	printf("Code -> ");
	gets(product->code);
	printf("Price -> ");
	scanf_s("%f", &product->price);
	printf("Quantity -> ");
	scanf_s("%d", &product->quantity);
}

void welcome_menu() {
	printf("Welcome to shop!\n");
}

int main() {

	welcome_menu();

	int numberOfProducts;

	printf("Enter the number of products: ");
	scanf_s("%d", &numberOfProducts);
	while (getchar() != '\n');

	Product* products = (Product*)malloc(numberOfProducts * sizeof(Product));

	if (products == NULL) {
		printf("Error in allocating memory!\n");
		return 1;
	}

	for (int i = 0; i < numberOfProducts; i++) {
		printf("Product %d:\n", i + 1);
		enter_data(&products[i]);
		while (getchar() != '\n');
	}

	FILE* file = fopen("products.txt", "a");

	if (file == NULL) {
		printf("Error happened!\n");
		return 1;
	}

	for (int i = 0; i < numberOfProducts; i++) {
		fprintf(file, "%s %s %.2f %d\n", products[i].name, products[i].code, products[i].price, products[i].quantity);
	}

	fclose(file);

	FILE* readFile = fopen("products.txt", "r");

	if (readFile == NULL) {
		printf("Error happened!\n");
		return 1;
	}

	printf("Products in our shop are:\n");

	printf("%-30s %-30s %-30s %-10s\n", "Product", "Code", "Price", "Quantity");
	printf("-----------------------------------------------------------------------------------------------------\n");

	while (!feof(readFile)) {
		Product product;
		if (fscanf(readFile, "%s %s %f %d\n", &product.name, &product.code, &product.price, &product.quantity) == 4) {
			printf("%-30s %-30s %-30.2f %-10d\n", product.name, product.code, product.price, product.quantity);
		}
	}

	fclose(readFile);

	free(products);

	// TODO: refactor code, naming convention, divide in smaller functions, add comments

	return 0;
}