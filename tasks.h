#ifndef __TASKS__
#define __TASKS__
#define MOD 10007
#include "strassen.h"

int ***load(int *count, int ***p, indexes **x)
{
	int m, n;
	int **matrix;

	scanf("%d%d", &m, &n);//reading the size of the matrix that will be loaded
	matrix = alloc_data(m, n);

	if (*count != 0) {
		indexes *tmp = (indexes *)realloc(*x, sizeof(indexes) * (*count + 1));
		if (tmp == 0) {
			fprintf(stderr, "realloc() failed\n");
			return NULL;
		}
		*x = tmp;
		p = (int ***)realloc(p, sizeof(int **) * (*count + 1));
	}

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &matrix[i][j]);
	p[*count] = matrix;

	//storing sizes for future tasks
	(*x)[*count].row = m;
	(*x)[*count].column = n;

	(*count) = (*count) + 1;
	return p;
}

//function that shows the size of a given matrix
void dimension(int count, indexes *x)
{
	int i;
	scanf("%d", &i);

	//if there isn't any matrix with the given index
	if (i < 0 || i >= count)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", x[i].row, x[i].column);
}

//function that prints a given matrix
void print(int count, int ***p, indexes *x)
{
	int i;
	scanf("%d", &i);

	if (i < 0 || i >= count)
		printf("No matrix with the given index\n");
	else
		for (int l = 0; l < x[i].row; ++l) {
			for (int c = 0; c < x[i].column; ++c)
				printf("%d ", p[i][l][c]);
			printf("\n");
		}
}

void crop(int count, int ***p, indexes *x)
{
	int index;
	int l, c, *rows, *columns, **newmatrix;

	//reading the index of the matrix that needs to be croped
	scanf("%d", &index);

	scanf("%d", &l);
	rows = (int *)malloc(l * sizeof(int));
	for (int i = 0; i < l; ++i)
		scanf("%d", &rows[i]);

	//the number of columns of the new matrix +
	//the array of the column indexes
	scanf("%d", &c);
	columns = (int *)calloc(c, sizeof(int));
	for (int i = 0; i < c; ++i)
		scanf("%d", &columns[i]);

	if (index < 0 || index >= count) {
		printf("No matrix with the given index\n");
	} else {
		newmatrix = alloc_data(l, c);
		for (int i = 0; i < l; ++i)
			for (int j = 0; j < c; ++j)
				newmatrix[i][j] = p[index][rows[i]][columns[j]];

		free_matrix(x[index].row, p[index]);
		p[index] = newmatrix;

		//updating the dimensions
		x[index].row = l;
		x[index].column = c;
	}
	free(rows);
	free(columns);
}

int ***multiply_matrix(int *count, int ***p, indexes **x)
{
	int index1, index2;

	scanf("%d %d", &index1, &index2);

	if ((index1 < 0 || index1 >= *count) || (index2 < 0 || index2 >= *count)) {
		printf("No matrix with the given index\n");
	} else if ((*x)[index1].column != (*x)[index2].row) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		//allocating space for the result of the multiplication
		int **result = alloc_data((*x)[index1].row, (*x)[index2].column);

		if (result == 0) {
			fprintf(stderr, "malloc() failed\n");
			return NULL;
		}

		//performing the multiplication algorithm
		for (int i = 0; i < (*x)[index1].row; ++i) {
			for (int j = 0; j < (*x)[index2].column; ++j)
				result[i][j] = 0;//initializing the result with 0
			}
		for (int i = 0; i < (*x)[index1].row; ++i) {
			for (int j = 0; j < (*x)[index2].column; ++j) {
				for (int k = 0; k < (*x)[index2].row; ++k)
					//the multiplication process modulo MOD
					//assuring the positivite nature of the result
					result[i][j] = (result[i][j] + (p[index1][i][k] *
								   p[index2][k][j]) % MOD + MOD) % MOD;
			}
		}

		//making space for a new matrix in our collection
		indexes *tmp = (indexes *)realloc(*x, sizeof(indexes) * (*count + 1));
		if (tmp == 0) {
			fprintf(stderr, "realloc() failed\n");
			return NULL;
		}
		*x = tmp;
		p = (int ***)realloc(p, sizeof(int **) * (*count + 1));

		//adding the result to the array of matrices
		//but also the dimensions for future calculations
		p[*count] = result;
		(*x)[*count].row = (*x)[index1].row;
		(*x)[*count].column = (*x)[index2].column;

		//incrementing count, awaiting for future matrices
		(*count) = (*count) + 1;
	}
	return p;
}

void sort(int count, int ***p, indexes *x)
{
	int *s;
	int *sum_array;
	sum_array = (int *)malloc(count * sizeof(int));
	int k = 0;
	while (k < count) {
		int sum = 0;
		for (int i = 0; i < x[k].row; ++i)
			for (int j = 0; j < x[k].column; ++j) {
				sum += p[k][i][j];
				while (sum < 0)
					sum += MOD;
				sum %= (MOD);
			}
		sum_array[k] = sum;
		++k;
	}
	s = sum_array;

	//implementing bubble sort
	for (int i = 0; i < count - 1; ++i)
		for (int j = i + 1; j < count; ++j)
			if (s[i] > s[j]) {
				//swapping the matrices
				int **auxp = p[i];
				p[i] = p[j];
				p[j] = auxp;

				//swapping the lengths of the matrices
				int aux = x[i].row;
				x[i].row = x[j].row;
				x[j].row = aux;

				//swapping the columns of the matrices
				aux = x[i].column;
				x[i].column = x[j].column;
				x[j].column = aux;

				//swapping the sums of the matrices
				aux = s[i];
				s[i] = s[j];
				s[j] = aux;
			}
	free(s);
}

void transpose(int count, int ***p, indexes *x)
{
	int index;
	scanf("%d", &index);

	if (index < 0 || index  >= count) {
		printf("No matrix with the given index\n");
	} else {
		//allocating space for the transpose matrix
		int **t = alloc_data(x[index].column, x[index].row);
		int r = x[index].row, c = x[index].column;

		//algorithm for getting the transpose
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				t[j][i] = p[index][i][j];

		//updating the array of matrices
		free_matrix(x[index].row, p[index]);
		p[index] = t;

		//we should also modify the dimensions by swapping them
		x[index].row = c;
		x[index].column = r;
	}
}

int ***free_data(int *count, int ***p, indexes **x)
{
	int index;
	scanf("%d", &index);

	if (index < 0 || index >= *count) {
		printf("No matrix with the given index\n");
	} else {
		free_matrix((*x)[index].row, p[index]);

		//deleting one matrix from the array by moving all
		//the elements after it one place to the left
		for (int i = index + 1; i < *count; ++i) {
			p[i - 1] = p[i];

			//we should also delete its dimensions
			(*x)[i - 1].row = (*x)[i].row;
			(*x)[i - 1].column = (*x)[i].column;
		}
		//reallocating the space since we deleted one matrix
		//we should redimension the matrix only if we have more
		//than one element left
		if (*count > 1) {
			indexes *tmp = (indexes *)realloc(*x, sizeof(indexes) *
						   (*count - 1));

			if (!tmp) {
				fprintf(stderr, "realloc() failed\n");
				return NULL;
			}
			*x = tmp;
			p = (int ***)realloc(p, sizeof(int **) * (*count - 1));
		}

		//the dimension of the array also changes
		*count = *count - 1;
	}
	return p;
}

void quit(int count, int ***p, indexes *x)
{
	for (int i = 0; i < count; ++i)
		free_matrix(x[i].row, p[i]);

	free(p);
	free(x);
}

int ***task_strassen(int *count, int ***p, indexes **x)
{
	int index1, index2;
	scanf("%d %d", &index1, &index2);

	if ((index1 < 0 || index1 >= *count) || (index2 < 0 || index2 >= *count)) {
		printf("No matrix with the given index\n");
	} else if ((*x)[index1].column != (*x)[index2].row) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		int **result = alloc_data((*x)[index1].row, (*x)[index1].row);
		strassen(p[index1], p[index2], result, (*x)[index1].row);

		indexes *tmp = (indexes *)realloc(*x, sizeof(indexes) * (*count + 1));
		if (tmp == 0) {
			fprintf(stderr, "realloc() failed\n");
			return NULL;
		}
		*x = tmp;
		p = (int ***)realloc(p, sizeof(int **) * (*count + 1));

		//adding the result to the array of matrices
		//but also the dimensions for future calculations
		p[*count] = result;
		(*x)[*count].row = (*x)[index1].row;
		(*x)[*count].column = (*x)[index2].column;

		//incrementing count, awaiting for future matrices
		(*count) = (*count) + 1;
	}
	return p;
}

#endif
