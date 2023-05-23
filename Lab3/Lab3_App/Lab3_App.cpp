// Lab3_App.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string.h>

// Специфичные заголовки для использования анклава
#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Enclave_Lab3_u.h"
#define ENCLAVE_FILE _T("../Simulation/Enclave_Lab3.signed.dll")

#define BUF_LEN 100 // Длина буфера обмена между анклавом и небезопасным приложением

int main() {
	char buffer[BUF_LEN] = { 0 };

	// Активация анклава
	sgx_enclave_id_t eid;
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 };
	int updated = 0;

	// Создание анклава из бибилиотеки .dll
	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);

	// Проверка на ошибки при создании
	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return -1;
	}

	while (true) {
		printf("Input index to retrieve, or -1 to exit: \t");
		int idx = -1;
		scanf_s("%d", &idx);
		if (idx < 0) {
			return 0;
		}
		//foo(buffer, BUF_LEN, idx);
		foo(eid, buffer, BUF_LEN, idx); // + eID (ID созданного анклава)
		printf("%s\n==============================\n\n", buffer);
	}

	// Выгрузка анклава
	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
		return -1;
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
