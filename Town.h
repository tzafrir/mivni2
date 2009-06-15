#ifndef _TOWN_H
#define _TOWN_H

#include "heap.h"

/*
 *
 *	Town.h
 *
 */

class Town {
	int maxNeighborhoods;
	int ma;
	heap* NeighborhoodsBottom;
	heap* NeighborhoodsTop;
public:


	Town(int RLocation,int maxNeighborhoods, int ma)  : 
		maxNeighborhoods(maxNeighborhoods), ma(ma), Location(RLocation), Neighborhoods(0) {
			NeighborhoodsBottom = new heap(ma);
			NeighborhoodsTop = new heap(maxNeighborhoods);
	}
	~Town(){
		delete NeighborhoodsBottom;
		delete NeighborhoodsTop;
	}
	int Location;
	int Neighborhoods;

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
};

#endif
