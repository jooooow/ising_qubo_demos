#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <string>
#include <functional>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define N 1024
#define S 1

void ReadArrayFromFile(string filename, int* data, int size);
void ReadMatrixFromFile(string filename, int* data, int size);
void MartixMirror(int* data, int size);
int GetRandom(int min, int max);
void GenerateRandArray(int* arr, int min, int max, int size);
void ShowArray(string name, int* arr, int size);

int GetH_QUBO(int* B, int* Q, int size);
int GetDeltaE_QUBO(int* Q, int* B, int size, int index);
void Run_QUBO(int* Q, int* B, int size, double T, double T_min, double p);
void Run_QUBO(int* Q, int* B, int size, double T, double p, int round);
void Run_QUBO2(int* Q, int* B, int size, double T, double p, int round);
void Run_QUBO(int* Q, int* B, int size, double T, double p, int round, int sub_round);

int main()
{
	srand(time(NULL));
	int* Q = new int[N * N];
	int* B = new int[N];
	vector<int> res;
	cout << "reading.." << endl;
	ReadMatrixFromFile("F:/mat2.txt", Q, N);
	MartixMirror(Q, N);
	//cout << Q[1024 * 1022 + 0] << "," << Q[1024 * 1023 + 1023] << endl;
	cout << "SA..." << endl;
	int min = 0;
	int avg = 0;
	int t = 0;
	for (int i = 0; i < S; i++)
	{
		GenerateRandArray(B, 0, 1, N);
		DWORD k = ::GetTickCount();
		Run_QUBO2(Q, B, N, 100000, 0.98, 200);
		//res.push_back(GetH_QUBO(B, Q, N));
		int H = GetH_QUBO(B, Q, N);
		avg = avg + (H - avg) / (i + 1);
		if (H < min)
			min = H;
		t = ::GetTickCount() - k;
		cout << "H : " << H << " " << min << " " << avg << " " << t << "ms" << " " << i << endl;
	}
	cout << "res : " << min << endl;
	//ShowArray("binary", B, N);
	//cout << "H : " << GetH_QUBO(B, Q, N) << endl;
	//cout << "avg : " << accumulate(res.begin(), res.end(), 0) / (double)S << endl;

	delete[] Q;
	Q = nullptr;
	delete[] B;
	B = nullptr;
	system("pause");
	return 0;
}

void Run_QUBO(int* Q, int* B, int size, double T, double T_min, double p)
{
	while (T > T_min)
	{
		int i = GetRandom(0, N - 1);
		int delta_e = GetDeltaE_QUBO(Q, B, size, i);
		if (delta_e < 0)
			B[i] = 1 - B[i];
		else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
			B[i] = 1 - B[i];
		T *= p;
	}
}

void Run_QUBO(int* Q, int* B, int size, double T, double p, int round)
{
	while (round)
	{
		int i = GetRandom(0, N - 1);
		int delta_e = GetDeltaE_QUBO(Q, B, size, i);
		if (delta_e < 0)
			B[i] = 1 - B[i];
		else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
			B[i] = 1 - B[i];
		T *= p;
		round--;
	}
}

void Run_QUBO2(int* Q, int* B, int size, double T, double p, int round)
{
	while (round)
	{
		for (int i = 0; i < size; i++)
		{
			int delta_e = GetDeltaE_QUBO(Q, B, size, i);
			if (delta_e < 0)
				B[i] = 1 - B[i];
			else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
				B[i] = 1 - B[i];
		}
		T *= p;
		round--;
	}
}

void Run_QUBO(int* Q, int* B, int size, double T, double p, int round, int sub_round)
{
	while (round)
	{
		int temp = sub_round;
		while (temp)
		{
			int i = GetRandom(0, N - 1);
			int delta_e = GetDeltaE_QUBO(Q, B, size, i);
			if (delta_e < 0)
				B[i] = 1 - B[i];
			else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
				B[i] = 1 - B[i];
			T *= p;
			temp--;
		}
		round--;
	}
}

int GetH_QUBO(int* B, int* Q, int size)
{
	int h = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			h += Q[i*size + j] * B[i] * B[j];
		}
	}
	return h;
}

int GetDeltaE_QUBO(int* Q, int* B, int size, int index)
{
	int delta_e = 0;
	int temp_b = B[index] == 0 ? 1 : -1;
	delta_e = temp_b * Q[index * size + index];
	for (int j = 0; j < size; j++)
	{
		if (j == index)
			continue;
		delta_e += temp_b * Q[index * size + j] * B[j];
	}
	return delta_e;
}

int GetRandom(int min, int max)
{
	return round((rand() / (double)RAND_MAX) * (max - min)) + min;
}

void GenerateRandArray(int* arr, int min, int max, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = GetRandom(min, max);
	}
}

void ShowArray(string name, int* arr, int size)
{
	cout << name << " : ";
	for (int i = 0; i < size; i++)
	{
		printf("%5d", arr[i]);
	}
	printf("\n");
}

void ReadArrayFromFile(string filename, int* data, int size)
{

}

void ReadMatrixFromFile(string filename, int* data, int size)
{
	ifstream in;
	in.open(filename);
	char ch;
	string num_str = "";
	int num = 0;
	in >> noskipws;

	int i = 0;
	int j = 0;
	while (!in.eof() && i < size)
	{
		in >> ch;
		if (ch == ' ')
		{
			num = atoi(num_str.c_str());
			data[i * size + j + i] = num;
			j++;
			num_str = "";
		}
		else if (ch == '\n')
		{
			j = 0;
			i++;
		}
		else if (ch == '\r')
		{

		}
		else
		{
			num_str += ch;
		}
	}
	in.close();
}

void MartixMirror(int* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			data[j * size + i] = data[i * size + j];
		}
	}
}
