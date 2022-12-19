#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
    A Mutex is different than a semaphore as it is a locking mechanism while a semaphore is a signalling mechanism. 
    A binary semaphore can be used as a Mutex but a Mutex can never be used as a semaphore
*/
long number_of_tosses;
int number_of_threads;
long number_in_circle = 0;
sem_t mutex;

void *thread_handler(void *) {
    double min = -1, max = 1;
    double x, y, distance_squared;
    long thread_number_in_circle = 0;
    unsigned int seed = (unsigned)time(NULL);

    long thread_number_of_tosses = number_of_tosses / number_of_threads;
    
    for (long toss = 0; toss < thread_number_of_tosses; toss++) {
        x = min + (double) rand_r(&seed) / RAND_MAX * (max - min);
        y = min + (double) rand_r(&seed) / RAND_MAX * (max - min);
        distance_squared = x*x + y*y;
        if (distance_squared <= 1) {
            thread_number_in_circle++;
        }
    }
    //avoid race risk
    sem_wait(&mutex);
    //critical section
    number_in_circle += thread_number_in_circle;
    sem_post(&mutex);
    pthread_exit(NULL);
}

int main() {

    cout << "Number of threads: ";
    cin >> number_of_threads;
    cout << "number of “darts” thrown: ";
    cin >> number_of_tosses;

    // Get starting timepoint
    auto start = high_resolution_clock::now();
    srand( (unsigned)time(NULL) );
    // Create pthreads
    pthread_t thread_array[number_of_threads];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < number_of_threads; i++) {
        int ret = pthread_create(&thread_array[i], NULL, thread_handler, NULL);
        if (ret != 0) {
            cout << "Create pthread error!" << endl;
            exit(EXIT_FAILURE);
        } else {
            cout << "Create pthread success!" << endl;
        }
    }
    // Join pthreads
    for (int i = 0; i < number_of_threads; i++) {
        int res = pthread_join(thread_array[i], NULL);
        if (!res) {
            cout << "Thread " << i << " joined" << endl;
        } 
        else {
            cout << "Thread " << i << " join failed" << endl;
        }
    }

    sem_destroy(&mutex);

    // Print result
    double pi_estimate = 4 * number_in_circle / (double) number_of_tosses;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "pi_estimate: " << pi_estimate << endl;
    cout << "Time taken by function: " << duration.count() / 1000000.0 << "seconds" << endl;
    return 0;
}