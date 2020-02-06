#include "tool.h"
#include "sa.h"


void Run_QUBO_MC(int* Q, int* B, int size, double T, double T_min, double p)
{
	while (T > T_min)
	{
		int i = GetRandom(0, size - 1);
		int delta_e = GetDeltaE_QUBO(Q, B, size, i);
		if (delta_e < 0)
			B[i] = 1 - B[i];
		else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
			B[i] = 1 - B[i];
		T *= p;
	}
}

void Run_QUBO_MC(int* Q, int* B, int size, double T, double p, int round)
{
	while (round)
	{
		int i = GetRandom(0, size - 1);
		int delta_e = GetDeltaE_QUBO(Q, B, size, i);
		if (delta_e < 0)
			B[i] = 1 - B[i];
		else if (rand() / (double)RAND_MAX < exp(-delta_e / T))
			B[i] = 1 - B[i];
		T *= p;
		round--;
	}
}

void Run_QUBO(int* Q, int* B, int size, double T, double p, int round)
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
