#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    //setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int max_length { 50 };     // Максимальная длина строки ввода
    const int max_words { 15 };      // Максимальное количество слов
    const int max_length_word { 10 };   // Максимальная длина одного слова

    char text[max_length];     // Хранилище для строки ввода
    char words[max_words][max_length_word]; // Массив для слов
    int count = 0;                  // Количество слов
    int wordIndex = 0;         // Индекс текущего символа в слове

    cout << "Введите слова: ";
    cin.getline(text, max_length); // Читаем строку ввода

    for (int i = 0; i < strlen(text); i++) {     //strlen() подсчитывает количество символов в строке
        if (text[i] == ' ') {          // Если символ — пробел, заканчиваем текущее слово
            words[count++][wordIndex] = '\0'; // Завершаем слово символом конца строки Переходим к следующему слову 
            wordIndex = 0;                  // Сбрасываем индекс текущего слова
        }
        else {
            words[count][wordIndex++] = text[i]; // Копируем символ в текущее слово
        }
    }

    // Завершаем последнее слово
    words[count++][wordIndex] = '\0';

    // Вывод всех слов
    cout << "Слова:" << endl;
    for (int i = 0; i < count; i++) {
        cout << words[i] << endl;
    }

    cout << "Количество слов: " << count << endl;

    return 0;
}