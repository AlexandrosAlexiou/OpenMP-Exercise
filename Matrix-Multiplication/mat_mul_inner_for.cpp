//
//  mat_mul_inner_for.c
//  Matrix-Mul-inner
//
// Alexandros Alexiou AM: 2929  on 18/4/20.
#include <iostream>
#include <stdlib.h>
#include <omp.h>

#define N 1024
#define NUM_THREADS 16
#define CHUNK_SIZE 100

int A[N][N], B[N][N], C[N][N];
int readmat(std::string fname, int* mat, int n),
    writemat(std::string fname, int* mat, int n);

int main()
{
    int i, j, k,sum;
    /* Read matrices from files: "A_file", "B_file" */
    if (readmat("../common/Amat1024.txt", (int *) A, N) < 0)
        exit(1 + printf("file problem\n"));
    if (readmat("../common/Bmat1024.txt", (int *) B, N) < 0)
        exit(1 + printf("file problem\n"));
	double start = omp_get_wtime();
	for (i = 0; i < N; i++){
	    for (j = 0; j < N; j++)
	    {
            sum = 0;
            #pragma omp parallel for private(k) reduction(+: sum) num_threads(NUM_THREADS) schedule(dynamic, CHUNK_SIZE)
            for (k= 0; k < N; k++)
                    sum += A[i][k]*B[k][j];
            C[i][j] = sum;
	    };
	}
    double end = omp_get_wtime();
    std::cout << "Calculation total time with tasks using " + std::to_string(NUM_THREADS) + " threads took: " + std::to_string(end - start) + " seconds\n" << std::endl;

    /* Save result in "Cmat1024_inner"
     */
    writemat("Cmat1024_inner", (int *) C, N);
    return (0);
}


/* Utilities to read & write matrices from/to files
 * VVD
 */

#define _mat(i,j) (mat[(i)*n + (j)])


int readmat(std::string fname, int* mat, int n)
{
    FILE* fp;
    int  i, j;

    if ((fp = fopen(fname.c_str(), "r")) == NULL) return (-1);
    for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
            if (fscanf(fp, "%d", &_mat(i,j)) == EOF)
            {
                fclose(fp);
                return (-1);
			};
    fclose(fp);
    return (0);
}


int writemat(std::string fname, int* mat, int n)
{
    FILE* fp;
    int  i, j;
    
    if ((fp = fopen(fname.c_str(), "w")) == NULL) return (-1);
    for (i = 0; i < n; i++, fprintf(fp, "\n"))
        for (j = 0; j < n; j++)
            fprintf(fp, " %d", _mat(i, j));
    fclose(fp);
    return (0);
}
