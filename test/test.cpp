//
//  matrix_checker.c
//  matrix_checker
//
//  Created by Alexandros Alexiou on 15/4/20.
//  Copyright © 2020 Alexandros Alexiou. All rights reserved.
//

#include <iostream>
#include "string"
#define N 1024

int check_matrices(std::string fname_serial, std::string fname_parallel);

int main(int argc, char* argv[])
{
    std::string serial(argv[1]);
    std::string parallel(argv[2]);
    check_matrices(serial, parallel);
    return (0);
}

int check_matrices(std::string fname_serial, std::string fname_parallel)
{
    FILE* fp_serial;
    FILE* fp_parallel;
    
    int serial_matrix_value = 0, parallel_matrix_value = 0, values_read = 0;
    
    if ((fp_serial = fopen(fname_serial.c_str(), "r")) == NULL)
    {
        std::cout << "File " + fname_serial +" error.\n" << std::endl;
        fclose(fp_serial);
        return (-1);
    }
    if ((fp_parallel = fopen(fname_parallel.c_str(), "r")) == NULL)
    {
        std::cout << "File " + fname_parallel +" error.\n" << std::endl;
        fclose(fp_parallel);
        return (-1);
    }
    
    while(fscanf(fp_serial, "%d", &serial_matrix_value) != EOF && fscanf(fp_parallel, "%d", &parallel_matrix_value) != EOF)
    {
        values_read++;
        if(serial_matrix_value != parallel_matrix_value)
        {
            std::cout << "Values read: " + std::to_string(values_read) << std::endl;
            std::cout << "Matrices are not equal." << std::endl;
            fclose(fp_serial);
            fclose(fp_parallel);
            return (-1);
        }
    }
    
    if (values_read < N*N)
    {
        std::cout << "Matrices are not equal." << std::endl;
        return (-1);
    }

    std::cout << "Matrices are equal." << std::endl;
    std::cout << "Values read: " + std::to_string(values_read) << std::endl;

    fclose(fp_serial);
    fclose(fp_parallel);
    return (0);
}
