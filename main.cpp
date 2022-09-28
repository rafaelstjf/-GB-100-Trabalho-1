/**
 * @file trab_1.cpp
 * @author Rafael Terra, Thays Rocha
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <cstdlib>
#include <iostream>
#include <random>
#include <assert.h>
#include <ctime>
#define MAX_VALUE 1000L
#define TEST_SEED 123456
std::mt19937 mt(TEST_SEED); //Generator as a global variable
using namespace std;

/**
 * @brief Função para multiplicar uma matriz (nxm) por um vetor (nx1) e retornar o resultado
 * 
 * @param matrix: Matriz usada na multiplicação
 * @param vector: Vetor usado na multiplicação
 * @param n: Número de linhas da matriz
 * @param m: Número de linhas do vetor
 * @return int*: Retorna o vetor resultante da multiplicação
 */
long int* multiply(long int** matrix, long int* vector, long int n, long int m){
    long int* c = new long int[n];
    //malloc(sizeof(int)*m);
    for(long int i = 0; i < m; i++)
        c[i] = 0;
    for(long int i  = 0; i < n; i++){
        for(long int j = 0; j < m; j++){
            c[i] += matrix[i][j]*vector[j];
            cout << "c[" << i << "]: = " << "M[" << i << "][" << j << "]*b[" << j << "]" << endl;
            //cout << c[i] << " = " << matrix[i][j] << " * " << vector[j] << endl;
        }
    }
    return c;
}
long int* multiplyCacheBlocking(long int** matrix, long int* vector, long int n, long int m, int tile_size){
    assert(m % tile_size == 0);
    long int* c = new long int[n];
    for(long int i =0; i < m; i++){
        c[i] = 0;
    }
    for(long int jj = 0; jj < m; jj+=tile_size){
        for(long int i  = 0; i < n; i++){
            for(long j = jj; j < jj + tile_size; j++){
                c[i] += matrix[i][j]*vector[j];
                cout << "c[" << i << "]: = " << "M[" << i << "][" << j << "]*b[" << j << "]" << endl;
                //cout << c[i] << " = " << matrix[i][j] << " * " << vector[j] << endl;
            }
        }
    }
    return c;
}

long int** create_matrix(int n, int m){
    uniform_int_distribution<long int> uniform{0L,MAX_VALUE};
    long int** matrix  = new long int*[n];
    //(int*)malloc(sizeof(int*)*n);
    for(long int i = 0; i < n; i++){
        matrix[i] = new long int[m];
        for(long int j = 0; j < m; j++){
            matrix[i][j] = uniform(mt);
        }
    }
    return matrix;

}
long int* create_vector(long int m){
    uniform_int_distribution<long int> uniform{0L,MAX_VALUE};
    long int* vector = new long int[m];
    for(long int i = 0; i < m; i++){
        vector[i] = uniform(mt);
    }
    return vector;

}
void printElements(long int** matrix, long int* vector, long int *c, long int n, long int m){
    cout << "Matrix: " << endl;
    for(long int i = 0; i < n; i++){
        for(long int j = 0; j < m; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Vector: " << endl;
    for(long int i = 0; i < m; i++){
        cout << vector[i] << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Resulting vector: " << endl;
    for(long int i = 0; i < n; i++){
        cout << c[i] << endl;
    }
    cout << "----------------------------------" << endl;
}
int main(int argc, char* argv[]){
    long int m = 2000, n = 3000;
    int use_cache = 0, tile_size=4;
    if (argc > 4){
        n = atol(argv[1]);
        m = atol(argv[2]);
        use_cache = atoi(argv[3]);
        tile_size = atoi(argv[4]);
    }
    else{
        cerr << "Arguments needed (in order): \"number of lines\" \"number of columns\" \"0 for normal multiplication or 1 for using cache blocking\" \"tile size\"" << endl;
        exit(-1);
    }
    long int* vector  = create_vector(m);
    long int** matrix = create_matrix(n, m);
    long int* c = nullptr;
    if (use_cache)
        c = multiplyCacheBlocking(matrix, vector, n, m, tile_size);
    else
        c = multiply(matrix, vector, n, m);

    printElements(matrix, vector, c, n, m);
    /*
    clock_t t;
    t = clock();
    t = clock() - t;
    float time_seconds = ((float)t)/CLOCKS_PER_SEC;
    cout << "The execution took " << time_seconds << " seconds." << endl;
    */
    delete vector;
    delete c;
    for(long int i = 0; i < n; i++){
        delete matrix[i];
    }
    delete matrix;
    return 0;
}
