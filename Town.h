#ifndef _TOWN_H
#define _TOWN_H

/*
 *
 *	Town.h
 *
 */

#include "library2.h"
#include "avl.h"

class Town {
public:
	Town(int RLocation,int MaxNeighborhoods)  : Location(RLocation), Neighborhoods(0)
	{
	//	Roads.insert(&DummyRoad);
	}
	int Location;
	int Neighborhoods;

	bool operator<=(const Town& X) const
	{
		return Location <= X.Location;
	}
private:
	Town (const Town&);
};

#endif
