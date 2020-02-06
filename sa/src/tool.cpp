#include "tool.h"

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
