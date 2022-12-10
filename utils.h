#ifndef __UTILS__
#define __UTILS__
#define MOD 10007

typedef struct {
		int row, column;
	} indexes;

// dynamically allocates memory for a matrix (int **)
//in other words we allocate memory for n pointers (arrays)
int **alloc_data(int row, int column)
{
	int **matrix = malloc(row * sizeof(int *));

	//defensive programming
	while (matrix == 0) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}
	//row allocation
	int i = 0;
	while (i < row) {
		//for each row we allocate column * sizeof(int)
		matrix[i] = malloc(column * sizeof(int));
		//further defensive programming
		while (matrix[i] == 0) {
			fprintf(stderr, "malloc() failed\n");

			//for each row previously allocated, we deallocate since
			//the malloc() function failed
			for (int j = 0; j < i; j++)
				free(matrix[i]);
			free(matrix);
			return NULL;
		}
		++i;
	}

	return matrix;
}

void free_matrix(int row, int **matrix)
{
	for (int i = 0; i < row; ++i)
		free(matrix[i]);
	free(matrix);
}

#endif
