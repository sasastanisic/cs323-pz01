#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_NUM 2

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

	Product product[PRODUCT_NUM];

	printf("Enter data for %d products:\n", PRODUCT_NUM);
	for (int i = 0; i < PRODUCT_NUM; i++) {
		printf("Product %d:\n", i + 1);
		enter_data(&product[i]);
		while (getchar() != '\n');
	}

	return 0;
}