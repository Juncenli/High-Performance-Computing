#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>


using namespace std;

#define PI 3.14159265





int main()
{
    int i, terms;
    float x, sum, t, temp;
    cout<<"Enter the value for x : ";
    cin>>x;
    cout<<"Enter the value for terms : ";
    cin>>terms;


    temp = x;
    // set input to 10 if input is too small
    if (terms < 10) {
        cout << "Too few terms. Setting minTerms to 10." << endl;
        terms = 10;
    }
    temp = temp * PI / 180;
    t = temp;
    sum = temp;

    auto start = chrono::steady_clock::now();
    /* Loop to calculate the value of Sine */
    for (i = 1; i <= terms; i++)
    {
        t = (t * (-1) * temp * temp)/(2 * i * (2 * i + 1));
        sum = sum + t;
    }

    // Get ending timepoint
    auto end = chrono::steady_clock::now();


    cout << "(Float)Using a Taylor/Maclaurin series expansion: the sine of "<< setprecision(7) << x << " degrees is " << setprecision(7) << sum << endl;

    float result = sin (x * PI / 180);

    cout << "(Float)Using cmath sine to test: the sine of "<< setprecision(7) << x << " degrees is " << setprecision(7) << result << endl;

    cout << "Time taken by function: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;

    return 0;
}
