﻿// ClientPassTrough.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include <iostream>

int main()
{
    FILE *file;
    fopen_s(&file ,"test.drganiev", "r + ");

    char buf[1024] = { 0 };
    fread_s(buf, 1024, sizeof(char), 1024, file);

    printf_s("FILE CONTENTS: %s\n\n", buf);

    char buf_to_write[1024] = { "---DGaniev---" };

    fseek(file, 0, 0);
    fwrite(buf_to_write, sizeof(char), 1024, file);
    fclose(file);

    getchar();

    return 0;

    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
