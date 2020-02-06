#include <iostream>
#include <time.h>
#include <math.h>
#include <numeric>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

#define N 10
#define T 1

void ShowArr(string name, int* arr, int size);
void ShowMat(string name, int* arr, int size);
void ShowVec(string name, vector<int> vec);
void MatMirror(int* arr, int size);
void GenerateC(int* C, int size);
void GenerateSpin(int* spin, int size);
int GetEnergy(int* spin, int* C, int size);
int GetHamilton(int* spin, int* h, int* J, int size);
void ShowResult(int* spin, int* C, int* h, int* J, int size);

void IsingRun(int* spin, int* h, int* J, int size, int step);

int main()
{
	int* C = new int[N] {2, 10, 3, 8, 5, 7, 9, 5, 3, 2};
	int* h = new int[N] {0};
	int* J = new int[N * N]{0};
	int* spin = new int[N];

	ShowArr("C", C, N);

	for (int i = 0; i < N; i++)
	{
		h[i] = 0;
		for (int j = i + 1; j < N; j++)
		{
			J[i * N + j] = 2 * C[i] * C[j];
		}
	}

	MatMirror(J, N);
	ShowArr("h", h, N);
	ShowMat("J", J, N);
	GenerateSpin(spin, N);

	ShowResult(spin, C, h, J, N);
	IsingRun(spin, h, J, N, 1000);
	ShowResult(spin, C, h, J, N);

	delete[] C;
	C = nullptr;
	delete[] h;
	h = nullptr;
	delete[] J;
	J = nullptr;

	system("pause");
	return 0;
}

void ShowArr(string name, int* arr, int size)
{
	cout << name << " :" << endl;
	for (int i = 0; i < size; i++)
		printf("%5d", arr[i]);
	cout << endl;
}

void ShowMat(string name, int* arr, int size)
{
	cout << name << " :" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%5d", arr[i * size + j]);
		printf("\n");
	}
	cout << endl;
}

void MatMirror(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			arr[j * size + i] = arr[i * size + j];
		}
	}
}

void GenerateC(int* C, int size)
{
	for (int i = 0; i < size; i++)
	{
		C[i] = rand() % 20;
	}
}

void GenerateSpin(int* spin, int size)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++)
	{
		spin[i] = ((rand() / (double)RAND_MAX) > 0.5 ? 1 : 0) * 2 - 1;
	}
}

int GetEnergy(int* spin, int* C, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += C[i] * spin[i];
	return sum;
}

int GetHamilton(int* spin, int* h, int* J, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += h[i] * spin[i];
		for (int j = i + 1; j < size; j++)
		{
			sum += J[i * size + j] * spin[i] * spin[j];
		}
	}
	return sum;
}

void ShowResult(int* spin, int* C, int* h, int* J, int size)
{
	vector<int> c1;
	vector<int> c2;
	for (int i = 0; i < size; i++)
	{
		if (spin[i] == 1)
			c1.push_back(C[i]);
		else if (spin[i] == -1)
			c2.push_back(C[i]);
	}
	cout << "---------------- result ----------------" << endl;
	ShowArr("spin", spin, size);
	ShowVec("c1", c1);
	ShowVec("c2", c2);
	cout << "sum c1 : " << accumulate(c1.begin(), c1.end(), 0) << "\tsum c2 : " << accumulate(c2.begin(), c2.end(), 0) << endl;
	cout << "energy : " << GetEnergy(spin, C, size) << endl;
	cout << "Hamilton : " << GetHamilton(spin, h, J, size) << endl;
	cout << "----------------------------------------" << endl << endl;
}

void ShowVec(string name, vector<int> vec)
{
	cout << name << " :" << endl;
	for (int i = 0; i < vec.size(); i++)
		printf("%5d", vec.at(i));
	cout << endl;
}

void IsingRun(int* spin, int* h, int* J, int size, int step)
{
	double t = T;
	for (int s = 0; s < step; s++)
	{
		for (int i = 0; i < size; i++)
		{
			int temp = spin[i] * -1;
			int e = h[i] * temp;
			for (int j = 0; j < size; j++)
				e += temp * J[i*size + j] * spin[j];
			e *= 2;
			if (e < 0)
				spin[i] *= -1;
			else if (rand() / (double)RAND_MAX < exp(-e / t))
				spin[i] *= -1;
		}
		t *= 0.95;
	}
}
