#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>

enum heapResult{
	Success,
	Failure
};

template <typename T, int max, bool deleteItems>
class heap {
	T tree[max];
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
	
	
	static const int Invalid = -1;
	
public:
	heap() : num_items(0) {}
	heapResult makeHeap(T* input_array, int size);
	heapResult insert(T new_item);
	heapResult delMax();
	T* findMax();
	
	void print(int n){
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




template <typename T, int max, bool deleteItems>
int heap<T, max, deleteItems>::father(int n) {
	return (((n+1) / 2) - 1);
}
template <typename T, int max, bool deleteItems>
int heap<T, max, deleteItems>::left(int n) {
	return 2*(n+1) - 1;
}
template <typename T, int max, bool deleteItems>
int heap<T, max, deleteItems>::right(int n) {
	return (2*(n+1)); // +1-1 
}
template <typename T, int max, bool deleteItems>
void heap<T, max, deleteItems>::swap(int n1, int n2) {
	T tmp = tree[n1];
	tree[n1] = tree[n2];
	tree[n2] = tmp;
}
template <typename T, int max, bool deleteItems>
int heap<T, max, deleteItems>::maxChild(int n) {
	return (tree[left(n)] <= tree[right(n)] ? right(n) : left(n));
}

template <typename T, int max, bool deleteItems>
void heap<T, max, deleteItems>::siftUp(int n) {
	while ((n != 0) && (tree[father(n)] <= tree[n])) {
					// Used only for insert(), so stop when found proper place
		swap(father(n), n);
		n = father(n);
	}
}
template <typename T, int max, bool deleteItems>
void heap<T, max, deleteItems>::siftDown(int n) {
	if (left(n) >= num_items) {
		return;
	}
	if (right(n) >= num_items) { // only have a left child, that must be a leaf
		int this1 = n;
		int thisleft = left(n);
		if (tree[n] <= tree[left(n)]) {
			swap(n, left(n));
		}
		return;
	}
	int maxChildIndex = maxChild(n);
	if (!(tree[n] <= tree[maxChildIndex])) { // Larger than both children
		return;
	}
	swap(n, maxChildIndex);
	siftDown(maxChildIndex);
}

template <typename T, int max, bool deleteItems>
void heap<T, max, deleteItems>::postOrderSiftDown(int n) {
	if (n >= num_items) {
		return;
	}
	postOrderSiftDown(left(n));
	postOrderSiftDown(right(n));
	siftDown(n);
}

template <typename T, int max, bool deleteItems>
heapResult heap<T, max, deleteItems>::makeHeap(T* input_array, int size) {
	if (size > max) {
		return Failure;
	}
	if (num_items != 0) { // Can't makeHeap on a non-empty heap
		return Failure;
	}
	for (int i=0; i < size; i++) {
		tree[i] = input_array[i];
	}
	num_items = size;
	postOrderSiftDown(0);
	return Success;
}

template <typename T, int max, bool deleteItems>
heapResult heap<T, max, deleteItems>::insert(T new_item) {
	if (num_items == max) {
		return Failure;
	}
	tree[num_items] = new_item;
	siftUp(num_items);
	num_items++;
	return Success;
}

template <typename T, int max, bool deleteItems>
heapResult heap<T, max, deleteItems>::delMax() {
	if (num_items == 0) {
		return Failure;
	}
	swap(0, num_items - 1);
	if (deleteItems) {
		delete tree[num_items - 1];
	}
	num_items--;
	siftDown(0);
	return Success;
}

template <typename T, int max, bool deleteItems	>
T* heap<T, max, deleteItems>::findMax() {
	if (num_items == 0) {
		return NULL;
	}
	return &tree[0];
}

#endif /* __HEAP_H__ */

