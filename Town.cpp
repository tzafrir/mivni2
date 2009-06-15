/*
 *
 *	Town.cpp
 *
 */
#include "Town.h"
#include "heap.h"
#include "select.h"
#include <assert.h>


Town::TownResult Town::AddNeighborhood(int population) {
	if (Neighborhoods == maxNeighborhoods) {
		return TownFailure;
	}
	if (Neighborhoods < ma) {
		if (NeighborhoodsBottom->insert(population) == NeighborhoodsBottom->Failure) {
			return TownFailure;
		}
		Neighborhoods++;
		return TownSuccess;
	}
							// Maximum heap of negatives := minimum heap
	if (NeighborhoodsTop->insert(-1 * population) == NeighborhoodsTop->Failure) { 
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
		if (i < ma) {
			tmp[i] = NeighborhoodsBottom->heap_array()[i];
		} else {
			tmp[i] = NeighborhoodsTop->heap_array()[i-ma] * -1;
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
	NeighborhoodsBottom->reset();
	NeighborhoodsTop->reset();
	
	if (Neighborhoods + size <= ma) {
		if (NeighborhoodsBottom->makeHeap(tmp, Neighborhoods+size) ==
				NeighborhoodsBottom->Failure) {
			delete[] tmp;
			return TownFailure;
		}
	} else {
		if (NeighborhoodsBottom->makeHeap(tmp, ma) == NeighborhoodsBottom->Failure) {
			delete[] tmp;
			return TownFailure;
		}
		for (int i=ma; i< Neighborhoods + size;i++) {
			tmp[i] *= -1;
		}

		if (NeighborhoodsTop->makeHeap(&tmp[ma], Neighborhoods + size - ma)
				== NeighborhoodsTop->Failure) {
			delete[] tmp;
			return TownFailure;
		}
	}
	delete[] tmp;
	Neighborhoods += size;
	return TownSuccess;
}

Town::TownResult Town::MonsterAttack(int* population) {	
	if (Neighborhoods < ma) {
		return TownFailure;
	}
	if (NeighborhoodsBottom->findMax(population) == NeighborhoodsBottom->Failure) {
		return TownFailure;
	}
	if (Neighborhoods == ma) {
		NeighborhoodsBottom->delMax();
	} else {
		int tmp;
		if (NeighborhoodsTop->findMax(&tmp) == NeighborhoodsTop->Failure) {
			return TownFailure;
		}
		NeighborhoodsBottom->heap_array()[0] = tmp * -1; // Hack - equivalent to
														 // removing and readding
														 // tmp to the heap
		NeighborhoodsTop->delMax();
	}
	Neighborhoods--;
	return TownSuccess;
}

Town::TownResult Town::ChangeMa(int ma) {
	if (Neighborhoods == 0) {
		this->ma = ma;
		return TownSuccess;
	}
	int* tmp = new int[Neighborhoods];
	for (int i=0;i<Neighborhoods;i++) {
		if (i < this->ma) {
			tmp[i] = NeighborhoodsBottom->heap_array()[i];
		} else {
			tmp[i] = -1 * NeighborhoodsTop->heap_array()[i - this->ma];
		}
	}
	
	this->ma = ma;
	
	
	Select s;
	s.select(tmp, 0, Neighborhoods-1, ma); // Side effect puts ma element in tmp[ma-1]
	for (int i=ma;i<Neighborhoods;i++) {
		tmp[i] *= -1;
	}
	
	delete NeighborhoodsBottom;
	NeighborhoodsBottom = new heap(ma);
	if (NeighborhoodsBottom->makeHeap(tmp, (Neighborhoods >= ma ? ma : Neighborhoods))
			== NeighborhoodsBottom->Failure) {
		delete[] tmp;
		return TownFailure;
	}
	

	if (Neighborhoods > ma) {
		delete NeighborhoodsTop;
		NeighborhoodsTop = new heap(maxNeighborhoods - ma); // maxNeighborhoods >= Neighborhoods,
															// so this will not fail
		if (NeighborhoodsTop->makeHeap(&tmp[ma], Neighborhoods - ma)
				== NeighborhoodsTop->Failure) {
			delete[] tmp;
			return TownFailure;		
		}
	} else {
		NeighborhoodsTop->reset();
	}
	delete[] tmp;
	return TownSuccess;
}


