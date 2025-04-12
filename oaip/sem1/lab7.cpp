#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Student {
    string surname;
    string groupNumber;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
};

void createFile(const string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file.close();
        cout << "Файл создан успешно.\n";
    }
    else {
        cout << "Ошибка при создании файла.\n";
    }
}

void addStudent(const string filename) {
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите номер группы: ";
    cin >> groupNumber;
    cout << "Введите оценку по физике: ";
    cin >> physicsGrade;
    cout << "Введите оценку по математике: ";
    cin >> mathGrade;
    cout << "Введите оценку по информатике: ";
    cin >> informaticsGrade;

    ofstream file(filename, ofstream::app);
    if (file.is_open()) {
        file << surname << " " << groupNumber << " "
            << physicsGrade << " " << mathGrade << " "
            << informaticsGrade << "\n";
        file.close();
        cout << "Студент добавлен успешно.\n";
    }
    else {
        cout << "Ошибка при добавлении студента.\n";
    }
}

void viewStudents(const string& filename) {
    ifstream file(filename);
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;
    if (file.is_open()) {
        while (file >> surname >> groupNumber >> physicsGrade >> mathGrade >> informaticsGrade) {
            double averageGrade = (physicsGrade + mathGrade + informaticsGrade) / 3.0;
            cout << surname << " " << groupNumber << " "
                << physicsGrade << " " << mathGrade << " "
                << informaticsGrade << " " << averageGrade << "\n";
        }
        file.close();
    }
    else {
        cout << "Ошибка при чтении файла.\n";
    }
}

void findSpecialStudents(const string& filename) {
    ifstream file(filename);
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;

    cout << "Студенты с оценкой 4 или 5 по физике и 8 или выше по другим предметам:\n";
    if (file.is_open()) {
        while (file >> surname >> groupNumber >> physicsGrade >> mathGrade >> informaticsGrade) {
            if ((physicsGrade == 4 || physicsGrade == 5) && (mathGrade >= 8 && informaticsGrade >= 8)) {
                cout << surname << " " << groupNumber << " "
                    << physicsGrade << " " << mathGrade << " "
                    << informaticsGrade << "\n";
            }
        }
        file.close();
    }
    else {
        cout << "Ошибка при чтении файла.\n";
    }
}

void editStudent(const string& filename) {
    ifstream file(filename);
    ofstream tempFile("temp.txt");
    Student student;
    string surnameToEdit;
    bool found = false;
    cout << "Введите фамилию студента для редактирования: ";
    cin >> surnameToEdit;
    if (file.is_open() && tempFile.is_open()) {
        while (file >> student.surname >> student.groupNumber >> student.physicsGrade >> student.mathGrade >> student.informaticsGrade) {
            if (student.surname == surnameToEdit) {
                found = true;
                cout << "Редактирование студента " << student.surname << ":\n";
                cout << "Введите новую оценку по физике: ";
                cin >> student.physicsGrade;
                cout << "Введите новую оценку по математике: ";
                cin >> student.mathGrade;
                cout << "Введите новую оценку по информатике: ";
                cin >> student.informaticsGrade;
            }
            tempFile << student.surname << " " << student.groupNumber << " "
                << student.physicsGrade << " " << student.mathGrade << " "
                << student.informaticsGrade << "\n";
        }
        file.close();
        tempFile.close();
        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Информация о студенте обновлена.\n";
        }
        else {
            remove("temp.txt");
            cout << "Студент с фамилией " << surnameToEdit << " не найден.\n";
        }
    }
    else {
        cout << "Ошибка при чтении или записи файла.\n";
    }
}

void deleteStudent(const string& filename) {
    ifstream file(filename);
    ofstream tempFile("temp.txt");
    Student student;
    string surnameToDelete;
    bool found = false;
    cout << "Введите фамилию студента для удаления: ";
    cin >> surnameToDelete;

    if (file.is_open() && tempFile.is_open()) {
        while (file >> student.surname >> student.groupNumber >> student.physicsGrade >> student.mathGrade >> student.informaticsGrade) {
            if (student.surname != surnameToDelete) {
                tempFile << student.surname << " " << student.groupNumber << " "
                    << student.physicsGrade << " " << student.mathGrade << " "
                    << student.informaticsGrade << "\n";
            }
            else {
                found = true;
            }
        }
        file.close();
        tempFile.close();
        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
            cout << "Студент удален.\n";
        }
        else {
            remove("temp.txt");
            cout << "Студент с фамилией " << surnameToDelete << " не найден.\n";
        }
    }
    else {
        cout << "Ошибка при чтении или записи файла.\n";
    }
}

void sortStudentsBySurname(const string& filename) {
    ifstream file(filename);
    ofstream tempFile("temp.txt");
    Student students[100];
    int count = 0;

    if (file.is_open()) {
        while (file >> students[count].surname >> students[count].groupNumber >>
            students[count].physicsGrade >> students[count].mathGrade >> students[count].informaticsGrade) {
            ++count;
        }
        file.close();

        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (students[i].surname > students[j].surname) {
                    swap(students[i], students[j]);
                }
            }
        }

        for (int i = 0; i < count; ++i) {
            tempFile << students[i].surname << " " << students[i].groupNumber << " "
                << students[i].physicsGrade << " " << students[i].mathGrade << " "
                << students[i].informaticsGrade << "\n";
        }
        tempFile.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Записи отсортированы по фамилии.\n";
    }
    else {
        cout << "Ошибка при чтении файла.\n";
    }
}

void menu() {
    const string filename = "students.txt";
    int choice;
    string groupNumber;

    do {
        cout << "Меню:\n";
        cout << "1. Создание файла\n";
        cout << "2. Просмотр записей\n";
        cout << "3. Добавление записи\n";
        cout << "4. Найти студентов по критериям\n";
        cout << "5. Редактирование\n";
        cout << "6. Удаление\n";
        cout << "7. Сортировка\n";
        cout << "8. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createFile(filename);
            break;
        case 2:
            viewStudents(filename);
            break;
        case 3:
            addStudent(filename);
            break;
        case 4:
            findSpecialStudents(filename);
            break;
        case 5:
            editStudent(filename);
            break;
        case 6:
            deleteStudent(filename);
            break;
        case 7:
            sortStudentsBySurname(filename);
            break;
        case 8:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    } while (choice != 8);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    return 0;
}