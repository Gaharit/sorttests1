#include  <stdio.h>
#include <Windows.h>
#include <time.h>
#include "tests.h"
#include "for.h"

int main() {
	//��� ������ ���������� ���� �������� ����������...

	//� ����� �������� - ��������� ����� ����� �� ������������� ����� test.h
	void(*fin)(int*, int);
	printf("\nbubble_sort:\n");
	fin = bubble_sort;
	test_sort(fin);

	printf("\ninsert_sort:\n");
	fin = sort_past;
	test_sort(fin);

	printf("\nshaker_sort:\n");
	fin = shake_sort;
	test_sort(fin);
}