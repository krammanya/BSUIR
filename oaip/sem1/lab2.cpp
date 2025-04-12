#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    double x, y, z, min1, min2, max, m;
    cout << "enter x:";
    cin >> x;
    cout << "enter y:";
    cin >> y;
    cout << "enter z:";
    cin >> z;
    if (x < z) {
        min1 = x;
    }
    else {
        min1 = y;
    }
    if (x < y) {
        min2 = x;
    }
    else
    {
        min2 = y;
    }
    if (x > y) {
        max = x;
    }
    else
    {
        max = y;
    }
    if (z > max) {
        max = z;
    }
    if (max == 0) {
        cout << "m=error";
    }
    m = (min1 + min2) / max * max;
    if (max != 0) {
    cout << "result m=" << m << endl;
    }
    return 0;
}

