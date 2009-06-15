#ifndef _SELECT_H
#define _SELECT_H

#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;

class Select {
	int partition(int* A, int first, int last, int x) {
		int* tmp = new int[last - first + 1];
		int j=0;
		for (int i = first; i <= last; i++) {
			if (A[i] < x) {
				tmp[j] = A[i];
				j++;
			}
		}
		int xi = j; // First cell with x
		for (int i = first; i <= last; i++) {
			if (A[i] == x) {
				tmp[j] = x;
				j++;
			}
		}
		xi = ((xi + j) / 2 ) + first; // Middle cell with x
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
	void swap(int* a, int* b) {
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
	int median_of_5(int* A){
		int tmp[5] = {A[0], A[1], A[2], A[3], A[4]};
		for (int j=4;j >=2;j--) {
			int maxtmp = 0;
			for (int i=1; i<=j; i++) {
				if (tmp[i] > tmp[maxtmp]) {
					maxtmp = i;
				}
			}
			swap(&tmp[j], &tmp[maxtmp]); 
		}
		return tmp[2];
	}
	int median_of_medians(int* A, int first, int last) {
		int size = (last - first + 1);
		int* medians;
		int medians_size;
		if (size % 5 != 0) {
			medians_size = (size / 5) + 1;
			medians = new int[medians_size];
			for (int i=0; i < medians_size - 1; i++) {
				medians[i] = median_of_5(&A[first + i*5]);
			}
			medians[medians_size - 1] = A[last]; // Arbitrary member for last group
		} else {
			medians_size = size / 5;
			medians = new int[medians_size];
			for (int i=0; i < medians_size ; i++) {
				medians[i] = median_of_5(&A[first + i*5]);
			}
		}
		int x;
		if (medians_size == 5) {
			x = median_of_5(medians);
		} else if (medians_size < 5) {
			x = medians[0]; // arbitrary return value; TODO maybe important to find real median
		} else {
			x = select(medians, 0, medians_size-1, medians_size / 2);
		}
		delete[] medians;
		return x;
	}
	public:
	int select(int* A, int first, int last, int i) {
		//cout << "Searching for " << i << " between " << first << " and " << last << "\n";
		if (first == last) {
			return A[first];
		}
		int x = median_of_medians(A, first, last);
		//cout << "pivot = " << x << "\n";
		int s = partition(A, first, last, x);
		
		
		if ((s - first) >= i) {
			return select(A, first, s-1, i);
		}
		if ((s - first) == 0) { // TODO: private case, or can be generalized?
			if (i == 1) {
				return A[first];
			}
			return select(A, first+1, last, i-1);
		}
		return select(A, s, last, i - (s - first) );
	}
};
#endif // _SELECT_H
