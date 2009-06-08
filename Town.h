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
	heap NeighborhoodsBottom;
	heap NeighborhoodsTop;
public:
	Town(int RLocation,int maxNeighborhoods, int ma)  : 
		Location(RLocation), Neighborhoods(0), maxNeighborhoods(maxNeighborhoods), ma(ma),
	
		NeighborhoodsBottom(ma),
		NeighborhoodsTop(maxNeighborhoods) {}
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
private:
	Town (const Town&);
};

#endif
