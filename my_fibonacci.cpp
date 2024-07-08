/*
 *  my_fibonacci.cpp
 *  ENSF 694 Lab 2 - Exercise D
 *  Created by Mahmood Moussavi
 *  Completed by: Jeff Wheeler
 *  Submission date: July 10, 2024
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
using namespace std;
#define N 2


void myPlot(int* x, double *y1, double *y2, int size);
/*
* REQUIRES: x, y1, y2 point to valid arrays
* PROMISES: plot y1 and y2 against x using gnuplot
*/

void multiplyMatrix(int a[N][N], int b[N][N], int result[N][N]);
/*
* REQUIRES: a, b, result are valid arrays
* PROMISES: Function to multiply two matrices of size N x N
*/

void powerMatrix(int base[N][N], int exp, int result[N][N]);
/*
* REQUIRES: exp > 0
* PROMISES: Recursive function to calculate matrices to the power of exp
*/

int fibonacciRecursive(int n);
/*
* REQUIRES: n > 0
* PROMISES: Returns the nth Fibonacci number using recursive matrix exponentiation
*/

int fibonacciIterative(int n);
/*
* REQUIRES: n > 0
* PROMISES: Returns the nth Fibonacci number iteratively
*/

double measureTime(int (*fibonacciFunc)(int), int n);
/*
* REQUIRES: n > 0
* PROMISES: Returns the time taken by a function to calculate the nth Fibonacci number 
*           This function is using a pointer to a function called fibonacciFunc
*/

int main(void) {
    const int maxN = 400000000; // Adjust maxN based on the range you want to test
    double recursive_result[50];
    double iterative_result[50];
    int N_value[50];

    cout << "Recursive Matrix Exponentiation Method\n";
    cout << setw(12) << "N" << setw(12) << "Time\n";
    for (int n = 20000000, i=0; n <= maxN; n+=20000000, i++) {
        double time = measureTime(fibonacciRecursive, n);
        recursive_result[i] = time;
        cout << setw(12) << n << setw(12) << recursive_result[i] << endl;
    }

    cout << "\nIterative Method\n";
    cout << setw(12) << "N" << setw(12) << "Time\n";
    for (int n = 20000000, i=0; n <= maxN; n+=20000000, i++) {
        double time = measureTime(fibonacciIterative, n);
        iterative_result[i] = time;
        cout << setw(12) << n << setw(12) << iterative_result[i] << endl;
        N_value[i] = n;
    }
    
    myPlot(N_value, iterative_result, recursive_result, 30);

    return 0;
}

void myPlot(int* x, double *y1, double *y2, int size){
    FILE * gnuplotPipe = popen ("C:/'Program Files'/gnuplot/bin/gnuplot.exe -persistent", "w");
    
    const char* name = "Plot";
    const char* xlabel = "N Value";
    const char* ylabel = "Time (s)";
    const char* y1label = "Iterative Result";
    const char* y2label = "Recursive Result";
   
    fprintf(gnuplotPipe, "set title '%s'\n", name);
    fprintf(gnuplotPipe, "set xlabel '%s'\n", xlabel);
    fprintf(gnuplotPipe, "set ylabel '%s'\n", ylabel);
    fprintf(gnuplotPipe, "set tics nomirror\n");
    fprintf(gnuplotPipe, "set y2tics\n");
    fprintf(gnuplotPipe, "set key top center horizontal\n");
    fprintf(gnuplotPipe, "set xrange [%d:*]\n", 0);
    fprintf(gnuplotPipe, "set yrange [%d:*]\n", 0);
    fprintf(gnuplotPipe, "plot '-' pt 7 ps 1 lc 'blue' title '%s', '-' pt 7 ps 1 lc 'red' title '%s'\n", y1label, y2label);
    
    for (int i=0; i < size; i++){
        fprintf(gnuplotPipe, "%d %f\n", x[i], y1[i]);  
    }
    fprintf(gnuplotPipe, "e\n");

    for (int i=0; i < size; i++){
        fprintf(gnuplotPipe, "%d %f\n", x[i], y2[i]);
    }
    fprintf(gnuplotPipe, "e\n");
    
    fflush(gnuplotPipe);

    pclose(gnuplotPipe);
}

void multiplyMatrix(int a[N][N], int b[N][N], int result[N][N]) {
    result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
}

void powerMatrix(int base[N][N], int exp, int result[N][N]) {
    if (exp == 1){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                result[i][j] = base[i][j];
            }
        }
        return;
    }
    else if (exp == 2){
        multiplyMatrix(base, base, result);
    }
    else if (exp % 2 == 0){
        int temp[N][N];
        powerMatrix(base, (exp/2), temp);
        multiplyMatrix(temp, temp, result);
    }
    else {
        int temp[N][N];
        powerMatrix(base, (exp - 1), temp);
        multiplyMatrix(base, temp, result);
    }
}

int fibonacciRecursive(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int base[N][N] = {{1, 1}, {1, 0}};
    int result[N][N];
    powerMatrix(base, n - 1, result);
    return result[0][0];
}

int fibonacciIterative(int n) {
    if (n <= 1)
        return n;
    int a = 0, b = 1 ,c;
    for (int i = 2; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

double measureTime(int (*fibonacciFunc)(int), int n) {
    const auto start = std::chrono::high_resolution_clock::now();
    fibonacciFunc(n);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = end - start;
    return (double) diff.count();
}