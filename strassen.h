#ifndef __STRASSEN__
#define __STRASSEN__

#define MOD 10007

void alloc_zones(int ***mat1, int ***mat2, int ***mat3, int ***mat4, int size)
{
	//allocating space for 4 aux matrices
	*mat1 = alloc_data(size, size);
	*mat2 = alloc_data(size, size);
	*mat3 = alloc_data(size, size);
	*mat4 = alloc_data(size, size);
}

void divide_matrix(int **mat, int **m1, int **m2, int **m3, int **m4, int size)
{
	//dividing the matrix mat into 4 aux matrices
	int i = 0;
	while (i < size) {
		for (int j = 0; j < size; ++j) {
			m1[i][j] = mat[i][j];
			m2[i][j] = mat[i][j + size];
			m3[i][j] = mat[i + size][j];
			m4[i][j] = mat[i + size][j + size];
		}
		++i;
	}
}

void sum_matrix(int **a, int **b, int **sum_matrix, int size)
{
	//calaculating the sum of two matrices
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			sum_matrix[i][j] = (a[i][j] + b[i][j] + MOD) % MOD;
}

void substract(int **a, int **b, int **sub_mat, int size)
{
	//calculating the substraction of two matrices and storing it
	//in sub_mat
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			sub_mat[i][j] = (a[i][j] - b[i][j] + MOD) % MOD;
}

void final_result(int **mat, int **m1, int **m2, int **m3, int **m4, int size)
{
	//reconstructing the matrix that represents the result of the
	//multiplication, using the blocks defined earlier
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			mat[i][j] = m1[i][j];
			mat[i][j + size] = m2[i][j];
			mat[i + size][j] = m3[i][j];
			mat[i + size][j + size] = m4[i][j];
		}
}

void free_zones(int ***mat1, int ***mat2, int ***mat3, int ***mat4, int size)
{
	//freeing the used matrices memory
	free_matrix(size, *mat1);
	free_matrix(size, *mat2);
	free_matrix(size, *mat3);
	free_matrix(size, *mat4);
}

void strassen(int **a, int **b, int **c, int size_m)
{
	if (size_m != 1) {
		int newsize = size_m / 2;
		//blocks used in the implementation of the algorithm
		//4 for each matrix
		int **a11, **a12, **a21, **a22;
		int **b11, **b12, **b21, **b22;
		int **c11, **c12, **c21, **c22;
		//seven matrices that help us minimize the number of multiplications
		int **p1, **p2, **p3, **p4, **p5, **p6, **p7;
		int **sum_a, **sum_b;

		alloc_zones(&a11, &a12, &a21, &a22, newsize);

		alloc_zones(&b11, &b12, &b21, &b22, newsize);

		alloc_zones(&c11, &c12, &c21, &c22, newsize);

		alloc_zones(&p1, &p2, &p3, &p4, newsize);

		alloc_zones(&p5, &p6, &p7, &sum_a, newsize);

		sum_b = alloc_data(newsize, newsize);

		divide_matrix(a, a11, a12, a21, a22, newsize);
		divide_matrix(b, b11, b12, b21, b22, newsize);

		sum_matrix(a11, a22, sum_a, newsize);
		sum_matrix(b11, b22, sum_b, newsize);
		strassen(sum_a, sum_b, p1, newsize);

		sum_matrix(a21, a22, sum_a, newsize);
		strassen(sum_a, b11, p2, newsize);

		substract(b12, b22, sum_b, newsize);
		strassen(a11, sum_b, p3, newsize);

		substract(b21, b11, sum_b, newsize);
		strassen(a22, sum_b, p4, newsize);

		sum_matrix(a11, a12, sum_a, newsize);
		strassen(sum_a, b22, p5, newsize);

		substract(a21, a11, sum_a, newsize);
		sum_matrix(b11, b12, sum_b, newsize);
		strassen(sum_a, sum_b, p6, newsize);

		substract(a12, a22, sum_a, newsize);
		sum_matrix(b21, b22, sum_b, newsize);
		strassen(sum_a, sum_b, p7, newsize);

		sum_matrix(p3, p5, c12, newsize);
		sum_matrix(p2, p4, c21, newsize);

		sum_matrix(p1, p4, sum_a, newsize);
		sum_matrix(sum_a, p7, sum_b, newsize);
		substract(sum_b, p5, c11, newsize);

		sum_matrix(p1, p3, sum_a, newsize);
		sum_matrix(sum_a, p6, sum_b, newsize);
		substract(sum_b, p2, c22, newsize);

		final_result(c, c11, c12, c21, c22, newsize);

		free_zones(&a11, &a12, &a21, &a22, newsize);
		free_zones(&b11, &b12, &b21, &b22, newsize);
		free_zones(&c11, &c12, &c21, &c22, newsize);
		free_zones(&p1, &p2, &p3, &p4, newsize);
		free_zones(&p5, &p6, &p7, &sum_a, newsize);
		free_matrix(newsize, sum_b);
	}

	else
		//the base case
		c[0][0] = (a[0][0] * b[0][0] + MOD) % MOD;
}

#endif
