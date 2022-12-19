#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

long number_of_tosses;
int number_of_threads;
long number_in_circle = 0;
//long test = 0;
pthread_mutex_t mutex;

void *thread_handler(void *) {
    // Random
    double min = -1, max = 1;
    double x, y, distance_squared;
    long thread_number_in_circle = 0;
    unsigned int seed = (unsigned)time(NULL);
    //long thread_test = 0;

    long thread_number_of_tosses = number_of_tosses / number_of_threads;
    
    for (long toss = 0; toss < thread_number_of_tosses; toss++) {
        x = min + (double) rand_r(&seed) / RAND_MAX * (max - min);
        y = min + (double) rand_r(&seed) / RAND_MAX * (max - min);
        distance_squared = x*x + y*y;
        if (distance_squared <= 1) {
            thread_number_in_circle++;
        }
        //thread_test++;
    }
    //avoid race risk
    pthread_mutex_lock(&mutex);
    number_in_circle += thread_number_in_circle;
    //test += thread_test;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {

    // Setting global variables
    cout << "Number of threads: ";
    cin >> number_of_threads;

    cout << "number of “darts” thrown: ";
    cin >> number_of_tosses;
    // Get starting timepoint
    auto start = high_resolution_clock::now();
    srand( (unsigned)time(NULL) );

    // Create pthreads
    pthread_t thread_array[number_of_threads];

    /* 互斥锁初始化 */
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < number_of_threads; i++) {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&thread_array[i], NULL, thread_handler, NULL);
        if (ret != 0) {
            printf ("Create pthread error!\n");
            exit(EXIT_FAILURE);
        } else {
            printf ("Create pthread success!\n");
        }
    }


    // Join pthreads
    for (int i = 0; i < number_of_threads; i++) {
        int res = pthread_join(thread_array[i], NULL);
        if (!res) {
            printf("Thread %d joined\n", i);
        } 
        else {
            printf("Thread %d join failed\n", i);
        }
    }



    pthread_mutex_destroy(&mutex);

    // Print result
    double pi_estimate = 4 * number_in_circle / (double) number_of_tosses;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "pi_estimate: " << pi_estimate << endl;
    cout << "Time taken by function: " << duration.count() / 1000000.0 << "seconds" << endl;

    //cout << "test: " << test << endl;

    return 0;
}