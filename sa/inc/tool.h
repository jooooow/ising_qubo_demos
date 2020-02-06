#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <string>
using namespace std;


void ReadArrayFromFile(string filename, int* data, int size);

void ReadMatrixFromFile(string filename, int* data, int size);

void MartixMirror(int* data, int size);

int GetRandom(int min, int max);

void GenerateRandArray(int* arr, int min, int max, int size);

void ShowArray(string name, int* arr, int size);

