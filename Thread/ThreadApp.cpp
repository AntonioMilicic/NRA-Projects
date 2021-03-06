#include "stdafx.h"

#define EXECUTENUMBER 5000000

using namespace std;

void loopMethod(double);

int main()
{
	int j = 0, i = 0, thAvgExecute = 0;
	thread th[16];	

	// 1 Thread
	cout << "Execution of 1 thread" << endl;

	while (i++ < 5) {
		clock_t timer = clock();

		th[0] = thread(loopMethod, 16 * EXECUTENUMBER);
		th[0].join();

		timer = clock() - timer;
		thAvgExecute += timer;
		cout << i << ". pass time in ms: " << timer << endl;
	}

	cout << endl << "1 thread average execute time for 5 runs: " << thAvgExecute / 5 << " ms" << endl;

	i = 0;
	thAvgExecute = 0;

	// 2 Threads
	cout << endl << "Execution of 2 threads" << endl;

	while (i++ < 5) {
		clock_t timer = clock();

		for (int j = 0; j < 2; j++) {
			th[j] = thread(loopMethod, 8 * EXECUTENUMBER);
		}
		for (int j = 0; j < 2; j++) {
			th[j].join();
		}

		timer = clock() - timer;
		thAvgExecute += timer;

		cout << i << ". time elapse in ms: " << timer << endl;
	}

	cout << endl << "2 threads average execute time for 5 runs: " << thAvgExecute / 5 << " ms" << endl;

	i = 0;
	thAvgExecute = 0;
	
	// 4 Threads
	cout << endl << "Execution of 4 threads" << endl;

	while (i++ < 5) {
		clock_t timer = clock();

		for (int j = 0; j < 4; j++) {
			th[j] = thread(loopMethod, 4 * EXECUTENUMBER);
		}
		for (int j = 0; j < 4; j++) {
			th[j].join();
		}

		timer = clock() - timer;
		thAvgExecute += timer;

		cout << i << ". time elapse in ms: " << timer << endl;
	}

	cout << endl << "4 threads average execute time for 5 runs: " << thAvgExecute / 5 << " ms" << endl;

	i = 0;
	thAvgExecute = 0;

	// 8 Threads
	cout << endl << "Execution of 8 threads" << endl;

	while (i++ < 5) {
		clock_t timer = clock();

		for (int j = 0; j < 8; j++) {
			th[j] = thread(loopMethod, 2 * EXECUTENUMBER);
		}
		for (int j = 0; j < 8; j++) {
			th[j].join();
		}

		timer = clock() - timer;
		thAvgExecute += timer;

		cout << i << ". time elapse in ms: " << timer << endl;
	}

	cout << endl << "8 threads average execute time for 5 runs: " << thAvgExecute / 5 << " ms" << endl;

	i = 0;
	thAvgExecute = 0;

	// 16 Threads
	cout << endl << "Execution of 16 threads" << endl;

	while (i++ < 5) {
		clock_t timer = clock();

		for (int j = 0; j < 16; j++) {
			th[j] = thread(loopMethod, EXECUTENUMBER);
		}
		for (int j = 0; j < 16; j++) {
			th[j].join();
		}

		timer = clock() - timer;
		thAvgExecute += timer;

		cout << i << ". time elapse in ms: " << timer << endl;
	}

	cout << endl << "16 threads average execute time for 5 runs: : " << thAvgExecute / 5 << " ms" << endl;

	char c;
	cin >> c;

	return 0;
}

void loopMethod(double t_numberOfExecutes) {
	double m_executeCounter = 0;

	// Looping and summing
	for (double i = 0; i < t_numberOfExecutes; i++) {
		m_executeCounter += i;
	}
}