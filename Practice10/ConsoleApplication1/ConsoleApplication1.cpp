// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <conio.h>
#include <iostream>

DWORD WINAPI ThreadFunction1(LPVOID lpParam) {
    std::cout << "Поток 1 создан.\n";

    int sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += i;
    }
    std::cout << "Поток 1: Сумма чисел от 1 до 100: " << sum << std::endl;

    return 0;
}

DWORD WINAPI ThreadFunction2(LPVOID lpParam) {
    std::cout << "Поток 2 создан.\n";

    char input;
    std::cout << "Поток 2: Введите знак: ";
    input = _getch();
    std::cout << "\nПоток 2: Вы ввели: " << input << std::endl;

    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");

    wchar_t lpszComLine[80];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Получение псевдодескриптора текущего процесса
    HANDLE hProcess = GetCurrentProcess();

    // Создание наследуемого дубликата псевдодескриптора текущего процесса
    // 4 и 5 задание
    HANDLE hInheritProcess;
    if (!DuplicateHandle(
        GetCurrentProcess(),    // дескриптор текущего процесса
        hProcess,               // исходный псевдодескриптор процесса
        GetCurrentProcess(),    // дескриптор текущего процесса
        &hInheritProcess,       // новый дескриптор процесса
        0,                      // этот параметр игнорируется
        TRUE,                   // новый дескриптор наследуемый
        DUPLICATE_SAME_ACCESS)) // доступ не изменяем
    {
        std::cerr << "Псевдодескриптор не был скопирован.\n";
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    std::cout << "Создан наследуемый дубликат псевдодескриптора текущего процесса.\n";

    std::cout << "\nВведите любой знак для начала дочернего процесса: ";
    _getch();

    // устанавливаем атрибуты нового процесса
    // 3 задание
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    wsprintf(lpszComLine, L"D:\\System programming\\10\\Practice10\\x64\\Debug\\ConsoleApplication2.exe %d", (int)hInheritProcess);

    // 1 задание
    if (!CreateProcess(
        NULL,
        lpszComLine,
        NULL,
        NULL,
        TRUE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "Новый процесс не создан.\n";
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    std::cout << "\nPID: " << pi.dwProcessId << std::endl;
    std::cout << "Дескриптор: " << pi.hProcess << std::endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    // завершение
    // 2 задание
    TerminateThread(pi.hThread, 0);
    TerminateProcess(pi.hProcess, 0);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    CloseHandle(hInheritProcess);


    // 6 и 7 задание
    HANDLE hThread1 = NULL;
    HANDLE hThread2 = NULL;
    char input;

    while (true) {
        if (hThread1 != NULL) {
            WaitForSingleObject(hThread1, INFINITE);
        }
        if (hThread2 != NULL) {
            WaitForSingleObject(hThread2, INFINITE);
        }

        std::cout << "\nВыберите действие:\n";
        std::cout << "1. Создать поток 1\n";
        std::cout << "2. Создать поток 2\n";
        std::cout << "3. Завершить поток 1\n";
        std::cout << "4. Завершить поток 2\n";
        std::cout << "q. Выйти из программы\n";
        std::cout << "Ваш выбор: ";
        std::cin >> input;

        switch (input) {
        case '1':
            if (hThread1 == NULL) {
                hThread1 = CreateThread(NULL, 0, ThreadFunction1, NULL, 0, NULL);
                if (hThread1 == NULL) {
                    std::cerr << "Не удалось создать поток 1.\n";
                }
            }
            else {
                std::cerr << "Поток 1 уже создан.\n";
            }
            break;
        case '2':
            if (hThread2 == NULL) {
                hThread2 = CreateThread(NULL, 0, ThreadFunction2, NULL, 0, NULL);
                if (hThread2 == NULL) {
                    std::cerr << "Не удалось создать поток 2.\n";
                }
            }
            else {
                std::cerr << "Поток 2 уже создан.\n";
            }
            break;
        case '3':
            if (hThread1 != NULL) {
                TerminateThread(hThread1, 0);
                CloseHandle(hThread1);
                hThread1 = NULL;
                std::cout << "Поток 1 завершен.\n";
            }
            else {
                std::cerr << "Поток 1 не был создан.\n";
            }
            break;
        case '4':
            if (hThread2 != NULL) {
                TerminateThread(hThread2, 0);
                CloseHandle(hThread2);
                hThread2 = NULL;
                std::cout << "Поток 2 завершен.\n";
            }
            else {
                std::cerr << "Поток 2 не был создан.\n";
            }
            break;
        case 'q':
            std::cout << "Выход из программы.\n";
            if (hThread1 != NULL) {
                TerminateThread(hThread1, 0);
                CloseHandle(hThread1);
            }
            if (hThread2 != NULL) {
                TerminateThread(hThread2, 0);
                CloseHandle(hThread2);
            }
            return 0;
        default:
            std::cerr << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }


    _cputs("Press any key to exit.\n");
    _getch();

    return 0;
}