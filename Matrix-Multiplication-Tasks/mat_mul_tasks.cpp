//
//  main.c
//  Matrix-Mul-Tasks
//
//  Created by Alexandros Alexiou on 18/4/20.
//  Copyright © 2020 Alexandros Alexiou. All rights reserved.
//
//
#include <iostream>
#include <cstdlib>
#include <omp.h>

#define N 1024
#define NUM_THREADS 16/* # threads */

/* Prototypes*/
int A[N][N], B[N][N], C[N][N];
int readmat(std::string fname, int* mat, int n),
    writemat(std::string fname, int* mat, int n);


int main(int argc, char *argv[])
{
    int S, M, row, column,i,j,k,sum;
    
    /* dimension of each submatrix */
    S = 8; //atoi(argv[1]);
    
    /* M*M submatrices in total -----> M*M tasks*/
    M = N/S;

    /* Read matrices from files: "A_file", "B_file"
     */
    if (readmat("../common/Amat1024.txt", (int *) A, N) < 0)
        exit( 1 + printf("file problem\n") );
    if (readmat("../common/Bmat1024.txt", (int *) B, N) < 0)
        exit( 1 + printf("file problem\n") );
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp single
        {
            for(row = 0; row < M; row++)
            {
                for (column = 0; column < M; column++)
                {
                    #pragma omp task firstprivate(row, column) private(i,j,k,sum)
                    {
                        for (i = row*S; i < (row+1)*S; i++){
                              for (j = column*S; j < (column+1)*S; j++)
                              {
                                  sum = 0;
                                  for (k = 0; k < N; k++)
                                      sum += A[i][k]*B[k][j];
                                  C[i][j] = sum;
                              }
                        }
                    }
                }
           }
        }
    }
    double end = omp_get_wtime();
    std::cout << "Calculation total time with tasks using " + std::to_string(NUM_THREADS) + " threads took: " + std::to_string(end - start) + " seconds\n" << std::endl;
    /* Save result in "Cmat1024"
     */
    writemat("Cmat1024_tasks", (int *) C, N);

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
    
    if ((fp = fopen(fname.c_str(), "r")) == NULL)
        return (-1);
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
    
    if ((fp = fopen(fname.c_str(), "w")) == NULL)
        return (-1);
    for (i = 0; i < n; i++, fprintf(fp, "\n"))
        for (j = 0; j < n; j++)
            fprintf(fp, " %d", _mat(i, j));
    fclose(fp);
    return (0);
}
