#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "tests.h"
#include "for.h"
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_DEFAULT 15

//Этот вспомогательный метод может быть полезным ... 
void print_test_result(HANDLE hConsole, char* test_name, int correct)
{
	SetConsoleTextAttribute(hConsole, correct ? COLOR_GREEN : COLOR_RED);
	printf("%s: %s\n", test_name, correct ? "SUCCESS" : "FAIL");
	SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
}

// ... и этот тоже
void print_test_diff(HANDLE hConsole, int* expected, int* actual, int length)
{
	int i;
	printf("Expected: ");
	for (i = 0; i < length; i++)
		printf("%d\t", expected[i]);
	printf("\n Actual: ");
	for (i = 0; i < length; i++)
	{
		SetConsoleTextAttribute(hConsole, expected[i] == actual[i] ? COLOR_GREEN : COLOR_RED);
		printf("%d\t", actual[i]);
	}
	SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
	printf("\n");
}

void test_null(void(*fin)(int*, int))
{
	//Здесь напишите тест для случая когда в функцию сортировки передаётся NULL вместо массива
	int *mass = NULL;

	fin(mass, 0);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	print_test_result(hStdOut, "test_null", 1);    //(mass == NULL) ? printf("Success\n") : printf("Fail\n");
}

void test_one_element(void(*fin)(int*, int))
{
	//Здесь напишите тест для случая когда массив длины 1
	int mass[1] = { -7 };
	int sorted_mass[] = { -7 };
	int *tmp = mass;
	int i, N = 1;

	fin(mass, N);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	(mass[0] == sorted_mass[0]) ? print_test_result(hStdOut, "test_one_element", 1) : print_test_result(hStdOut, "test_one_element", 0);
	print_test_diff(hStdOut, sorted_mass, mass, N);
}

void test_two_elements(void(*fin)(int*, int))
{
	//Здесь напишите тест для случая когда массив длины 2
	int mass[2] = { 45, 12 };
	int j, N = 2;
	int sorted_mass[2] = { 12, 45 };

	fin(mass, N);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	print_test_result(hStdOut, "test_two_elements", 1);
	print_test_diff(hStdOut, sorted_mass, mass, N);
}

void test_common_even(void(*fin)(int*, int))
{
	int mass[4] = { 23, 76, -31, 78 };
	int sorted_mass[4] = { -31, 23, 76, 78 };
	int j, N = 4;

	fin(mass, N);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	print_test_result(hStdOut, "test_common_even", 1);
	print_test_diff(hStdOut, sorted_mass, mass, N);
	//Здесь напишите тест для случая когда массив произвольной чётной длины
}

void test_common_odd(void(*fin)(int*, int))
{
	int mass[5] = { 71, -3, 25, 100, -13 };
	int sorted_mass[5] = { -13, -3, 25, 71, 100 };
	int j, N = 5;

	fin(mass, N);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	print_test_result(hStdOut, "test_common_odd", 1);
	print_test_diff(hStdOut, sorted_mass, mass, N);
	//Здесь напишите тест для случая когда массив произвольной нечётной длины
}

void test_speed(void(*fin)(int*, int), int mode)
{
	int stress, i, N = 3000;
	int mass[3000];
	long start;

	switch (mode)
	{
	case 1: {
		for (i = 0; i < N; ++i) {
			mass[i] = i;
		}
	}
	case 2: {
		for (i = 0; i < N; ++i) {
			mass[i] = N - i;
		}
	}
	case 3: {
		for (i = 0; i < N; ++i) {
			mass[i] = rand() % 1000;
		}
	}
	}

	start = clock();
	fin(mass, N);
	long finish = clock();
	for (i = 0; i < N - 1; ++i) {
		if (mass[i] > mass[i + 1]) {
			printf("Fail\n");
			return 1;
		}
	}
	//Можете изменить формат вывода результатов
	printf("Elapsed time: %lf\n", ((double)(finish - start)) / CLOCKS_PER_SEC);
}

void test_sort(void(*fin)(int*, int))
{
	test_null(fin);
	test_one_element(fin);
	test_two_elements(fin);
	test_common_even(fin);
	test_common_odd(fin);

	test_speed(fin, 1);
	test_speed(fin, 2);
	test_speed(fin, 3);
}