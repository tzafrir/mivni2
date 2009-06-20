#include "heap.h"

int heap::father(int n) {
	return (((n+1) / 2) - 1);
}
int heap::left(int n) {
	return 2*(n+1) - 1;
}
int heap::right(int n) {
	return (2*(n+1)); // +1-1 
}
void heap::swap(int n1, int n2) {
	int tmp = tree[n1];
	tree[n1] = tree[n2];
	tree[n2] = tmp;
}
int heap::maxChild(int n) {
	return (tree[left(n)] <= tree[right(n)] ? right(n) : left(n));
}

void heap::siftUp(int n) {
	while ((n != 0) && (tree[father(n)] <= tree[n])) {
					// Used only for insert(), so stop when found proper place
		swap(father(n), n);
		n = father(n);
	}
}
void heap::siftDown(int n) {
	if (left(n) >= num_items) {
		return;
	}
	if (right(n) >= num_items) { // only have a left child, that must be a leaf
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

void heap::postOrderSiftDown(int n) {
	if (n >= num_items) {
		return;
	}
	postOrderSiftDown(left(n));
	postOrderSiftDown(right(n));
	siftDown(n);
}

heap::heapResult heap::insert(int new_item) {
	if (num_items == max) {
		return Failure;
	}
	tree[num_items] = new_item;
	siftUp(num_items);
	num_items++;
	return Success;
}

void heap::delMax() {
	if (num_items == 0) {
		return;
	}
	swap(0, num_items - 1);
	num_items--;
	siftDown(0);
}


heap::heapResult heap::findMax(int* output) {
	if ((output == NULL) || (num_items == 0)) {
		return Failure;
	}
	*output = tree[0];
	return Success;
}

void heap::reset() {
	num_items = 0;
}

const int heap::_num_items() {
	return num_items;
}

int* heap::heap_array() {
	return tree;
}
