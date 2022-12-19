#include <iostream>
#include <stdlib.h>
#include <omp.h>

//声明我用std这个库
using namespace std;

int main()
{
        // Input
    long darts;
    int thread_num;
    cout << "Number of threads: ";
    cin >> thread_num;

    cout << "number of “darts” thrown: ";
    cin >> darts;

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    long number_in_circle, i;
    double x, y;
    unsigned short xi[3];


    omp_set_num_threads(thread_num);
    
    //thread_number_in_circle local varible
    #pragma omp parallel 
    {
        number_in_circle = 0;
        xi[0] = 1;
        xi[1] = 1;
        xi[2] = omp_get_thread_num();
        //reduction
        #pragma omp for firstprivate(xi) private(x, y) reduction(+: number_in_circle)
        for (i = 0;  i < darts; i++) {
            x = erand48(xi);
            y = erand48(xi);
            if (x * x + y * y < 1.0) {
                number_in_circle++;
            }
        }
    }


     // Stores the estimated value of PI
    double pi = 4.0 * ((double)number_in_circle / (double)(darts));
    //must use this way to measure time
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    // Prints the value in pi
    cout << "Final Estimation of Pi = "<< pi << endl;
    cout << "Time taken by function: "  << exec_time << "seconds" << endl;
    return 0;
}