#include "stdafx.h"

#define MAXSIZE 64*1024*1024

using namespace std;

void getMemoryForCache(double);

void main()
{
	cout << "Started" << endl;

	for (double size = 256; size <= MAXSIZE; size <<= 1) {
		cout << (float)size / 256 << "kB \t\t\t";
		thread th(getMemoryForCache, size);
		th.join();
	}
	cout << "Finished";
	char c;
	cin >> c;
}

void getMemoryForCache(double t_size) {
	int* m_array = new int[t_size];

	auto m_before = chrono::high_resolution_clock::now();

	for (double i = 0; i < MAXSIZE; i++) {
		m_array[(i * 16) % t_size]++;
	}

	auto m_time = chrono::high_resolution_clock::now() - m_before;
	cout << m_time.count() << endl;
    
    delete[] m_array;
}