/*
 *
 *	Town.cpp
 *
 */
#include "Town.h"
#include "heap.h"
#include "select.h"

Town::TownResult Town::AddNeighborhood(int population) {
	if (Neighborhoods == maxNeighborhoods) {
		return TownFailure;
	}
	if (Neighborhoods < ma) {
		if (NeighborhoodsBottom.insert(population) == NeighborhoodsBottom.Failure) {
			return TownFailure;
		}
		Neighborhoods++;
		return TownSuccess;
	}
							// Maximum heap of negatives := minimum heap
	if (NeighborhoodsTop.insert(-1 * population) == NeighborhoodsTop.Failure) { 
		return TownFailure;
	}
	Neighborhoods++;
	return TownSuccess;
}

Town::TownResult Town::AddManyNeighborhoods(int size, const int* populations) {
	if (Neighborhoods + size > maxNeighborhoods) {
		return TownFailure;
	}
	int* tmp = new int[Neighborhoods + size];
	for (int i=0; i<Neighborhoods; i++) {
		if (i <= ma) {
			tmp[i] = NeighborhoodsBottom.heap_array()[i];
		} else {
			tmp[i] = NeighborhoodsTop.heap_array()[i-ma] * -1;
		}
	}
	for (int i=0; i < size; i++) {
		tmp[Neighborhoods+i] = populations[i]; 
	}
	Select s;
	s.select(tmp, 0, Neighborhoods+size-1, ma); // Side effect: ma'th member
												// is now in tmp[ma-1], and all
												// those before it are smaller than it.
												// This works also when ma is larger
												// than the size of the array.
	NeighborhoodsBottom.reset();
	NeighborhoodsTop.reset();
	
	if (Neighborhoods + size <= ma) {
		if (NeighborhoodsBottom.makeHeap(tmp, Neighborhoods+size) == NeighborhoodsBottom.Failure) {
			delete[] tmp;
			return TownFailure;
		}
	} else {
		if (NeighborhoodsBottom.makeHeap(tmp, ma) == NeighborhoodsBottom.Failure) {
			delete[] tmp;
			return TownFailure;
		}
		for (int i=ma; i< Neighborhoods + size;i++) {
			tmp[i] *= -1;
		}

		if (NeighborhoodsTop.makeHeap(&tmp[ma], Neighborhoods + size - ma)
				== NeighborhoodsTop.Failure) {
			delete[] tmp;
			return TownFailure;
		}
	}
	delete[] tmp;
	Neighborhoods += size;
	return TownSuccess;
}
