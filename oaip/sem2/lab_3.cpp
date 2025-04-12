#include <iostream>

using namespace std;

struct spis {
    int info;
    spis* prev, * next;
};

// создаем список с одним узлом

void create(spis **begin, spis **end, int in ) {
    spis* t = new spis;
    t->info = in;
    t->next = t->prev = NULL;
    *begin=*end=t; //указатели на начало и конец списка указывают на новый узел
}

spis* add(int atbeginning, spis** b, spis** e, int in) {
    spis* t = new spis;
    t->info = in;
    if (atbeginning==0) { //если добавляем в начало
        t->next = *b; // Новый узел указывает на текущий первый узел
        t->prev = NULL;  // У нового узла нет предыдущего узла
        if (*b!= NULL) {  // Если список не пуст
            (*b)->prev = t; // У первого узла теперь есть указатель на новый узел
        }
        *b = t;  // Обновляем указатель на первый узел
    } 
    else { // Если мы добавляем в конец
        t->next = NULL;  // Новый узел будет последним
        t->prev = *e;  // Новый узел указывает на текущий последний узел
        if (*e != NULL) {  // Если список не пуст
            (*e)->next = t; // У последнего узла теперь есть указатель на новый узел
        }
        *e = t;
    }

    return t;
}

void view(int position, spis* t) {
    while (t != NULL) {
        cout << t->info << endl;
        if (position == 0) {
            t = t->next;
        }
        else {
            t = t->prev;
        }
    }
}

void del(spis** b) {
    spis* current = *b;
    while (current != NULL) {
        spis* next = current->next;
        delete current;
        current = next;
    }
    *b = NULL;
}

void elements(spis** head, spis** end) { 
    spis* current = *head;

    while (current != NULL) {
        if (current->info % 10 == 5) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            else {
                *head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            else {
                *end = current->prev;
            }
            spis* temp = current;
            current = current->next;
            delete temp;
        }
        else
            current = current->next;
    }
   
}

int main()
{
    setlocale(LC_ALL, "ru");
    spis *begin = NULL;
    spis* end = NULL;
    int in, addposition, choice;
    char str[2][10] = { "Begin","End" };
    while (true) {
        cout << "\nСоздать  список- 1\nДобавить элемент в список - 2\nПросмотр очереди - 3\nУдалить очередь - 4 \nЗадание- 5\nВыход - 0  "<<endl;
        cin >> choice;
        switch (choice) {
        case 1:
            if (begin != NULL) {
                cout << "Очистите память!\n";
                break;
            }
            cout << "Begin info=";
            cin >> in;
            create(&begin, &end, in);
            break;
        case 2:
            cout << "Info=";
            cin >> in;
            cout << "Добавить в начало-0, добавить в конец-1: ";
            cin >> addposition;
            add(addposition, &begin, &end, in);
            spis* t;
            if (addposition == 0) t = begin;
            else t = end;
            cout << "Добавить в " << str[addposition] << " " << t->info << endl;
            break;
        case 3:
            if (!begin) {
                cout << "Очередь пуста!" << endl;
                break;
            }
            cout << "Просмотр с начала-0, просмотр с конца-1:";
            cin >> addposition;
            if (addposition == 0) {
               t = begin;
                cout << "--Начало--" << endl;
            }
            else {
               t = end;
                cout << "--Конец--" << endl;
            }
            view(addposition, t);
            break;
        case 4:
            del(&begin);
            cout << "Память очищена!" << endl;
            end = NULL;//сброс указателя на конец после удаления
            break;
        case 5:
            elements(&begin, &end);
            break;
        case 0:
            if (begin != NULL) {
                del(&begin);
            }
            return 0;
        default:
            cout << "Неверный ввод." << endl;
        }
    }
}
