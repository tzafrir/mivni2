#ifndef _HEAP_H
#define _HEAP_H
#include <cstddef>

/*
 *
 *	heap.h
 *
 */

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
	heap() : tree(NULL), max(0),num_items(0) { }
	heap(int items, int* Array ,int heapmax) : tree(Array), max(heapmax),
		num_items(items) { postOrderSiftDown(0); }
	enum heapResult{
		Success,
		Failure
	};
	heapResult insert(int new_item);
	void delMax();
	heapResult findMax(int* output);
	
	void reset();
	
	const int _num_items();
	int* heap_array();
};


#endif /* _HEAP_H */

