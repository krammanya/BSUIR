#include <iostream> 
#include <string>
#include <windows.h>
#include <algorithm>

using namespace std;

struct Tree {
	string name;
	int info;
	Tree* left, * right;
} ;

Tree* List(string na,int inf) {
	Tree* t = new Tree;   
	t->info = inf;    
	t->name = na;
	t->left = t->right = NULL; 
	return t;    
}

Tree* add(Tree* root, string na, int inf) {
    if (root == NULL) {
        // Если дерево пустое, создаем новый узел
        root = List(na, inf);
    }
    else if (inf < root->info) {
        // Если ключ меньше текущего, рекурсивно добавляем в левое поддерево
        root->left = add(root->left, na, inf);
    }
    else if (inf > root->info) {
        // Если ключ больше текущего, рекурсивно добавляем в правое поддерево
        root->right = add(root->right, na, inf);
    }
    else {
        // Если ключ уже существует, выводим сообщение и ничего не добавляем
        cout << "Такой узел уже существует!" << endl;
        return root;  // Возвращаем текущий узел, чтобы не изменять структуру дерева
    }
    return root;  // Возвращаем корень дерева
}
void Del_Tree(Tree* t) {
    if (t != NULL) {
        Del_Tree(t->left);
        Del_Tree(t->right);
        delete t;
    }
}
// Функция для поиска минимального узла в правом поддереве
Tree* minValueNode(Tree* node) {
    Tree* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}
// Функция для удаления узла из дерева
Tree* deleteNode(Tree* root, int key) {
    // Если дерево пусто, возвращаем nullptr
    if (root == nullptr) {
        return root;
    }
    // Ищем узел для удаления
    if (key < root->info) {
        root->left = deleteNode(root->left, key);  // Если ключ меньше, идем в левое поддерево
    }
    else if (key > root->info) {
        root->right = deleteNode(root->right, key);  // Если ключ больше, идем в правое поддерево
    }
    else {
        // Мы нашли узел, который нужно удалить

        // Случай 1: Узел не имеет потомков (лист)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // Случай 2: Узел имеет только одного потомка
        else if (root->left == nullptr) {
            Tree* temp = root->right;
            delete root;
            return temp;  // Возвращаем правого потомка
        }
        else if (root->right == nullptr) {
            Tree* temp = root->left;
            delete root;
            return temp;  // Возвращаем левого потомка
        }

        // Случай 3: Узел имеет двух потомков
        else {
            // Ищем минимальный узел в правом поддереве
            Tree* temp = minValueNode(root->right);

            // Копируем данные минимального узла в текущий узел
            root->info = temp->info;
            root->name = temp->name;

            // Удаляем минимальный узел в правом поддереве
            root->right = deleteNode(root->right, temp->info);
        }
    }
    return root;
}
void View_Tree(Tree* p, int level) {
    if (p) {
        View_Tree(p->right, level + 1);
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << p->info << ", " << p->name << endl;
        View_Tree(p->left, level + 1);
    }
}
//прямой обход
void RootLR(Tree* root) {
    if (root) {
        cout << root->info << ", " << root->name << endl; // Посетить узел
        RootLR(root->left);  // Рекурсивно обойти левое поддерево
        RootLR(root->right); // Рекурсивно обойти правое поддерево
    }
}
//обратный обход
void LRRoot(Tree* root) {
    if (root) {
        LRRoot(root->left);  // Рекурсивно обойти левое поддерево
        LRRoot(root->right); // Рекурсивно обойти правое поддерево
        cout << root->info << ", " << root->name << endl; // Посетить узел
    }
}
//центрированный обход
void LRootR(Tree* root) {
    if (root) {
        LRootR(root->left);  // Рекурсивно обойти левое поддерево
        cout << root->info << ", " << root->name << endl; // Посетить узел
        LRootR(root->right); // Рекурсивно обойти правое поддерев
    }
}
Tree* search(Tree* root, int key) {
    if (root == NULL) {
        cout << "Значение не найдено.\n ";
        return root;
    }
    if ( root->info == key) {
        return root;
    }
    if (key < root->info) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

Tree* Make_Blns(int n, int k, int* a, string* names) {
    if (n >= k) return nullptr;

    int m = (n + k) / 2;

    Tree* node = new Tree;
    node->info = a[m];
    node->name = names[m];

    node->left = Make_Blns(n, m, a, names);
    node->right = Make_Blns(m + 1, k, a, names);

    return node;
}
void countnodes(Tree* root, int level, int* levelcounts, int maxlevels) {
    if (root == NULL || level>=maxlevels) return;
    levelcounts[level]++;
    countnodes(root->left, level + 1, levelcounts, maxlevels);
    countnodes(root->right, level + 1, levelcounts, maxlevels);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");
    Tree* root = nullptr;
    int choice = 0;
    int n;  // Количество узлов
    int* keys = nullptr;  // Массив для хранения ключей
    string* names = nullptr;
    const int MAX_LEVELS = 100;
    int levelCounts[MAX_LEVELS] = { 0 };
    do {
        cout << "\nМеню:\n";
        cout << "1. Вывести дерево\n";
        cout << "2. Определить число узлов на каждом уровне дерева\n";
        cout << "3. Найти информацию по ключу\n";
        cout << "4. Удалить узел по ключу\n";
        cout << "5. Прямой обход дерева\n";
        cout << "6. Обратный обход дерева\n";
        cout << "7. Вывод в порядке возрастания ключа (центрированный обход)\n";
        cout << "8. Добавить узел\n";
        cout << "9. Создать сбалансированное дерево\n";
        cout << "10. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Дерево:\n";
            if (root) {
                View_Tree(root, 0);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 2:
            if (root) {
                for (int i = 0; i < MAX_LEVELS; i++) levelCounts[i] = 0; //сброс для повторного вызова 
                countnodes(root, 0, levelCounts, MAX_LEVELS);
                for (int i = 0; i < MAX_LEVELS; i++) {
                    if (levelCounts[i] > 0) {
                        cout << "Уровень " << i << ": " << levelCounts[i] << " узлов" << endl;
                    }
                }
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 3:
            if (root) {
                int key;
                cout << "Введите ключ для поиска:\n";
                cin >> key;
                Tree* result = search(root, key);
                if (result != nullptr) {
                    cout << "Найден узел с ключом " << key << ": " << result->info << ", " << result->name << endl;
                }
                else {
                    cout << "Узел с ключом " << key << " не найден!" << endl;
                }
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 4:
            if (root) {
                int key;
                cout << "Введите ключ узла для удаления: ";
                cin >> key;
                Tree* node = search(root, key);
                if (node) {
                    root = deleteNode(root, key);
                    cout << "Узел с ключом " << key << " удалён.\n";
                }
                else {
                    cout << "Узел с ключом " << key << " не найден.\n";
                }
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 5:
            cout << "Прямой обход дерева:\n";
            if (root) {
                RootLR(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 6:
            cout << "Обратный обход дерева:\n";
            if (root) {
                LRRoot(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 7:
            cout << "Центрированный обход:\n";
            if (root) {
                LRootR(root);
            }
            else {
                cout << "Дерево пустое.\n";
            }
            break;
        case 8:
            if (keys) delete[] keys;
            if (names) delete[] names;
            cout << "Введите количество узлов:\n";
            cin >> n;
            if (n <= 0) {
                cout << "Неверное количество узлов.\n";
                break;
            }

            // Выделяем память для ключей и имён
            keys = new int[n];
            names = new string[n];

            for (int i = 0; i < n; i++) {
                int key;
                string name;

                cout << "Введите ключ для узла " << i + 1 << ": ";
                cin >> key;
                cin.ignore(); // очищаем буфер
                cout << "Введите имя для узла " << i + 1 << ": ";
                getline(cin, name);

                keys[i] = key;
                names[i] = name;

                root = add(root, name, key); // добавляем в дерево
            }

            cout << "Добавление завершено.\n";
            break;
        case 9:
            if (keys != nullptr && names != nullptr) {
                // Сортировка вставками с учетом имён
                for (int i = 1; i < n; i++) {
                    int key = keys[i];
                    string name = names[i];
                    int j = i - 1;
                    while (j >= 0 && keys[j] > key) {
                        keys[j + 1] = keys[j];
                        names[j + 1] = names[j];
                        j--;
                    }
                    keys[j + 1] = key;
                    names[j + 1] = name;
                }
                Del_Tree(root); // Удаляем старое несбалансированное дерево
                // Строим сбалансированное дерево
                root = Make_Blns(0, n, keys, names);
                cout << "Сбалансированное дерево построено.\n";
            }
            else {
                cout << "Сначала добавьте узлы.\n";
            }
            break;
        case 10:
            cout << "Выход из программы.\n";
            delete[] keys; 
            delete[] names;// Освобождаем память
            break;
        default:
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    } while (choice != 10);

    Del_Tree(root);
    return 0;
}
