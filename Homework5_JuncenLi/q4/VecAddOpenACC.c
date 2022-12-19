#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <math.h>
// CUDA kernel. Each thread takes care of one element of c
void vecaddgpu(float *a, float *b, float *restrict c, int n) {
    #pragma acc kernels copyin(a[0:n],b[0:n]) copyout(c[0:n])
    for (int i = 0; i < n; ++i)
        c[i] = a[i] + b[i];
}

int main( int argc, char* argv[] ) {
    // Size of vectors
    int n = 100000;
    float *a;
    float *b;
    float *c;


    // Allocate memory for each vector on host
    size_t bytes = n*sizeof(float);
    a = (float*)malloc(bytes);
    b = (float*)malloc(bytes);
    c = (float*)malloc(bytes);
    // Initialize vectors on host
    int i;
    for( i = 0; i < n; i++ ) {
        a[i] = sinf(i)*sinf(i);
        b[i] = cosf(i)*cosf(i);
    }

    //timing variables
    struct timeval  start, end;
    double comp_time;

    //Start timer
    gettimeofday(&start, NULL);
    // Execute the kernel
    vecaddgpu(a, b, c, n);
    //Stop timer
    gettimeofday(&end, NULL);
    comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec))); 
    printf("GPU calculation time %f msec\n", comp_time);

    // Sum up vector c and print result divided by n, this should equal 1 within error
    float sum = 0;
    for(i=0; i<n; i++)
        sum += c[i];
    printf("final result: %f\n", sum/n);
    // Release host memory
    free(a);
    free(b);
    free(c);
    return 0;
}