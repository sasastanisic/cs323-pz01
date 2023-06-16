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

void enter_product_data(Product* product) {
	printf("Name -> ");
	gets(product->name);
	printf("Code -> ");
	gets(product->code);
	printf("Price -> ");
	scanf_s("%f", &product->price);
	printf("Quantity -> ");
	scanf_s("%d", &product->quantity);
}

void save_products(Product* products, int number_of_products) {
	FILE* file = fopen("products.txt", "a");

	if (file == NULL) {
		printf("Error happened!\n");
		return;
	}

	for (int i = 0; i < number_of_products; i++) {
		fprintf(file, "%s %s %.2f %d\n", products[i].name, products[i].code, products[i].price, products[i].quantity);
	}

	fclose(file);
}

void read_products() {
	FILE* read_file = fopen("products.txt", "r");

	if (read_file == NULL) {
		printf("Error happened!\n");
		return;
	}

	printf("Products in our shop are:\n");

	printf("%-30s %-30s %-30s %-10s\n", "Product", "Code", "Price", "Quantity");
	printf("-----------------------------------------------------------------------------------------------------\n");

	while (!feof(read_file)) {
		Product product;
		if (fscanf(read_file, "%s %s %f %d\n", product.name, product.code, &product.price, &product.quantity) == 4) {
			printf("%-30s %-30s %-30.2f %-10d\n", product.name, product.code, product.price, product.quantity);
		}
	}

	fclose(read_file);
}

void welcome_menu() {
	printf("Welcome to shop!\n");
}

int main() {

	welcome_menu();

	int number_of_products;

	printf("Enter the number of products: ");
	scanf_s("%d", &number_of_products);
	while (getchar() != '\n');

	Product* products = (Product*)malloc(number_of_products * sizeof(Product));

	if (products == NULL) {
		printf("Error in allocating memory!\n");
		return 1;
	}

	for (int i = 0; i < number_of_products; i++) {
		printf("Product %d:\n", i + 1);
		enter_product_data(&products[i]);
		while (getchar() != '\n');
	}

	save_products(products, number_of_products);

	read_products();

	free(products);

	return 0;
}