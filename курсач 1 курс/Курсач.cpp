#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
const int max_records = 100;

struct Information {
	char facultativ [50];
	char prepod [50];
	char day [20];
	int count_of_students;
};

void writeToReport(ofstream& report, const char* facultativ, const char* prepod, const char* day, int count_of_students) {
	report << left << setw(25) << facultativ << setw(25)
		<< prepod << setw(25)
		<< day << setw(45)
		<< count_of_students << endl;
}
void viewInformation(const char* filename) {
	ifstream file(filename, ios::binary);
	ofstream report("report.txt", ios::app);
	Information plan;

	if (!file.is_open()) {
		cout << "Ошибка при открытии файла.\n";
		return;
	}

	cout << "\nСистема планирования факультативных занятий в университете:\n";
	cout << "---------------------------------------------------------------------------------------------------------------------------\n";
	cout << left << setw(25) << "Факультатив" << setw(25)
		<< "Преподаватель" << setw(25)
		<< "День недели" << setw(45)
		<< "Кол-во записавшихся студентов" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------\n";
	report << "\nСистема планирования факультативных занятий в университете:\n";
	report << "---------------------------------------------------------------------------------------------------------------------------\n";
	report << left << setw(25) << "Факультатив" << setw(25)
		<< "Преподаватель" << setw(25)
		<< "День недели" << setw(45)
		<< "Кол-во записавшихся студентов" << endl;
	report << "---------------------------------------------------------------------------------------------------------------------------\n";
	while (file.read((char*)&plan, sizeof(plan))) {
		cout << left << setw(25) << plan.facultativ << setw(25)
			<< plan.prepod << setw(25)
			<< plan.day << setw(45)
			<< plan.count_of_students << endl;
		writeToReport(report, plan.facultativ, plan.prepod, plan.day, plan.count_of_students);
	}
	cout << "---------------------------------------------------------------------------------------------------------------------------\n";
	file.close();
	report.close(); 
}
void createBinaryFile(const char* filename) {
	ofstream file, report;
	file.open(filename, ios::out | ios::binary);
	file.close();
	report.open("report.txt", ios::out | ios::app);
	report << " Вы создали новый файл\n";
	cout << "Файл создан\n";
}
void file_create() {
	ofstream out;
	out.open("report.txt", ios::out);
	out.close();
	cout << "Файл создан\n";
}
// Функция для вывода одного факультатива на экран
void viewOneInformation(Information info, int in) {
	if (in == 0) {
		cout << left << setw(20) << "Факультатив" << setw(20) << "Преподаватель" << setw(20)
			<< "День недели" << setw(15) << "Количество студентов" << endl;
	}
	cout << left << setw(20) << info.facultativ << setw(20) << info.prepod << setw(20) << info.day
		<< setw(15) << info.count_of_students << endl;
}

// Функция для записи информации о факультативе в отчет
void viewOneInformationReport(Information info, ofstream& report) {
	report << "\nФакультатив: " << info.facultativ << "\nПреподаватель: " << info.prepod
		<< "\nДень недели: " << info.day << "\nКоличество студентов: " << info.count_of_students << "\n";
}

void addInformation(const char* filename, Information records[], int& count) {
	Information plan;
	if (count >= max_records) {
		cout << "Достигнуто максимальное количество записей.\n";
		return;
	}
	cout << "Введите название факультатива:";
	cin.ignore();
	cin.getline(plan.facultativ, 50);
	cout << "Введите фамилию преподавателя:";
	cin.getline(plan.prepod, 50);
	cout << "Введите день недели:";
	cin.getline(plan.day, 20);
	cout << "Введите количество записавшихся студентов:";
	cin >> plan.count_of_students;
	ofstream file(filename, ios::app | ios::binary);
	if (file.is_open()) {
		file.write((char*)&plan, sizeof(plan));
		file.close();
		cout << "Информация добавлена успешно.\n";
		records[count++] = plan;
		ofstream report("report.txt", ios::app);
		if (report.is_open()) {
			report << "\nФакультатив \"" << plan.facultativ << "\" был добавлен.\n";
			report.close();
			cout << "Информация о добавлении факультатива записана в отчет.\n";
		}
		else {
			cout << "Ошибка при записи в отчет.\n";
		}
	}
	else {
		cout << "Ошибка при добавлении информации.\n";
		return;
	}
}



void LineSearchFacultativ(const char* filename) {
	ifstream file(filename, ios::binary);
	ofstream report("report.txt", ios::app);

	if (!file.is_open() || !report.is_open()) {
		cout << "Ошибка при открытии файла." << endl;
		return;
	}

	Information plan;
	char search[50];
	bool found = false;

	cout << "Введите название факультатива для поиска: ";
	cin.ignore();
	cin.getline(search, 50);
	report << "\nПоиск факультатива по названию: " << search << "\n";
	while (file.read(reinterpret_cast<char*>(&plan), sizeof(plan))) {
		if (strcmp(plan.facultativ, search) == 0) { 
			cout << "Найден факультатив: " << plan.facultativ << endl;
			cout << "Преподаватель: " << plan.prepod << endl;
			cout << "День недели: " << plan.day << endl;
			cout << "Количество записавшихся студентов: " << plan.count_of_students << endl;
			viewOneInformationReport(plan, report);  
			found = true; 
		}
	}
	if (!found) {
		cout << "Факультатив не найден." << endl;
		report << "Факультатив не найден.\n";
	}

	file.close();
	report.close();
}
// Функция сортировки по количеству студентов и записи в отчет
void sortbychoice(const char* filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла.";
		return;
	}

	Information records[max_records];
	int count = 0;
	while (file.read((char*)&records[count], sizeof(Information))) {
		count++;
	}
	file.close();

	for (int i = 0; i < count - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < count; j++) {
			if (records[min_index].count_of_students > records[j].count_of_students) {
				min_index = j;
			}
		}
		if (min_index != i) {
			Information temp = records[min_index];
			records[min_index] = records[i];
			records[i] = temp;
		}
	}

	ofstream outfile(filename, ios::binary);
	if (outfile.is_open()) {
		for (int i = 0; i < count; i++) {
			outfile.write((char*)&records[i], sizeof(Information));
		}
		outfile.close();
		cout << "Записи отсортированы по количеству записавшихся студентов.\n";
	}
	else {
		cout << "Ошибка при записи в файл.\n";
	}
	ofstream report("report.txt", ios::app);
	if (report.is_open()) {
		report << "\nЗаписи после сортировки по количеству студентов:\n";
		
		for (int i = 0; i < count; i++) {
			viewOneInformationReport(records[i], report); 
		}
		report.close();
		cout << "Данные перезаписаны в отчет.\n";
	}
	else {
		cout << "Ошибка при записи в отчет.\n";
	}
}

int getDayIndex(const char* day) {
	if (strcmp(day, "понедельник") == 0) return 0;
	if (strcmp(day, "вторник") == 0) return 1;
	if (strcmp(day, "среда") == 0) return 2;
	if (strcmp(day, "четверг") == 0) return 3;
	if (strcmp(day, "пятница") == 0) return 4;
	if (strcmp(day, "суббота") == 0) return 5;
	if (strcmp(day, "воскресенье") == 0) return 6;
	return -1;  // Ошибка, если день недели не распознан
}

// Быстрая сортировка по дням недели
void quickSortByDay(Information arr[], int left, int right) {
	if (left >= right) return;
	Information p = arr[left];
	int i = left, j = right;
	while (i <= j) {
		while (getDayIndex(arr[i].day) < getDayIndex(p.day)) i++;
		while (getDayIndex(arr[j].day) > getDayIndex(p.day)) j--;
		if (i <= j) {
			Information temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;  
			j--;
		}
	}
	if (left < j) quickSortByDay(arr, left, j);
	if (i < right) quickSortByDay(arr, i, right);
}
void quickSortByPrepod(Information arr[], int left, int right) {
	if (left >= right) return;
	Information pivot = arr[(left + right) / 2];
	int i = left, j = right;

	while (i <= j) {
		while (strcmp(arr[i].prepod, pivot.prepod) < 0) i++; 
		while (strcmp(arr[j].prepod, pivot.prepod) > 0) j--; 
		if (i <= j) {
			Information temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (left < j) quickSortByPrepod(arr, left, j);
	if (i < right) quickSortByPrepod(arr, i, right);
}
void SortInformation(const char* filename, bool sortByDay) {
	ifstream file(filename, ios::binary);
	if (!file) {
		cout << "Ошибка при открытии файла.\n";
		return;
	}
	Information records[max_records];
	int count = 0;
	while (file.read((char*)&records[count], sizeof(Information))) {
		count++;
		if (count >= max_records) break;
	}
	file.close();
	if (count == 0) {
		cout << "Файл пуст.\n";
		return;
	}
	ofstream report("report.txt", ios::app); 
	if (!report.is_open()) {
		cout << "Ошибка при открытии файла отчета.\n";
		return;
	}
	report << "\nЗаписи после сортировки: \n";
	if (sortByDay) {
		quickSortByDay(records, 0, count - 1);  // Сортировка по дням недели
		cout << "Записи отсортированы по дням недели.\n";
	}
	else {
		quickSortByPrepod(records, 0, count - 1);  // Сортировка по фамилиям преподавателей
		cout << "Записи отсортированы по фамилиям преподавателя.\n";
	}
	// Запись отсортированных данных как в файл, так и в отчет
	ofstream outfile(filename, ios::binary);
	if (outfile.is_open()) {
		for (int i = 0; i < count; i++) {
			outfile.write((char*)&records[i], sizeof(Information));
			viewOneInformationReport(records[i], report); 
		}
		outfile.close();
	}
	else {
		cout << "Ошибка при записи в файл.\n";
	}
	report.close();
	cout << "Данные перезаписаны в файл и отчет.\n";
}
// Функция бинарного поиска по фамилии преподавателя
void binarySearchByPrepod(const char* filename) {
	ifstream file(filename, ios::in | ios::binary);
	if (!file) {
		cout << "Ошибка при открытии файла.\n";
		return;
	}
	Information arr[max_records];  
	int count = 0;
	while (file.read((char*)&arr[count], sizeof(Information))) {
		count++;
		if (count >= max_records) break;
	}
	file.close();
	if (count == 0) {
		cout << "Файл пуст.\n";
		return;
	}
	char searchPrepod[50];
	cout << "Введите фамилию преподавателя для поиска: ";
	cin >> searchPrepod;
	int left = 0, right = count - 1;
	int foundIndex = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int cmp = strcmp(arr[mid].prepod, searchPrepod); 
		if (cmp == 0) {
			foundIndex = mid;
			break;
		}
		else if (cmp < 0) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	ofstream report("report.txt", ios::app);
	if (!report.is_open()) {
		cout << "Ошибка при открытии файла отчета.\n";
		return;
	}
	report << "\nРезультаты поиска преподавателя: " << searchPrepod << "\n";
	if (foundIndex == -1) {
		cout << "Преподаватель с такой фамилией не найден.\n";
		report << "Преподаватель с фамилией " << searchPrepod << " не найден.\n";
	}
	else {
		cout << "Преподаватель " << searchPrepod << " найден.\n";
		report << "Преподаватель " << searchPrepod << " найден:\n";
		// Запись всех факультативов для найденного преподавателя
		for (int i = 0; i < count; i++) {
			if (strcmp(arr[i].prepod, searchPrepod) == 0) {
				cout << "Преподаватель: " << arr[i].prepod << "\n";
				cout << "Предмет: " << arr[i].facultativ << "\n";
				cout << "День: " << arr[i].day << "\n";
				cout << "Количество студентов: " << arr[i].count_of_students << "\n\n";
				viewOneInformationReport(arr[i], report);
			}
		}
	}
	report.close(); 
}

// Функция для сортировки вставками по факультативу
void insertionSortByFacultativ(const char* filename) {
	ifstream in;
	ofstream out, file_out;
	Information info, records[100];
	int counter = 0;
	in.open(filename, ios::binary | ios::in);
	if (!in.is_open()) {
		cout << "Ошибка при открытии файла для чтения.\n";
		return;
	}
	file_out.open("report.txt", ios::out | ios::app);
	if (!file_out.is_open()) {
		cout << "Ошибка при открытии файла отчета.\n";
		return;
	}
	file_out << "\n\nВы осуществили сортировку вставками по факультативам:\n";
	while (in.read((char*)&info, sizeof(Information))) {
		records[counter++] = info;
	}
	in.close();
	for (int i = 1; i < counter; i++) {
		for (int j = i; j > 0 && strcmp(records[j - 1].facultativ, records[j].facultativ) > 0; j--) {
			Information temp = records[j];
			records[j] = records[j - 1];
			records[j - 1] = temp;
		}
	}
	out.open(filename, ios::binary | ios::trunc); 
	if (!out.is_open()) {
		cout << "Ошибка при открытии файла для записи.\n";
		return;
	}
	for (int i = 0; i < counter; i++) {
		out.write((char*)&records[i], sizeof(Information));

		// Запись в отчет информации о факультативе
		file_out << left << setw(25) << records[i].facultativ
			<< setw(25) << records[i].prepod
			<< setw(25) << records[i].day
			<< setw(45) << records[i].count_of_students << endl;
	}
	out.close();
	file_out.close();
	cout << "Сортировка завершена и данные перезаписаны в файл.\n";
}
void searchByPrepodAndDay(const char* filename) {
	Information records[max_records];
	int count = 0;
	ifstream infile(filename, ios::binary);
	if (!infile) {
		cout << "Не удалось открыть файл.\n";
		return;
	}
	while (infile.read((char*)&records[count], sizeof(Information))) {
		count++;
	}
	infile.close();
	char teacher[50];
	char day[20];
	cout << "Введите фамилию преподавателя: ";
	cin.ignore();
	cin.getline(teacher, 50);
	cout << "Введите день недели: ";
	cin.getline(day, 20);
	Information filteredRecords[max_records];
	int filteredCount = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(records[i].prepod, teacher) == 0 && strcmp(records[i].day, day) == 0) {
			filteredRecords[filteredCount] = records[i];
			filteredCount++;
		}
	}
	if (filteredCount == 0) {
		cout << "Факультативы не найдены.\n";
		return;
	}
	for (int i = 0; i < filteredCount - 1; i++) {
		for (int j = i + 1; j < filteredCount; j++) {
			if (filteredRecords[i].count_of_students < filteredRecords[j].count_of_students) {
				Information temp = filteredRecords[i];
				filteredRecords[i] = filteredRecords[j];
				filteredRecords[j] = temp;
			}
		}
	}
	ofstream report("report.txt", ios::app);
	if (!report) {
		cout << "Не удалось открыть файл отчета.\n";
		return;
	}
	report << "\nРезультаты поиска по преподавателю " << teacher << " в день " << day << ":\n";
	report << "---------------------------------------------------------------------------------------------------------------------------\n";
	report << left << setw(25) << "Факультатив" << setw(25)
		<< "Преподаватель" << setw(25)
		<< "День недели" << setw(45)
		<< "Кол-во записавшихся студентов" << endl;
	report << "---------------------------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < filteredCount; i++) {
		writeToReport(report, filteredRecords[i].facultativ, filteredRecords[i].prepod, filteredRecords[i].day, filteredRecords[i].count_of_students);
	}

	report.close();
	cout << "Факультативы преподавателя " << teacher << " в день " << day << ":\n";
	for (int i = 0; i < filteredCount; i++) {
		cout << "Факультатив: " << filteredRecords[i].facultativ << ", "
			<< "количество студентов: " << filteredRecords[i].count_of_students << endl;
	}

	cout << "Результаты поиска записаны в отчет.\n";
}
void deleteFacultativ(const char* filename) {
	ifstream file(filename, ios::binary);
	ofstream tempfile("temp.bin", ios::binary);
	ofstream report("report.txt", ios::app); 
	Information plan;
	char facultativ_delete[50];
	bool found = false;

	cout << "Введите название факультатива для удаления: ";
	cin >> facultativ_delete;

	if (file.is_open() && tempfile.is_open() && report.is_open()) {
		while (file.read((char*)&plan, sizeof(plan))) {
			bool equal = true;
			// Сравниваем название факультатива
			for (int i = 0; i < 50; i++) {
				if (plan.facultativ[i] != facultativ_delete[i]) {
					if (plan.facultativ[i] == '\0' || facultativ_delete[i] == '\0') {
						break;
					}
					equal = false;
					break;
				}
			}
			if (!equal) {
				tempfile.write((char*)&plan, sizeof(plan));
			}
			else {
				found = true; 
			}
		}
		file.close();
		tempfile.close();
		if (found) {
			remove(filename);        
			rename("temp.bin", filename);
			report << "\nФакультатив '" << facultativ_delete << "' был удален.\n";
			report << "---------------------------------------------------------------------------------------------------------------------------\n";
			cout << "Факультатив удален.\n";
		}
		else {
			remove("temp.bin"); 
			cout << "Факультатив не найден.\n";
		}
		report.close();
	}
	else {
		cout << "Ошибка при чтении или записи в файлы.\n";
	}
}
void edit(const char* filename) {
	ifstream file(filename, ios::binary);
	ofstream tempfile("temp.bin", ios::binary);
	ofstream report("report.txt", ios::app);
	Information plan;
	char edit[50];
	bool found = false;
	cout << "Введите факультатив для редактирования: ";
	cin >> edit;
	if (file.is_open() && tempfile.is_open()) {
		while (file.read(reinterpret_cast<char*>(&plan), sizeof(plan))) {
			if (strcmp(plan.facultativ, edit) == 0) { 
				found = true;
				cout << "Редактирование факультатива: " << plan.facultativ << endl;
				cout << "Введите преподавателя: ";
				cin.ignore();
				cin.getline(plan.prepod, 50);
				cout << "Введите день недели: ";
				cin.getline(plan.day, 20);
				cout << "Введите кол-во записавшихся студентов: ";
				cin >> plan.count_of_students;
			}
			tempfile.write(reinterpret_cast<char*>(&plan), sizeof(plan));
		}
		file.close();
		tempfile.close();
		if (found) {
			if (remove(filename) != 0) {
				cout << "Ошибка при удалении оригинального файла.\n";
				return;
			}

			if (rename("temp.bin", filename) != 0) {
				cout << "Ошибка при переименовании временного файла.\n";
				return;
			}

			cout << "Информация о факультативе обновлена.\n";
			if (report.is_open()) {
				report << "\nФакультатив \"" << edit << "\" был отредактирован.\n";
			}
		}
		else {
			remove("temp.bin");
			cout << "Факультатив не найден.\n";
		}
	}
	else {
		cout << "Ошибка при открытии файла.\n";
	}
	if (report.is_open()) {
		report.close();
	}
}
// Функция для сортировки факультативов преподавателя по количеству студентов (по убыванию)
void sortByStudents(Information arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int max_index = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[max_index].count_of_students < arr[j].count_of_students) {
				max_index = j;
			}
		}
		if (max_index != i) {
			Information temp = arr[max_index];
			arr[max_index] = arr[i];
			arr[i] = temp;
		}
	}
}
// Функция для вывода статистики по преподавателям
void printStatistics(const char* filename) {
	ifstream file(filename, ios::binary);
	ofstream report("report.txt", ios::app); 
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла.";
		return;
	}
	Information records[max_records];
	int count = 0;
	while (file.read((char*)&records[count], sizeof(Information))) {
		count++;
	}
	file.close();
	bool printedPrepod[max_records] = { false };
	if (report.is_open()) {
		report << "\nСтатистика по факультативам:\n";
		report << "---------------------------------------------------------------------------------------------------------------------------\n";
		report << left << setw(25) << "Преподаватель" << setw(25)
			<< "Факультатив" << setw(25)
			<< "День недели" << setw(45)
			<< "Кол-во записавшихся студентов" << endl;
		report << "---------------------------------------------------------------------------------------------------------------------------\n";
	}
	else {
		cout << "Ошибка при открытии отчета.\n";
		return;
	}

	for (int i = 0; i < count; i++) {
		bool isPrinted = false;
		for (int j = 0; j < i; j++) {
			if (strcmp(records[i].prepod, records[j].prepod) == 0) {
				isPrinted = true;
				break;
			}
		}
		if (!isPrinted) {
			cout << "Преподаватель: " << records[i].prepod << endl;
			if (report.is_open()) {
				report << "\nПреподаватель: " << records[i].prepod << endl;
			}
			Information facultyList[max_records];
			int facultyCount = 0;
			for (int j = i; j < count; j++) {
				if (strcmp(records[j].prepod, records[i].prepod) == 0) {
					facultyList[facultyCount] = records[j];
					facultyCount++;
				}
			}
			sortByStudents(facultyList, facultyCount);
			for (int j = 0; j < facultyCount; j++) {
				cout << "  Факультатив: " << facultyList[j].facultativ
					<< ", День: " << facultyList[j].day
					<< ", Количество студентов: " << facultyList[j].count_of_students << endl;
				if (report.is_open()) {
					writeToReport(report, facultyList[j].facultativ, facultyList[j].prepod, facultyList[j].day, facultyList[j].count_of_students);
				}
			}
		}
	}
	if (report.is_open()) {
		report.close();
	}
}
void popular_facultative(const char* filename) {
	ifstream file(filename, ios::in | ios::binary);
	ofstream report("report.txt", ios::app);  
	if (!file) {
		cout << "Ошибка при открытии файла.\n";
		return;
	}
	Information arr[max_records];
	int count = 0;
	while (file.read((char*)&arr[count], sizeof(Information))) {
		count++;
		if (count >= max_records) {
			cout << "Максимальное количество записей достигнуто.\n";
			break;
		}
	}
	file.close();
	if (count == 0) {
		cout << "Файл пуст.\n";
		return;
	}
	char facultatives[max_records][50]; 
	int students[max_records] = { 0 };  
	int uniqueCount = 0;  
	for (int i = 0; i < count; i++) {
		bool found = false;
		for (int j = 0; j < uniqueCount; j++) {
			if (strcmp(arr[i].facultativ, facultatives[j]) == 0) {
				students[j] += arr[i].count_of_students; 
				found = true;
				break;
			}
		}
		if (!found) {
			strcpy_s(facultatives[uniqueCount], arr[i].facultativ);
			students[uniqueCount] = arr[i].count_of_students;
			uniqueCount++;
		}
	}
	int maxStudents = 0;
	for (int i = 0; i < uniqueCount; i++) {
		if (students[i] > maxStudents) {
			maxStudents = students[i];
		}
	}
	cout << "Статистика по факультативам:\n";
	cout << "----------------------------------------\n";
	if (report.is_open()) {
		report << "\nСтатистика по факультативам:\n";
		report << "----------------------------------------\n";
	}

	for (int i = 0; i < uniqueCount; i++) {
		cout << "Факультатив: " << facultatives[i] << ", Количество студентов: " << students[i] << "\n";
		if (report.is_open()) {
			report << "Факультатив: " << facultatives[i] << ", Количество студентов: " << students[i] << "\n";
		}
	}
	cout << "\nСамые популярные факультативы (с максимальным количеством студентов: " << maxStudents << "):\n";
	if (report.is_open()) {
		report << "\nСамые популярные факультативы (с максимальным количеством студентов: " << maxStudents << "):\n";
	}

	for (int i = 0; i < uniqueCount; i++) {
		if (students[i] == maxStudents) {
			cout << "  Факультатив: " << facultatives[i] << ", Количество студентов: " << students[i] << "\n";
			if (report.is_open()) {
				report << "  Факультатив: " << facultatives[i] << ", Количество студентов: " << students[i] << "\n";
			}
		}
	}
	if (report.is_open()) {
		report.close(); 
	}
}
void menu()
{
	Information records[max_records];
	int count = 0;
	const char* filename = "facultative.txt";
	int choice;
	do {
		cout << "Меню:\n";
		cout << "1. Создание файла\n";
		cout << "2. Просмотр записей\n";
		cout << "3. Добавление записи\n";
		cout << "4. Линейный поиск по названию факультатива\n";
		cout << "5. Поиск факультатива по преподавателю и дню недели\n";\
		cout << "6. Бинарный поиск по преподавателю\n";
		cout << "7. Быстрая сортировка по дню недели\n";
		cout << "8. Сортировка выбором по количеству студентов\n";
		cout << "9. Сортировка вставками по названию факультатива\n";
		cout << "10. Статистика по преподавателям.Самый популярный факультатив.\n";
		cout << "11. Удаление записей из файла\n";
		cout << "12.Редактирование записей в файле.\n";
		cout << "13. Создание отчета в тестовом файле\n";
		cout << "14. Выход\n";
		cout << "Выберите пункт: ";
		cin >> choice;
		switch(choice){
		case 1:
			createBinaryFile(filename);
			break;
		case 2:
			viewInformation(filename);
			break;
		case 3:
			addInformation(filename,records,count);
			break;
		case 4:
			LineSearchFacultativ(filename);
			break;
		case 5:
			searchByPrepodAndDay(filename);
			break;
		case 6:
			SortInformation(filename, false);
			viewInformation(filename);
			binarySearchByPrepod(filename);
			break;
		case 7:
			SortInformation(filename, true);
			break;
		case 8:
			sortbychoice(filename);
			break;
		case 9:
			insertionSortByFacultativ(filename);
			break;
		case 10:
			printStatistics(filename);
			popular_facultative(filename);
			break;
		case 11:
			deleteFacultativ(filename);
			break;
		case 12:
			edit(filename);
			break;
		case 13:
			file_create();
			break;
		case 14:
			cout << "Выход из программы.\n";
			break;
		}
	} while (choice !=14 );
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	
	menu();
	return 0;
}

