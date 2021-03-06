// ConsoleApplication4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double compares;
double Allcompares;
double Maxcompares;

void swap(int i, int j, int *x) {
	int tmp;
	tmp = x[i];
	x[i] = x[j];
	x[j] = tmp;
}
void BubbleSort(int *A, int n) {
	for (int i = 0; i<n - 1;i++)
		for (int j = 0; j < n - 1;j++)
			if (A[j] > A[j + 1])
				swap(j, j + 1, A);
}

double line_search(int a, int* myarray, int n) {
	for (size_t i = 0; i < n; i++) {
		compares++;
		if (myarray[i] == a) {
			return i;
		}
	}
	return -1;
}

double line_search_fast(int a, int* myarray, int n) { //Переделать!
	for (size_t i = 0; (i < n) && (i>0?myarray[i]>myarray[i-1]:1); i++) {
		compares++;
		if (myarray[i] == a) {
			return i;
		}
	}
	return -1;
}

double bin_search(int a, int* myarray, int n) {
	double left = 0, right = n, search = -1;
	compares++;
	while (left <= right) // пока левая граница не "перескочит" правую
	{
		int center = (left + right) / 2; // ищем середину отрезка
		compares++;
		if (a == myarray[center]) {  // если ключевое поле равно искомому
			return center;     // мы нашли требуемый элемент,
			break;            // выходим из цикла
		}
		compares++;
		if (a < myarray[center])     // если искомое ключевое поле меньше найденной середины
			right = center - 1;  // смещаем правую границу, продолжим поиск в левой части
		else                  // иначе
			left = center + 1;   // смещаем левую границу, продолжим поиск в правой части
	}
	return -1;
}

double blocksearch(int a, int* myarray, int n)
{
	char found = -1;
	int blocks = 4, i = 0, j = n;

	while ((n!=0)&&(i<n)&&(found==-1))
	{
		int last = i + (j / blocks);
		if (last > n) {
			last = n-1;
		}
		if (myarray[last] >= a) {
			found=line_search(a, myarray+i, n / blocks)+i;
		}
		i += n / blocks;
	}
	return found;
}

void tester(const char name[256], double f(int, int*, int), char sorted) {
	srand(time(NULL));
	puts("----------------------------");
	for (int i = 50; i <= 450; i += 50) {
		printf("\n   *** %s search (%i elements)***\n", name, i);
		compares = 0; Allcompares = 0; Maxcompares = 0;
		int k;

		for (k = 0; k < 50; k++)
		{
			compares = 0;
			int *myarray = (int *)malloc(i * sizeof(int));
			for (int j = 0; j < i; ++j) myarray[j] = (rand() % 1000);

			if (sorted) {
				BubbleSort(myarray, i);
			}

			//for (size_t k = 0; k < i; k++) printf("%i ", myarray[k]); puts(""); //Вывод массива

			f(myarray[rand() % i], myarray, i);
			Allcompares += compares;
			if (compares > Maxcompares) Maxcompares = compares;

			free(myarray);
		}

		printf("   %5.0i elements have %5.0f max compares and srednee %5.1f compares\n", i, Maxcompares, Allcompares / k);
	}
	puts("\n----------------------------\n");
}

int main()
{
	tester("Linear", line_search, false);
	tester("Fast Linear", line_search_fast, false); //Переделать!
	tester("Fast Linear", line_search_fast, true);
	tester("Bin", bin_search, true);
	tester("Block", blocksearch, true);

    return 0;
}

