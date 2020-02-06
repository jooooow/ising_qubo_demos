#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <string>
#include <functional>
#include <Windows.h>
#include "tool.h"
#include "sa.h"
using namespace std;

void SA_Test(string filename, int size, int trail, int sub_trail, double T, double p, int round, int correct_res);

int main()
{
	/*random64_16.txt*/
	SA_Test("F:/mat.txt", 64, 10, 10, 10000, 0.95, 60, -2838335);

	/*random1k_16.txt*/
	//SA_Test("F:/mat2.txt", 1024, 20, 4, 100000, 0.937, 50, -182208337);
	//SA_Test("F:/mat2.txt", 1024, 10, 3, 100000, 0.96, 80, -182208337);
	
	system("pause");
	return 0;
}

void SA_Test(string filename, int size, int trail, int sub_trail, double T, double p, int round, int correct_res)
{
	cout << "-------------------------------------" << endl;
	srand(time(NULL));
	int* Q = new int[size * size];
	int* B = new int[size];
	cout << "data reading.." << endl;
	ReadMatrixFromFile(filename, Q, size);
	MartixMirror(Q, size);

	cout << "SA..." << endl << endl;
	int min = 0;
	int avg = 0;
	int tts = 0;
	int t = 0;
	int success_cnt = 0;
	double success_rate = 0;
	int time_avg = 0;
	for (int j = 0; j < trail; j += 1)
	{
		avg = 0;
		min = 0;
		DWORD k = ::GetTickCount();
		for (int i = 0; i < sub_trail; i++)
		{
			GenerateRandArray(B, 0, 1, size);
			Run_QUBO(Q, B, size, T, p, round);
			int H = GetH_QUBO(B, Q, size);
			avg += (H - avg) / (i + 1);
			if (H < min) min = H;
			//cout << "    H : " << H << " " << min << " " << avg << " " << i << endl;
		}
		t = ::GetTickCount() - k;
		time_avg += (t - time_avg) / (j + 1);
		cout << "trail[" << j << "] ans : " << min << " time : " << t << "ms" << endl << endl;
		if (min == correct_res)
			success_cnt++;
	}
	success_rate = success_cnt / (double)trail;
	tts = log(1 - 0.99) / log(1 - success_rate) * time_avg / 1000.0;
	cout << "success_rate : " << success_rate * 100 << "%" << endl;
	cout << "avg_time     : " << time_avg << "ms" << endl;
	cout << "tts          : " << tts << "s" << endl;
	cout << "-------------------------------------" << endl;

	delete[] Q;
	Q = nullptr;
	delete[] B;
	B = nullptr;
}
