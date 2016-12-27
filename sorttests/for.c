#include  <stdio.h>
#include <Windows.h>
#include <time.h>
#include "tests.h"
#include "for.h"
void bubble_sort(int *mass, int N)
{
	if (mass != NULL) {
		int i, j, tmp;
		for (i = 0; i < N - 1; ++i) {
			for (j = 0; j < N - i - 1; ++j) {
				if (mass[j] > mass[j + 1]) {
					tmp = mass[j];
					mass[j] = mass[j + 1];
					mass[j + 1] = tmp;
				}
			}
		}
		return 1;
	}
	return 0;
}

void sort_past(int *mass, int N) {
	if (mass != NULL) {
		int tmp, i, j;
		for (i = 0; i < N - 1; ++i) {
			for (j = i; j >= 0; --j) {
				if (mass[j] > mass[j + 1])
				{
					tmp = mass[j + 1];
					mass[j + 1] = mass[j];
					mass[j] = tmp;
				}
				else {
					break;
				}
			}
		
		}
		return 1;
	}
	return 0;
}

void shake_sort(int *mass, int N) {
	if (mass != NULL) {
		int i = 0, j, tmp, left = 0, right = N - 1;

		while (right > left) {
			if (i % 2 == 0) {
				for (j = left; j < right; ++j) {
					if (mass[j] > mass[j + 1]) {
						tmp = mass[j];
						mass[j] = mass[j + 1];
						mass[j + 1] = tmp;
					}
				}
				--right;
			}
			else {
				for (j = right; j > left; --j) {
					if (mass[j - 1] > mass[j]) {
						tmp = mass[j - 1];
						mass[j - 1] = mass[j];
						mass[j] = tmp;
					}
				}
				++left;
			}

			/*for (j = 0; j < N; ++j) {
			printf("%d ", mass[j]);
			}
			printf("\n");*/
			++i;
		}
	}
}