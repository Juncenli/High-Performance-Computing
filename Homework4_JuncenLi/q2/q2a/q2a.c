#include <stdio.h>
#include<stdlib.h>
#include <mpi.h>
#include<sys/time.h>

#define N 2000000
#define UPPER_LIM 1000000.0
#define LOWER_LIM  1.0
#define NBINS 100
#define SLICE N/NBINS


// Produce random numbers within the given parameters
double generate_random_number(unsigned int lower_limit, unsigned int upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

// Function that, given the bottom and upper bounds and the number of bins, 
// returns the histogram of the input array data (probably not the most efficient one)
void histogram(double* data, int data_len, double* bins, int nbins, int* hist){
    //Histogram
    for(int i = 0; i<data_len; i++){
        for(int j = 0; j<nbins; j++){
            if(data[i] >= bins[j]){
                if((data[i] < bins[(j+1)]) || j==nbins-1){
                    hist[j]++;
                    break;
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
    double data[N];
    double slice[SLICE];
     // Create a random array of values
    for (int i = 0; i < N; i ++) {
        data[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
    }
    
    int rank, size, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    // Histograms both locally and globally
    int local_hist[NBINS], global_hist[NBINS];

    // Time
    struct timeval  start, end;
    double comp_time;

    // Bin limits vector
    double bins[NBINS];
    for(int i = 0; i<NBINS; i++)
        bins[i] = ((UPPER_LIM - LOWER_LIM) / NBINS * i) + LOWER_LIM;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name, &namelen);

    // Start timer in node 0
    if(rank==0){
        gettimeofday(&start, NULL);
    }

    // Slice and send data
    if(rank==0){
        for(int i = 1; i<NBINS; i++){
            // Choose the relevant data segment to send.
            for(int j=0; j < SLICE; j++){
                slice[j] = data[i * SLICE + j];
            }
            MPI_Send(slice, SLICE, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
        //get the main process own slice
        for(int j=0; j < SLICE; j++) slice[j] = data[j];
    }else{
        MPI_Recv(slice, SLICE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Compute local histogram
    histogram(slice, SLICE, bins, NBINS, local_hist);

    // Reduce to master process
    MPI_Reduce(local_hist, global_hist, NBINS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    if(rank==0){
        gettimeofday(&end, NULL);
        comp_time = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec))); 
        printf("Total computation period: %f\n", comp_time);
    }
}