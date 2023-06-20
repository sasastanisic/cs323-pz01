#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6385)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {

	char name[30];
	char code[50];
	float price;
	int quantity;

} Product;

void generate_random_code(char* code, int length) {
	static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int charset_length = sizeof(charset) - 1;

	for (int i = 0; i < length; i++) {
		int index = rand() % charset_length;
		code[i] = charset[index];
	}

	code[length] = '\0';
}

void swap_characters(char* name, char ch1, char ch2) {
	for (int i = 0; name[i] != '\0'; i++) {
		if (name[i] == ch1) {
			name[i] = ch2;
		}
	}
}

void enter_product_data(Product* product) {
	printf("Name -> ");
	gets(product->name);
	swap_characters(product->name, ' ', '_');

	generate_random_code(product->code, 10);

	printf("Price -> ");
	scanf_s("%f", &product->price);
	printf("Quantity -> ");
	scanf_s("%d", &product->quantity);
	printf("-----------------------------------\n");
	printf("Product data is successfully added!\n\n");
}

void save_products(Product* products, int number_of_products) {
	FILE* file = fopen("products.txt", "a");

	if (file == NULL) {
		printf("Error happened!\n");
		return;
	}

	if (number_of_products == 0) {
		printf("You haven't added any new products\n\n");
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
			swap_characters(product.name, '_', ' ');
			printf("%-30s %-30s %-30.2f %-10d\n", product.name, product.code, product.price, product.quantity);
		}
	}

	printf("\n");
	fclose(read_file);
}

void welcome_menu() {
	printf("  >>   Welcome to shop!   <<  \n");
	printf("-----------------------------\n\n");
}

void display_options() {
	printf("  >>   Choose an option from the menu:   <<  \n");
	printf("---------------------------------------------\n");
	printf("> 1 - Add products\n");
	printf("> 2 - View products\n");
	printf("> 3 - Exit\n");
	printf("---------------------------------------------\n");
	printf("--> ");
}

void menu() {
	char choice;
	int number_of_products;

	do {
		display_options();
		choice = getchar();
		printf("\n");
		while (getchar() != '\n');

		switch (choice) {
		case '1':
			printf("Enter the number of products: ");
			scanf_s("%d", &number_of_products);
			while (getchar() != '\n');

			Product* products = (Product*)malloc(number_of_products * sizeof(Product));

			if (products == NULL) {
				printf("Error in allocating memory!\n");
				return;
			}

			for (int i = 0; i < number_of_products; i++) {
				printf("Product %d:\n", i + 1);
				enter_product_data(&products[i]);
				while (getchar() != '\n');
			}

			save_products(products, number_of_products);

			free(products);
			break;
		case '2':
			read_products();
			break;
		case '3':
			printf("You have successfully exited the program.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != '3');
}

int main() {

	welcome_menu();

	srand((unsigned int)time(NULL));

	menu();

	return 0;
}