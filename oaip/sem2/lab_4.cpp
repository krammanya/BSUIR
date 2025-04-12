#include<iostream>
#include<string>
using namespace std;
struct Stack {

	char info;

	Stack* next;

}*start;

Stack* OutStack(Stack* p, char* out)
{
	Stack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
}

Stack* InStack(Stack* p, int inf) {
	Stack* t = new Stack;
	t->info = inf;
	t->next = p;
	return t;
}

int Prior(char a)
{
	switch (a)
	{

	case '*': case'/': return 3;

	case'+': case'-': return 2;

	case'(':return 1;

	}
	return 0;
}

double Result(char* str)
{
	char ch, ch1, ch2;
	char chR = 'z' + 1;
	double op1, op2, result = 0;
	double array[200];
	cout << "Введите данные:" << "\n";
	for (int i = 0; str[i] != '\0'; i++)
	{
		ch = str[i];
		if (ch >= 'a' && ch <= 'z')
		{
			cout << ch << "\n";
			cin >> array[int(ch)];
		}
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		ch = str[i];

		if (!(ch == '+' || ch == '-' || ch == '*' || ch == '/'))
		{
			start = InStack(start, ch);
		}
		else
		{
			start = OutStack(start, &ch2);

			start = OutStack(start, &ch1);

			op1 = array[int(ch1)];

			op2 = array[int(ch2)];

			switch (ch)
			{
			case '+': result = op1 + op2;
				break;
			case '-': result = op1 - op2;
				break;
			case '*': result = op1 * op2;
				break;
			case '/': result = op1 / op2;
				break;
			}
			array[int(chR)] = result;
			start = InStack(start, chR);
			chR++;
		}
	}
	return result;

}

int main()
{
	setlocale(LC_ALL, "ru");
	Stack* t, * TokenStack = NULL;
	char a;
	char InStr[201], OutStr[201];
	int k = 0, l = 0;
	cout << "Введите исходное выражение" << "\n";
	cin >> InStr;
	while (InStr[k] != '\0')
	{
		if (InStr[k] >= 'a' && InStr[k] <= 'z')
		{
			OutStr[l] = InStr[k];
			l++;
		}

		if (InStr[k] == '(')
		{
			TokenStack = InStack(TokenStack, InStr[k]);
		}

		if (InStr[k] == ')')
		{
			while (TokenStack->info != '(')
			{
				TokenStack = OutStack(TokenStack, &a);
				if (!TokenStack)
				{
					a = '\0';
				}
				OutStr[l++] = a;
			}
			t = TokenStack;
			TokenStack = TokenStack->next;
			delete t;
		}

		if (InStr[k] == '*' || InStr[k] == '/' || InStr[k] == '-' || InStr[k] == '+')
		{
			while (TokenStack != NULL && Prior(TokenStack->info) >= Prior(InStr[k]))
			{
				TokenStack = OutStack(TokenStack, &a);
				OutStr[l] = a;
				l++;
			}

			TokenStack = InStack(TokenStack, InStr[k]);

		}
		k++;
	}
	while (TokenStack != NULL)
	{
		TokenStack = OutStack(TokenStack, &a);
		OutStr[l] = a;
		l++;
	}
	OutStr[l] = '\0';
	cout << "Польская запись:" << "\n";
	cout << OutStr << "\n";
	cout << "Результат: " << Result(OutStr) << "\n";

}