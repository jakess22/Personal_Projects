#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double** make_s() {
	double** s = (double**)calloc(2, sizeof(double*));
	for (int i = 0; i < 2; i++){
		s[i] = (double*)calloc(2, sizeof(double));
	}
	s[0][0] = (1.00 + sqrt(5.00)) / 2.00;
	s[0][1] = (1.00 - sqrt(5.00)) / 2.00;
	s[1][0] = 1.00000;
	s[1][1] = 1.00000;

	return s;
}

double** make_eig() {
	double** eig = (double**)calloc(2, sizeof(double*));
	for (int i = 0; i < 2; i++) {
		eig[i] = (double*)calloc(2, sizeof(double));
	}
	eig[0][0] = (1.00 + sqrt(5.00)) / 2.00;
	eig[0][1] = 0.00;
	eig[1][0] = 0.00;
	eig[1][1] = (1.00 - sqrt(5.00)) / 2.00;

	return eig;
}

double** make_s_inv() {
	double** s_inv = (double**)calloc(2, sizeof(double*));
	for (int i = 0; i < 2; i++) {
		s_inv[i] = (double*)calloc(2, sizeof(double));
	}
	s_inv[0][0] = 1.00 / sqrt(5.00);
	s_inv[0][1] = -(1.00 - sqrt(5.00)) / (2.00 * sqrt(5.00));
	s_inv[1][0] = -1.00 / sqrt(5.00);
	s_inv[1][1] = (1.00 + sqrt(5.00)) / (2.00 * sqrt(5.00));

	return s_inv;
}


void matrix_mult(double** a, double** b, double** prod_matrix) {
	prod_matrix[0][0] = (a[0][0] * b[0][0]) + (a[0][1] * b[1][0]);
	prod_matrix[0][1] = (a[0][0] * b[0][1]) + (a[0][1] * b[1][1]);
	prod_matrix[1][0] = (a[1][0] * b[0][0]) + (a[1][1] * b[1][0]);
	prod_matrix[1][1] = (a[1][0] * b[0][1]) + (a[1][1] * b[1][1]);
}



double get_fib_term(int user_term, double** s, double** eig, double** s_inv) {
	eig[0][0] = pow(eig[0][0], user_term);
	eig[1][1] = pow(eig[1][1], user_term);
	double** temp_matrix = (double**)calloc(2, sizeof(double*));
	for (int i = 0; i < 2; i++) {
		temp_matrix[i] = (double*)calloc(2, sizeof(double));
	}

	matrix_mult(s, eig, temp_matrix);


	double** final_matrix = (double**)calloc(2, sizeof(double*));
	for (int i = 0; i < 2; i++) {
		final_matrix[i] = (double*)calloc(2, sizeof(double));
	}
	matrix_mult(temp_matrix, s_inv, final_matrix);

	double fib = final_matrix[0][0];

	eig[0][0] = (1 + sqrt(5)) / 2;
	eig[1][1] = (1 - sqrt(5)) / 2;

	return fib;
}

void get_fib(double** s, double** eig, double** s_inv) {
	printf("Enter the Fibonacci term you would like to find.\n");
	int user_term;
	scanf(" %d", &user_term);

	double fib = get_fib_term(user_term, s, eig, s_inv);
	printf("The #%d term of the Fibonacci sequence is %.0f.\n", user_term, fib);
	printf("Would you like to calculate another term?\n");
	printf("\"y\" for yes, and \"n\" for no.\n");

	char user_choice;
	scanf(" %c", &user_choice);
	if (user_choice == 'y' || user_choice == 'Y') {
		get_fib(s, eig, s_inv);
	} else {
		return;
	}
}


int main() {
	double** s = NULL;
	double** eig = NULL;
	double** s_inv = NULL;
	//s[2][2]

	printf("Any Fibonacci term can be calculated noniteratively using exponentiation of the eigenvalue decomposition of the symettric Fibonacci matrix.\n");
	printf("Assume n = 1 is 1, with n - 2 = 0 and n - 1 = 1.\n");
	s = make_s();
	eig = make_eig();
	s_inv = make_s_inv();

	get_fib(s, eig, s_inv);


	return 0;
}
