#include "matrix_algebra.h"
#include <stdlib.h>

//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{
	int n;
	int m;
	double ** n_rows;
	//n_rows is an array of pointers, points to the start of each row


};


mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
	struct matrix * matt = malloc(sizeof(struct matrix));
	if (matt == NULL)
	{
		return NULL;
	}
	matt->n = n;
	matt->m = m;

	matt->n_rows = malloc(sizeof(double*) * n);

	for(int i = 0; i < n; i++)
	{
		matt->n_rows[i] = malloc(sizeof(double) * m);
	}


	return matt;
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	
	FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
     //fopen fail
     return NULL;
    }
	
	int n;
	int m;

	fread(&n, sizeof(int), 1, fptr);
	fread(&m, sizeof(int), 1, fptr);

	
	

	struct matrix * matt = create_matrix(n, m);

	for(int i = 0; i < n; i++)
	{
		int get = fread(matt->n_rows[i], sizeof(double), m, fptr);
		if (get < m)
		{
			return NULL;
		}
	}

	fclose(fptr);

	return(matt);

}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
	
	//if the multiplication doesnt exist
	
	if(A->m != B->n || A == NULL || B == NULL)
	{
		return NULL;
	}

	struct matrix *matt = create_matrix(A->n, B->m);
	double temp = 0;

	for(int i = 0; i < A->n; i++)
	{
		for(int j = 0; j < B->m; j++)
		{
			temp = 0;
			for(int k = 0; k < B->n; k++)
			{
				temp += A->n_rows[i][k] * B->n_rows[k][j];
			}
			matt->n_rows[i][j] = temp;
		}
	}

	return(matt);
	

}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.

	if(A->n != B->n || A->m != B->m || A == NULL || B == NULL)
	{
		return NULL;
	}

	struct matrix *matt = create_matrix(A->n, A->m);

	for(int i = 0; i < A->n; i++)
	{
		for(int j = 0; j < A->m; j++)
		{
			matt->n_rows[i][j] = A->n_rows[i][j] + B->n_rows[i][j];
		}
		
	}

	

	return matt;
}

void matrix_free(mat* A)
{
	//fill in this funciton to free the matrix A.
	if( A == NULL)
	{
		return;
	}
	for(int i = 0; i < A->n; i++)
	{
		free(A->n_rows[i]);
	}
	free(A->n_rows);
	free(A);
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
	if(A == NULL)
	{
		return 0;
	}
	FILE *fptr = fopen(filename, "wb");
    if (fptr == NULL)
    {
     //fopen fail
     return 0;
    }
	
	
	fwrite(&A->n, sizeof(int), 1, fptr);
	fwrite(&A->m, sizeof(int), 1, fptr);

	for(int i = 0; i < A->n; i++)
	{
		fwrite(A->n_rows[i], sizeof(double), A->m, fptr);
	}

	

	fclose(fptr);

	//free(A);

	return(1);

}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{

	if(A == NULL)
	{
		return NULL;
	}
	//create the matrix
	struct matrix *matt = create_matrix(A->n, A->m);

	for(int i = 0; i < A->n; i++)
	{
		for(int j = 0; j < A->m; j++)
		{
			matt->n_rows[i][j] = A->n_rows[i][j] * c;
		}
		
	}

	return matt;

}



// my gf is so cool and compile core <3
// i would do some ascii art but i don't actually know how
// -*
// tiny flower

