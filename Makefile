CC = g++
CFLAGS = -fopenmp
OBJECTS =

all: 		mat_mul primes tasks matchecker

mat_mul:	Matrix-Multiplication/mat_mul_inner_for.cpp Matrix-Multiplication/mat_mul_middle_for.cpp Matrix-Multiplication/mat_mul_outer_for.cpp Matrix-Multiplication/mat_mul_serial.cpp
			$(CC) $(CFLAGS) -o Matrix-Multiplication/mat_mul_inner	Matrix-Multiplication/mat_mul_inner_for.cpp
			$(CC) $(CFLAGS) -o Matrix-Multiplication/mat_mul_middle	Matrix-Multiplication/mat_mul_middle_for.cpp
			$(CC) $(CFLAGS) -o Matrix-Multiplication/mat_mul_outer	Matrix-Multiplication/mat_mul_outer_for.cpp
			$(CC) $(CFLAGS) -o Matrix-Multiplication/mat_mul_serial	Matrix-Multiplication/mat_mul_serial.cpp

primes:		Primes-Calculator/primes.cpp
			$(CC) $(CFLAGS) -o Primes-Calculator/primes 		Primes-Calculator/primes.cpp

tasks:		Matrix-Multiplication-Tasks/mat_mul_tasks.cpp
			$(CC) $(CFLAGS) -o Matrix-Multiplication-Tasks/mat_mul_tasks	Matrix-Multiplication-Tasks/mat_mul_tasks.cpp

matchecker: test/test.cpp
			$(CC) $(CFLAGS) -o test/test		test/test.cpp
	
clean:
	rm -f 	Matrix-Multiplication/mat_mul_serial Matrix-Multiplication/mat_mul_inner Matrix-Multiplication/mat_mul_middle Matrix-Multiplication/mat_mul_outer Primes-Calculator/primes Matrix-Multiplication-Tasks/mat_mul_tasks test/test  Matrix-Multiplication-Tasks/Cmat1024_tasks  Matrix-Multiplication/Cmat1024_inner Matrix-Multiplication/Cmat1024_outer Matrix-Multiplication/Cmat1024_middle Matrix-Multiplication/Cmat1024_serial
