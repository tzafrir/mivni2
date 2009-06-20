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
		if (NeighborhoodsBottom.insert(population) == NeighborhoodsBottom.Failure) {
			return TownFailure;
		}
		Neighborhoods++;
		return TownSuccess;
	}
	
	int tmp;
	if (NeighborhoodsBottom.findMax(&tmp) == NeighborhoodsBottom.Failure) 
	{
		return TownFailure;
	}
	
	if (population < tmp)
	{
		NeighborhoodsBottom.delMax();
		NeighborhoodsBottom.insert(population);
		population = tmp;
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

	//resotre plus sign so will be able to work with the real values
	for (int i = ma; i < Neighborhoods; i++)
	{
		Townpopulation[i] *= -1; 
	}

	for (int i = 0 ; i < size ; i++)
	{
		Townpopulation[Neighborhoods+i] = populations[i];
	}

	Neighborhoods+= size;

	BuildHeaps();

	return TownSuccess;
}

Town::TownResult Town::MonsterAttack(int* population) {	
	if (Neighborhoods < ma) {
		return TownFailure;
	}
	if (NeighborhoodsBottom.findMax(population) == NeighborhoodsBottom.Failure) {
		return TownFailure;
	}
	if (Neighborhoods == ma) {
		NeighborhoodsBottom.delMax();
	} else {
		int tmp;
		if (NeighborhoodsTop.findMax(&tmp) == NeighborhoodsTop.Failure) {
			return TownFailure;
		}
		NeighborhoodsBottom.heap_array()[0] = tmp * -1; // Hack - equivalent to
														 // removing and readding
														 // tmp to the heap
		NeighborhoodsTop.delMax();
	}
	Neighborhoods--;
	return TownSuccess;
}

void Town::BuildHeaps()
{
	
	if (maxNeighborhoods <= ma)
	{
		NeighborhoodsBottom = heap(Neighborhoods,Townpopulation,maxNeighborhoods);
		NeighborhoodsTop =  heap();
	}
	else
	{
		if (Neighborhoods  > ma)
		{
			//puts ma element in Townpopulation[ma-1] and
			//partition the array so all smaller elements ar
			//before Townpopulation[ma-1] all larger after
			//and equal to are on both sides
			Select::select(Townpopulation, Neighborhoods, ma); 
		

			//restore minus sign to emulate min heap
			for (int i = ma; i < Neighborhoods; i++)
			{
				Townpopulation[i] *= -1; 
			}
			NeighborhoodsBottom = heap(ma,Townpopulation,ma);
			NeighborhoodsTop =  heap(Neighborhoods-ma,Townpopulation+ma,maxNeighborhoods - ma);
		}
		else
		{
			NeighborhoodsBottom = heap(Neighborhoods,Townpopulation,ma);
			NeighborhoodsTop =  heap(0,Townpopulation+ma,maxNeighborhoods - ma);
		}
	}
}



Town::TownResult Town::ChangeMa(int ma) {
	if (Neighborhoods == 0) {
		this->ma = ma;
		return TownSuccess;
	}

	for (int i = this->ma; i < Neighborhoods; i++)
	{
		Townpopulation[i] *= -1; 
	}

	this->ma = ma;
	
	BuildHeaps();

	return TownSuccess;
}


