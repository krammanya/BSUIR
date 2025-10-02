#include<iostream>
#include"longint.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	LongInt userNumber1("0");
	while (true) {
		string input1;
		cout << "Введите первое число: ";
		cin >> input1;
		
		try {
			userNumber1=LongInt (input1);
			cout << "Вы ввели: " << userNumber1 << endl;
			break;
		}
		catch (const invalid_argument& e) {
			cout << "Некорректный ввод: " << e.what() << endl;
		}
	}

	while (true) {
		cout << "\n=== Меню ===" << endl;
		cout << " 0. Выход" << endl;
		cout << " 1. Преобразование длинного целого к целому" << endl;
		cout << " 2. Сложение двух длинных целых" << endl;
		cout << " 3. Сложение длинного целого с целым" << endl;
		cout << " 4. Вычитание двух длинных целых" << endl;
		cout << " 5. Вычитание из длинного целого целого" << endl;
		cout << " 6. Произведение двух длинных целых" << endl;
		cout << " 7. Произведение длинного целого и целого" << endl;
		cout << " 8. Деление двух длинных целых" << endl;
		cout << " 9. Деление длинного целого на целое" << endl;
		cout << "10. Сравнение двух длинных целых" << endl;
		cout << "11. Сравнение длинного целого с целым" << endl;
		cout << "12. Пре- и постинкремент" << endl;
		cout << "13. Пре- и постдекремент" << endl;
		cout << "Выберите операцию (0-13): ";

		int choice;
		cin >> choice;
		if(choice==0) {
			cout << "Завершение программы.\n";
			break;
		}
		
			switch (choice) {
			case 1: {
				int result = (int)userNumber1;
				cout << "Результат преобразования к int: " << result << endl;
				break;
			}
			case 2:
			{
				cout << "Введите второе число: ";
				string input2;
				cin >> input2;
				try {
					LongInt userNumber2(input2);
					cout << "Вы ввели: " << userNumber2 << endl;
					LongInt result = userNumber1 + userNumber2;
					cout << userNumber1 << " + " << userNumber2 << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Некорректный ввод: " << e.what() << endl;
				}
				break;
			}
			case 3: {
				cout << "Введите целое число: ";
				int num;
				cin >> num;
				try {
					LongInt temp(to_string(num));
					LongInt result = userNumber1 + temp;
					cout << userNumber1 << " + " << num << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка: " << e.what() << endl;
				}
				break;
			}
			case 4: {
				cout << "Введите второе число: ";
				string input2;
				cin >> input2;
				try {
					LongInt userNumber2(input2);
					cout << "Вы ввели: " << userNumber2 << endl;
					LongInt result = userNumber1 - userNumber2;
					cout << userNumber1 << " - " << userNumber2 << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Некорректный ввод: " << e.what() << endl;
				}
				break;
			}
			case 5: {
				cout << "Введите целое число: ";
				int num;
				cin >> num;
				try {
					LongInt temp(to_string(num));
					LongInt result = userNumber1 - temp;
					cout << userNumber1 << " - " << num << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка: " << e.what() << endl;
				}
				break;
			}
			case 6: {
				cout << "Введите второе число: ";
				string input2;
				cin >> input2;
				try {
					LongInt userNumber2(input2);
					cout << "Вы ввели: " << userNumber2 << endl;
					LongInt result = userNumber1 * userNumber2;
					cout << userNumber1 << " * " << userNumber2 << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Некорректный ввод: " << e.what() << endl;
				}
				break;
			}
			case 7: {
				cout << "Введите целое число: ";
				int num;
				cin >> num;
				try {
					LongInt temp(to_string(num));
					LongInt result = userNumber1 *temp;
					cout << userNumber1 << " * " << num << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка: " << e.what() << endl;
				}
				break;
			}
			case 8: {
				cout << "Введите второе число: ";
				string input2;
				cin >> input2;
				try {
					LongInt userNumber2(input2);
					cout << "Вы ввели: " << userNumber2 << endl;
					LongInt result = userNumber1 / userNumber2;
					cout << userNumber1 << " / " << userNumber2 << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Некорректный ввод: " << e.what() << endl;
				}
				break;
			}
			case 9: {
				cout << "Введите целое число: ";
				int num;
				cin >> num;
				try {
					LongInt temp(to_string(num));
					LongInt result = userNumber1 / temp;
					cout << userNumber1 << " / " << num << " = " << result << endl;
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка: " << e.what() << endl;
				}
				break;
			}
			case 10: {
				cout << "Введите второе число: ";
				string input2;
				cin >> input2;
				try {
					LongInt userNumber2(input2);
					cout << "Вы ввели: " << userNumber2 << endl;
					userNumber1.compareWith(userNumber2); 
				}
				catch (const invalid_argument& e) {
					cout << "Некорректный ввод: " << e.what() << endl;
				}
				break;
			}
			case 11: {
				cout << "Введите целое число: ";
				int num;
				cin >> num;
				try {
					userNumber1.compareWith(num);  
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка: " << e.what() << endl;
				}
				break;
			}
			case 12: {
				cout << "Исходное число: " << userNumber1 << endl;
				cout << "++число: " << ++userNumber1 << endl;
				cout << "После инкремента: " << userNumber1 << endl;
				break;
			}
			case 13: {
				cout << "Исходное число: " << userNumber1 << endl;
				cout << "--число: " << --userNumber1 << endl;
				cout << "После декремента: " << userNumber1 << endl;
				break;
			}
			default:
				cout << "Неверный выбор операции!" << endl;
				break;
			}
	}
	return 0;
}