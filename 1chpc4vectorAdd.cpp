%%cu
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void add(int* A, int* B, int* C, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        C[tid] = A[tid] + B[tid];
    }
}

void initialize(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 10;
    }
}

void print(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
}

int main() {
    int N = 4;
    int *A, *B, *C;

    size_t vectorBytes = N * sizeof(int);

    A = new int[N];
    B = new int[N];
    C = new int[N];

    initialize(A, N);
    initialize(B, N);

    cout << "Vector A: ";
    print(A, N);
    cout << "Vector B: ";
    print(B, N);

    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, vectorBytes);
    cudaMalloc(&d_B, vectorBytes);
    cudaMalloc(&d_C, vectorBytes);

    cudaMemcpy(d_A, A, vectorBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, vectorBytes, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    add<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();  // Ensure kernel execution is complete

    cudaMemcpy(C, d_C, vectorBytes, cudaMemcpyDeviceToHost);

    cout << "Addition: ";
    print(C, N);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}

