#ifndef _EDGE_H
#define _EDGE_H

/*
 *
 *	edge.h
 *
 */


#include "library2.h"
class Edge {
public:
#define FirstShore NORTH
#define SecondShore SOUTH
	Edge(int north, int south) 
	{
		Location[FirstShore] = north;
		Location[SecondShore] = south;
	}
	int Location[2];

	bool operator<=(const Edge& X) const
	{
		if  (Location[FirstShore] == X.Location[FirstShore])
		{
			return Location[SecondShore] <= X.Location[SecondShore];
		}
		//else 
		return Location[FirstShore] <= X.Location[FirstShore];
	}

	int AValue()
	{
		return Location[SecondShore];
	}

private:
	Edge (const Edge&);
};

#endif
