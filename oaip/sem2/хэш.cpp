#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Book {
    string name;
    int pages;
    int year;
};

struct hashNode {
    Book data;
    bool occupied;
};

int basicHash(int key, int size) {
    return key % size;
}

int quadraticProbing(int key, int attempt, int size) {
    return (basicHash(key, size) + attempt * attempt) % size;
}

void insert(hashNode* table, int size, Book book) {
    int attempt = 0;
    int index = basicHash(book.pages, size);

    while (table[index].occupied && attempt < size) {
        attempt++;
        index = (basicHash(book.pages, size) + attempt * attempt) % size;
    }

    if (attempt < size) {
        table[index].data = book;
        table[index].occupied = true; // Указываем, что ячейка теперь занята
    }
    else {
        cout << "Ошибка: Таблица переполнена\n";
    }
}

int searchInHashTable(hashNode* table, int size, int key) {
    int attempt = 0;
    int i = basicHash(key, size);
    int firstIndex = i;

    while (table[i].occupied && attempt < size) {
        if (table[i].data.pages == key) {
            return i; // Найден элемент
        }

        attempt++;
        i = (basicHash(key, size) + attempt * attempt) % size;

        if (i == firstIndex) break; // Вернулись в начальную точку, завершаем поиск
    }
     return -1; // Элемент не найден
}
void HashTable(hashNode* table, int size) {
    cout << "\nХеш-таблица:\n";
    for (int i = 0; i < size; i++) {
        cout << "H[" << i << "] = ";
        if (table[i].occupied) {
            cout << "Кол-во страниц: " << table[i].data.pages
                << ", Название: " << table[i].data.name
                << ", Год: " << table[i].data.year;
        }
        else {
            cout << "пусто";
        }
        cout << endl;
    }
}

void Array(Book* arr, int size) {
    cout << "\nИсходный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i << ": Кол-во страниц: " << arr[i].pages
            << ", Название: " << arr[i].name
            << ", Год: " << arr[i].year << endl;
    }
}

void inputBooks(Book* arr, int size) {
    cout << "Введите данные для " << size << " книг:\n";
    for (int i = 0; i < size; i++) {
        cout << "\nКнига " << i + 1 << ":\n";
        cout << "Название: ";
        cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, arr[i].name);

        cout << "Кол-во страниц: ";
        cin >> arr[i].pages;

        cout << "Год: ";
        cin.ignore(cin.rdbuf()->in_avail());
       cin>>arr[i].year;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    const int n = 9;
    const int m = 10;

    Book books[n];
    inputBooks(books, n);

    hashNode* hashTable = new hashNode[m];
    for (int i = 0; i < m; i++) {
        hashTable[i].occupied = false;
    }

    for (int i = 0; i < n; i++) {
        insert(hashTable, m, books[i]);
    }

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Вывести исходный массив\n";
        cout << "2. Вывести хеш-таблицу\n";
        cout << "3. Найти элемент по количеству страниц\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            Array(books, n);
            break;
        case 2:
            HashTable(hashTable, m);
            break;
        case 3: {
            int searchKey;
            cout << "Введите кол-во страниц для поиска: ";
            cin >> searchKey;
            int index = searchInHashTable(hashTable, m, searchKey);
            if (index != -1) {
                cout << "Найден элемент:\n";
                cout << "Кол-во страниц: " << hashTable[index].data.pages
                    << ", Название книги: " << hashTable[index].data.name
                    << ", Год: " << hashTable[index].data.year << endl;
            }
            else {
                cout << "Элемент с количеством страниц " << searchKey << " не найден\n";
            }
            break;
        }
        case 0:
            cout << "bye bye!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    delete[] hashTable;
    return 0;
}

