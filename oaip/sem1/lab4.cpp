#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    int num;
    cout << "Введите число: ";
    cin >> num;
    int temp = num;
    int count = 0;

    while (temp != 0) {
        temp = temp / 10; // считаем цифры в числе
        count++;
    }

    int* arr = new int[count];//создаем массив с размером равным кол-ву цифр
    temp = num;
    int i = 0;
    while (temp != 0) {
        int digit = temp % 10;
        arr[i++] = digit;//заполняем массив цифрами
        temp = temp / 10;
    }

    bool check = true;
    for (int i = 0; i < count / 2; i++) {
        if (arr[i] != arr[count - i - 1]) {
            check = false;
            break;
        }
    }

    if (!check) {
        cout << "Число не является палиндромом" << endl;
    } else {
        cout << "Число является палиндромом" << endl;
        //if (count % 2 == 0) {
            for (int i = 0; i < (count + 1) / 2; i++) {
                cout << arr[i];
            }
       /* }
        if (count % 2 == 1) {
            for (int i = 0; i < count / 2 + 1; i++) {
                cout << arr[i];
            }
        }*/
    }

    delete[] arr;
    return 0;
}
