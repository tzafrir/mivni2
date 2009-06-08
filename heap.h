#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>

class heap {
	int* tree;
	int max;
	int num_items;
	
private:
	int father(int n);
	int left(int n);
	int right(int n);
	
	void swap(int n1, int n2);
	int maxChild(int n);
	
	void siftUp(int n);
	void siftDown(int n);
	void postOrderSiftDown(int n);
	
public:
	heap(int max);
	~heap();
	enum heapResult{
		Success,
		Failure
	};
	heapResult makeHeap(const int* const input_array, int size);
	heapResult insert(int new_item);
	heapResult delMax();
	heapResult findMax(int* output);
	
	void reset();
	
	const int _num_items();
	int* heap_array();
	
	void print(int n){ // TODO: remove
		for (int i=0, j=0, k=1;i<n;i++) {
			std::cout << tree[i] << " ";
			j++;
			if (j==k) {
				j=0;
				std::cout << "\n";
				k *= 2;
			}
		}
		std::cout << "\n\n";
	}
};


#endif /* _HEAP_H */

