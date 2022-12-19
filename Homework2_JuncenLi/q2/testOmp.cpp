#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <iostream>

using namespace std;
int main() {
    int nthreads, tid;
    int i;
    omp_set_num_threads(3);
    #pragma omp parallel 
    {
        tid = omp_get_thread_num();
        cout << "Hello world from " << tid << endl;
        #pragma omp for private(tid, i)
        for(i = 0; i <=4; i++) {
         cout << "Iteration " << i << "by " << tid << endl;
        }
    } // all threads join master thread and terminates
}