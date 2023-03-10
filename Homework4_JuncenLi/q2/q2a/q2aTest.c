#include <stdio.h>
#include<stdlib.h>

#define N 1000
#define UPPER_LIM 200.0
#define LOWER_LIM  1.0
#define NBINS 4
#define SLICE N/NBINS

double generate_random_number(double lower_limit, double upper_limit) {
    return lower_limit + (upper_limit - lower_limit) * ((double)rand() / RAND_MAX);
}

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
    for (int i = 0; i < N; i ++) {
        data[i] = generate_random_number(LOWER_LIM, UPPER_LIM);
    }
    
    //Local and global histograms
    int local_hist[NBINS], global_hist[NBINS];

    //Bin limits vector
    double bins[NBINS];
    for(int i = 0; i<NBINS; i++)
        bins[i] = ((UPPER_LIM - LOWER_LIM) / NBINS * i) + LOWER_LIM;

    //Compute local histogram
    histogram(data, N, bins, NBINS, global_hist);
    
    //Print local results
    printf("RESULTS LOCAL");
    for(int i = 0; i < NBINS; i++){
        if(i<NBINS-1){
            printf("[%f - %f)\t", bins[i], bins[i+1]);
        }else{
            printf("[%f - %f)\t", bins[i], UPPER_LIM);
        }
    }
    printf("\n");

    //Print global results
    printf("GLOBAL RESULTS:\n");
    for(int i = 0; i < NBINS; i++){
        if(i<NBINS-1){
            printf("[%f - %f)\t", bins[i], bins[i+1]);
        }else{
            printf("[%f - %f)\t", bins[i], UPPER_LIM);
        }
        
    }
    printf("\n");
    for(int i = 0; i < NBINS; i++){
        printf("%d\t", global_hist[i]);
    }
    printf("\n");

}