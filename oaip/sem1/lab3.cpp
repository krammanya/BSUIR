// ЛР3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float S(int n, float x)
{
	float r = 1, s = 1;
	for (int k = 1; k < n; k++)
	{
		r *= k;
		s += (cos(k * x)) / r;

	}
	return s;
}

float Y(float x)
{
	return (exp(cos(x)) * cos(sin(x)));
}

int main()
{
	setlocale(LC_ALL, "RU");
	float a, b, h;
	int n = 1;
	cout << "Введите диапазон x:" << endl;
	cin >> a >> b;
	cout << "Введите разность шага h:";
	//cin >> h;
	h = (b - a) / 9.0;
	// Заголовки таблицы
	cout << setw(15) << "x="
		<< setw(15) << "n="
		<< setw(20) << "S="
		<< setw(20) << "Y="
		<< setw(30) << "Модуль:" << endl;
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
	for (float x = a; x <= b + h / 2; x += h)
	{
		n = 1;
		while (fabs(S(n, x) - Y(x)) >= 0.00001)
		{
			n++;

		}
		// Данные таблицы
		cout << setw(15) << x
			<< setw(15) << n
			<< setw(20) << S(n, x)
			<< setw(20) << Y(x)
			<< setw(30) << (fabs(S(n, x) - Y(x))) << endl;
	}
	return 0;
}

