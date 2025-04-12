#include <iostream>
#include<windows.h>
using namespace std;
int dlina_stroki(char string[]) {
    int count_elem = 0;
    while (string[count_elem] != '\0') {
        count_elem++;
    }
    return count_elem;
}
int dlina_stroki_recursive(char text[], int index = 0) {
    if (text[index] == '\0') {
        return index;
    }
    return dlina_stroki_recursive(text, index + 1);
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int max_length=100 ;
    char text[max_length];
    cout << "Введите строку: ";
    cin.getline(text, max_length);
    int count_simvols = 0;
   count_simvols= dlina_stroki(text);
   cout << "Длина строки обычная функция: ";
    cout << count_simvols<<endl;
    int count_simvols_recursive = 0;
    count_simvols_recursive = dlina_stroki_recursive(text);
    cout << "Длина строки рекурсивная функция: ";
    cout << count_simvols_recursive;
    return 0;  
}

