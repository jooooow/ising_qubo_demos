#pragma once


int GetH_QUBO(int* B, int* Q, int size);

int GetDeltaE_QUBO(int* Q, int* B, int size, int index);

void Run_QUBO_MC(int* Q, int* B, int size, double T, double T_min, double p);

void Run_QUBO_MC(int* Q, int* B, int size, double T, double p, int round);

void Run_QUBO(int* Q, int* B, int size, double T, double p, int round);
