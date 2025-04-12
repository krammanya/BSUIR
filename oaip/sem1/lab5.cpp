#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");

    int n, m;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите количество столбцов: ";
    cin >> m;

    int** numbers = new int* [n];
    for (int i = 0; i < n; i++) {
        numbers[i] = new int[m];
    }

    std::cout << "Введите элементы матрицы:"<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> numbers[i][j];
        }
    }

    cout << "Матрица:"<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << numbers[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Индексы \"особых\" элементов для элемента одновременно наименьшего в строке и наибольшего в столбце:"<<endl;
   //для наименьшего в строке и наибольшего в столбце
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool is_min_row = true;
            bool is_max_col = true;

            for (int k = 0; k < m; k++) {
                if (numbers[i][j] >numbers[i][k]) {
                    is_min_row = false;
                    break;
                }
            }

            for (int k = 0; k < n; k++) {
                if (numbers[k][j] > numbers[i][j]) {
                    is_max_col = false;
                    break;
                }
            }

            if (is_min_row && is_max_col) {
                cout << "(" << i << ", " << j << ")"<<endl;
            }
        }
    }
    // для наибольшего в строке и наименьшего в столбце
    cout << "Индексы \"особых\" элементов для элемента одновременно наибольшего в строке и наименьшего в столбце:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool is_max_row = true;
            bool is_min_col = true;
            for (int k = 0; k < m; k++) {
                if (numbers[i][j] < numbers[i][k]) {
                    is_max_row = false;
                    break;
                }
            }
            for (int k = 0; k < n; k++) {
                if (numbers[i][j] > numbers[k][j]) {
                    is_min_col = false;
                    break;
                }
            }
            if (is_max_row && is_min_col) {
                cout << "(" << i << "," << j << ")" << endl;
            }
        }
    }
    return 0;
}