#include <iostream>
#include <cmath>
using namespace std;
double square_recursive(int n, int index=1) {
    if (n == index) {
        return  sqrt(index);
    }
    return sqrt(index+square_recursive(n ,index+1));
      
}
double calc (int n) {
    double result = 0;
    for (int i = n; i >= 1; i--) {
        result = sqrt(i + result);
    }
    return result;
}
int main()
{
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите n: ";
    cin >> n;
    double y = square_recursive(n);
    cout<< "Рекурсия значение: ";
    cout << y<<endl;
    double r = calc(n);
    cout << "Обычная функция значение: ";
    cout << r;
}
