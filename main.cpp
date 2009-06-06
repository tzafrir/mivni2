#include "heap.h"
#include <assert.h>
#include <iostream>

int main() {
	srand(time(NULL));
	heap mheap(100000);
	int input[50000];
	for (int i=0;i<50000;i++) {
		input[i] = rand() % 100000;
	}
	std::cout << mheap._num_items() << " ";
	mheap.makeHeap(input, 50000);
	std::cout << mheap._num_items() << " ";
	for (int i=0; i<50000;i++) {
		mheap.insert(rand() % 100000);
		std::cout << mheap._num_items() << " ";
	}
	int a;
	mheap.findMax(&a);
	int b;
	for (int i=0;i<100000;i++) {
		mheap.findMax(&b);
		assert(b <= a);
		mheap.delMax();
		std::cout << a << " ";
		a=b;
	}
	return 0;
}
