#ifndef _SELECT_H
#define _SELECT_H

#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;

class Select {
	int partition(int* A, int first, int last, int x) {
		int* tmp = new int[last - first + 1];
		int xi = -1;
		int j=0;
		for (int i = first; i <= last; i++) {
			if (A[i] < x) {
				tmp[j] = A[i];
				j++;
			}
			if (A[i] == x) {
				xi = i;
			}
		}
		if (xi != -1) { // x is in the subarray
			tmp[j] = x;
			xi = j+first;
			j++;
		}
		for (int i = first; i <= last; i++) {
			if (A[i] > x) {
				tmp[j] = A[i];
				j++;
			}
		}
		for (int i=0; i <= last-first; i++) {
			A[first+i] = tmp[i];
		}
		delete[] tmp;
		return xi;
	}
	public:
	Select() {
		srand(time(NULL));
	}
	int select(int* A, int first, int last, int i) {
		//cout << "Searching for " << i << " between " << first << " and " << last << "\n";
		if (first == last) {
			return A[first];
		}
		int r = rand() % (last-first+1) ;
		//cout << "pivot = " << A[first+r] << "\n";
		int s = partition(A, first, last, A[first + r]);
		if ((last - s) >= i) {
			return select(A, s+1, last, i);
		}
		return select(A, first, s, i - (last - s) );
	}
};
#endif // _SELECT_H
