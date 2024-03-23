// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <conio.h>
#include <iostream>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");

	int value = atoi(argv[1]);
	std::cout << "Полученное значение: " << value << std::endl;
	value *= 5;
	std::cout << "Результат вычисления: " << value << std::endl;

	HANDLE hThread;	
	hThread = (HANDLE)atoi(argv[1]);

	char c;
	while (true) {
		std::cout << "\nВведите 't' для завершения процесса: ";
		c = _getch();
		if (c == 't') {
			std::cout << "t\n";
			break;
		}
	}

	TerminateThread(hThread, 0);
	CloseHandle(hThread);

	std::cout << "Press any key to exit.\n";
	_getch();
	return 0;
}