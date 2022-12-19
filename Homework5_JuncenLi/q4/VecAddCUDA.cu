#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <string.h>
#include <cuda.h>
#include "math.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// CUDA kernel. Each thread takes care of one element of c
__global__ void vecaddgpu(float *d_a, float *d_b, float *d_c, int n) {
 //Device Code
 	//get unique index on which to compute
	int index = threadIdx.x + (blockIdx.x * blockDim.x);
	
	//add vectors on this index
	if(index < n){
		d_c[index] = d_a[index] + d_b[index];
	}
}

int main( int argc, char* argv[] ) {

    float timerValueGPU;
	cudaEvent_t start, stop;
	cudaEventCreate(&start); 
    cudaEventCreate(&stop);

    // Size of vectors
    int n = 100000;
    float *h_a;
    float *h_b;
    float *h_c;
    float *d_a;
    float *d_b;
    float *d_c;
    // Allocate memory for each vector on host
    size_t bytes = n*sizeof(float);
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);
    // Allocate memory for each vector on GPU
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
    // Initialize vectors on host
    int i;
    for ( i = 0; i < n; i++ ) {
        h_a[i] = sinf(i)*sinf(i);
        h_b[i] = cosf(i)*cosf(i);
    }
    // Copy host vectors to device
    cudaMemcpy( d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, h_b, bytes, cudaMemcpyHostToDevice);
    // Execute the kernel
    int blockSize, gridSize;
    blockSize = 1024;
    gridSize = (int)ceil((float)n/blockSize);

    // start timer
	cudaEventRecord(start, 0);
    // running kernel function
    vecaddgpu<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);
    // GPU computation time estimate
    cudaDeviceSynchronize();
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
    cudaEventElapsedTime(&timerValueGPU, start, stop);
    printf("GPU calculation time %f msec\n", timerValueGPU);

    // Copy array back to host
    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
    // Sum up vector c and print result divided by n, this should equal 1 within error
    float sum = 0;
    for(i = 0; i < n; i++) {
        sum += h_c[i];
    }
    printf("final result: %f\n", sum/n);
    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    // Release host memory
    free(h_a);
    free(h_b);
    free(h_c);
    return 0;
}