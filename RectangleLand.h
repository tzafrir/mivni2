#ifndef _RECTANGLELAND_H
#define _RECTANGLELAND_H

/*
 *
 *	RectangleLand.h
 *
 */

#include "library2.h"
#include "Maxavl.h"
#include "Town.h"
#include "Edge.h"

class RectangleLand {
	
	int ma;

	MAXAVL<Edge> Roads;

	MAXAVL<Town> Shores[2];
	MAXAVL<Edge> Borders[2]; //in Borders[SOUTH] the edges  are swithed so it will be orderd
	//accrding to the SOUTH vertex first
	
	class MaChanger : public MAXAVL<Town>::Predicate {
		int ma;
		bool DoWork(Town* T);
	public:
		MaChanger(int ma) : ma(ma) {}
	};
	
public:
	RectangleLand(int rma) : ma(rma) {}
	~RectangleLand()
	{
		Borders[NORTH].DestroyTree(true);
		Borders[SOUTH].DestroyTree(true);
		Roads.DestroyTree(true);
		Shores[NORTH].DestroyTree(true);
		Shores[SOUTH].DestroyTree(true);
	}
	StatusType  AddTown(Shore side, int location, int maxNeighborhoods);
	StatusType  AddRoad(int northTown, int southTown);
	StatusType  RemoveRoad(int northTown, int southTown);
	StatusType  AddBorder(int northPt, int southPt);
	StatusType  RemoveBorder(int northPt, int southPt);
	StatusType  AddNeighborhood(Shore side, int location, int population);
	StatusType  AddManyNeighborhoods(Shore side, int location, int size, const int* populations);
	StatusType  MonsterAttack(Shore side, int location, int* population);
	StatusType  ChangeMa(int ma);
};

#endif
