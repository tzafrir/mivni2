#ifndef _TOWN_H
#define _TOWN_H

#include "heap.h"

/*
 *
 *	Town.h
 *
 */

class Town {
	int Location;
	int ma;
	int maxNeighborhoods;
	int Neighborhoods;
	int* Townpopulation;
	heap NeighborhoodsBottom;
	heap NeighborhoodsTop;
public:
	Town(int RLocation) : Location(RLocation), Townpopulation(NULL)  {}

	Town(int RLocation,int maxNeighborhoods, int ma)  : 
		Location(RLocation), ma(ma), maxNeighborhoods(maxNeighborhoods), Neighborhoods(0) {
			Townpopulation = new int[maxNeighborhoods];
			BuildHeaps();
	}

	~Town(){
		delete[] Townpopulation;
	}


	bool operator<=(const Town& X) const
	{
		return Location <= X.Location;
	}

	int AValue()
	{
		return -1;
	}
	
	enum TownResult { TownSuccess, TownFailure } ;
	TownResult AddNeighborhood(int population);
	TownResult AddManyNeighborhoods(int size, const int* populations);
	TownResult MonsterAttack(int* population);
	TownResult ChangeMa(int ma);
private:
	Town (const Town&);
	void BuildHeaps();
};

#endif
