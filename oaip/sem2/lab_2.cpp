#include <iostream>
#include<windows.h>
using namespace std;
// Декларация структурного типа
struct Stack {
	int info; //данные, которые хранятся в узле
	Stack* next; //указатель на следующий узел
};

Stack* p = NULL; // Инициализация стека?????? указатель на NULL, если begin=NULL
										//то стек пустой
									

//------------ Декларации прототипов функций пользователя ---------- 
Stack* InStack(Stack*, int);
void View(Stack*);
void Del_All(Stack**);
void Sort_info(Stack* p);

//-------------- - Функция добавления элемента в Стек------------------------
Stack* InStack(Stack* p, int in) {   // р указатель на верхний объект стека
	Stack* t = new Stack;     //выделяем память
	t->info = in; //t указатель на новый объект
	t->next = p; //указатель t ссылается на верхний объект
	return t;    //возвращает указатель на новый созданный объект
}

//----------------- Функция просмотра Стека---------------------------------- 
void View(Stack* p) {//p указатель на вершину стека
	Stack* t =p;// t временный указатель
	while (t != NULL) {
		cout << " " << t->info << endl;
		t = t->next;    // Переходим к следующему узлу
	}
}

//----------------------- Функция освобождения памяти ----------------------- 
void Del_All(Stack** p) {
	while (*p != NULL) {
		Stack* t = *p;
		*p = (*p)->next; //Скобки в (*p) необходимы для правильного разыменования указателя на указатель
		delete t;
	}
}

//----------------------- Функция сортировки  -----------------------
// обмен информацией (2 способ)
void Sort_info(Stack* p) { //указатель p, который указывает на вершину стека.
	Stack* t = NULL, * t1; //t — указатель, который будет использоваться для отслеживания конца отсортированной части стека.
	int r;//временная переменная для хранения значений при обмене.
	do {
		for(t1=p;t1->next!=t;t1=t1->next)   //t1 — указатель, который будет использоваться для прохода по стеку.
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info=t1->next->info;
				t1->next->info = r;
			}
		t = t1; // после завершения цикла, чтобы t указывал на последний обработанный узел 
		        // и пошел на следующий круг do-while
	} while (p->next != t); // пока указатель t не совпадает с next верхнего узла стека p.
}

//-----------------Функция удаления элементов которые заканчиваются на 5------------

void elements(Stack*& p) { // p — ссылка на указатель на вершину

	// Удаляем элементы с 5 в конце на вершине стека
	while (p != NULL && p->info % 10 == 5) { //проверяем певый элемент
		Stack* temp = p;
		p = p->next;
		delete temp;
	}

	// Если стек стал пустым, завершаем работу
	if (p == NULL) return;

	// Удаляем остальные элементы с 5 в конце
	Stack* t = p;
	while (t->next != NULL) {
		if (t->next->info % 10 == 5) {
			Stack* temp = t->next;
			t->next = t->next->next;
			delete temp;
		}
		else {
			t = t->next; // Переход к следующему элементу
		}
	}
}

//Функция меню
void Menu() {
	int choice,in,n,i;
	while(true){
		cout << "\nMenu:\n";
		cout << "1. Добавьте рандомные элементы в стек\n";
		cout << "2. Просмотреть стек\n";
		cout << "3. Удалить элементы заканчивающиеся на 5\n";
		cout << "4. Сортировать стек\n";
		cout << "5. Удалить все элементы\n";
		cout << "6.Выход\n";
		cout << "Выберите функцию: ";
		cin >> choice;
		Stack* begin = NULL;
		switch (choice) {
		case 1: 
			if ( p != NULL) {
				// Если создаем новый стек, должны освободить память, занятую предыдущим
				cout << "Освободите память!" << endl;
				break;
			}
			cout << "Input kol=";
			cin >> n;
			for (i = 1; i <= n; i++) {
				in = rand()%20;
				p = InStack(p, in);
			}
			break;
		case 2:
			if (p==NULL) {
				cout << "Стек пуст!" << endl;
				break;
			}
			cout << "Элементы стека:\n";
			View(p);
			break;
		case 3:
			

			// Создаём стек: 35 → 12 → 25 → 40 → 15
			/*begin = InStack(begin, 10);
			begin = InStack(begin, 10);
			begin = InStack(begin, 15);
			begin = InStack(begin, 15);
			begin = InStack(begin, 15);*/

			//cout << "Стек до удаления: ";
			View(begin);

			//// Вызываем функцию удаления элементов
			elements(begin);

			cout << "Стек после удаления: ";
			View(begin);

			break;
		case 4:
			Sort_info(p); 
			break;
		case 5:
			Del_All(&p);
			cout << "Все элементы удалены!\n";
			break;
		case 6:
			cout << "Выход:\n";
			Del_All(&p);
			return;
		default:
			cout << "Неверный ввод! Введите еще раз.\n";
		}
	} 
}

int main()
{
	setlocale(LC_ALL, "ru");
	Menu();
	return 0;

}							

