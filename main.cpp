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
long* multiply(long* matrix, long* vector, long n, long m){
    long* c = new long[n];
    if(c){
        for(long i = 0; i < n; i++)
        c[i] = 0L;
    }
    else{
        exit(-1);
    }
    for(long i  = 0; i < n; i++){
        for(long j = 0; j < m; j++){
            c[i] += matrix[i*m + j]*vector[j];
            //cout << "c[" << i << "]: = " << "M[" << i << "][" << j << "]*b[" << j << "]" << endl;
            //cout << c[i] << " = " << matrix[i][j] << " * " << vector[j] << endl;
        }
    }
    return c;
}
/**
 * @brief Função para multiplicar uma matriz (nxm) por um vetor (nx1) utilizando cache blocking e retornar o resultado 
 * 
 * @param matrix: Matriz usada na multiplicação
 * @param vector: Vetor usado na multiplicação
 * @param n: Número de linhas da matriz
 * @param m: Número de linhas do vetor
 * @param tile_size: Tamanho do tile
 * @return long*: Retorna o vetor resultante da multiplicação
 */
long* multiplyCacheBlocking(long* matrix, long* vector, long n, long m, int tile_size){
    assert(m % (long)tile_size == 0);
    long* c = new long[n];
    for(long i =0; i < n; i++){
        c[i] = 0L;
    }
    for(long jj = 0; jj < m; jj+=(long)tile_size){
        for(long i  = 0; i < n; i++){
            for(long j = jj; j < jj + (long)tile_size; j++){
                c[i] += matrix[i*m + j]*vector[j];
                //cout << "c[" << i << "]: = " << "M[" << i << "][" << j << "]*b[" << j << "]" << endl;
                //cout << c[i] << " = " << matrix[i*m + j] << " * " << vector[j] << endl;
            }
        }
    }
    return c;
}
/**
 * @brief Cria uma matriz de dimensao nxm com valores aleatórios entre 0 e MAX_VALUE
 * 
 * @param n: Número de linhas
 * @param m: Número de colunas
 * @return long**: Retorna a matriz criada
 */
long* create_matrix(long n, long m){
    uniform_int_distribution<long> uniform{0L,MAX_VALUE};
    long* matrix  = new long[n*m];
    for(long i = 0; i < n; i++){
        for(long j = 0; j < m; j++){
            matrix[i*m + j] = uniform(mt);
        }
    }
    return matrix;

}
/**
 * @brief Cria um vetor de dimensao mx1 com valores aleatórios entre 0 e MAX_VALUE
 * 
 * @param m: Número de linhas do vetor
 * @return long*: Retorna o vetor criado 
 */
long* create_vector(long m){
    uniform_int_distribution<long> uniform{0L,MAX_VALUE};
    long* vector = new long[m];
    for(long i = 0; i < m; i++){
        vector[i] = uniform(mt);
    }
    return vector;

}
/**
 * @brief Exibe os elementos (matriz, vetor e vetor resultante) usados para os cálculos
 * 
 * @param matrix: Matriz de dimensão nxm
 * @param vector: Vetor de dimensão mx1
 * @param c: Vetor de dimensão nx1 resultante da multiplicação da matriz pelo vetor 
 * @param n: Número de linhas da matriz
 * @param m: Número de colunas da matriz 
 */
void printElements(long** matrix, long* vector, long *c, long n, long m){
    cout << "Matrix: " << endl;
    for(long i = 0; i < n; i++){
        for(long j = 0; j < m; j++){
            cout << matrix[i*m + j] << "\t";
        }
        cout << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Vector: " << endl;
    for(long i = 0; i < m; i++){
        cout << vector[i] << endl;
    }
    cout << "----------------------------------" << endl;
    cout << "Resulting vector: " << endl;
    for(long i = 0; i < n; i++){
        cout << c[i] << endl;
    }
    cout << "----------------------------------" << endl;
}

int main(int argc, char* argv[]){
    long m = 2000L, n = 2000L;
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
    long* vector  = create_vector(m);
    long* matrix = create_matrix(n, m);
    long* c = nullptr;
    if (use_cache)
        c = multiplyCacheBlocking(matrix, vector, n, m, tile_size);
    else
        c = multiply(matrix, vector, n, m);
    //printElements(matrix, vector, c, n, m);
    delete[] vector;
    delete[] c;
    delete[] matrix;
    return 0;
}
