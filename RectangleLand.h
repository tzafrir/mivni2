#ifndef _RECTANGLELAND_H
#define _RECTANGLELAND_H

/*
 *
 *	RectangleLand.h
 *
 */

#include "library2.h"
#include "avl.h"
#include "Maxavl.h"
#include "Town.h"
#include "Edge.h"

class RectangleLand {
	
	int ma;

	MAXAVL<Edge> Roads;

	AVL<Town> Shores[2];
	AVL<Edge> Borders;

public:
	RectangleLand(int rma) : ma(rma) {}
	StatusType  AddTown(Shore side, int location, int maxNeighborhoods);
	StatusType  AddRoad(int northTown, int southTown);
	StatusType  RemoveRoad(int northTown, int southTown);
	StatusType  AddBorder(int northPt, int southPt);
};

#endif
