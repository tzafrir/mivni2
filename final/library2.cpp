#include "library2.h"
#include "RectangleLand.h"

void* Init(int ma)
{
	if (ma > 0) 
	{
		try
		{
			RectangleLand* DS = new RectangleLand(ma);
			return (void*)DS;
		}
		catch (std::bad_alloc&) 
		{
		}
	}
	return NULL;
}

StatusType  AddTown(void* DS, Shore side, int location, int maxNeighborhoods)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->AddTown(side,location,maxNeighborhoods);
}

StatusType  AddRoad(void* DS, int northTown, int southTown)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->AddRoad(northTown,southTown);
}

StatusType  RemoveRoad(void* DS, int northTown, int southTown)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->RemoveRoad(northTown,southTown);
}

StatusType AddBorder(void* DS, int northPt, int southPt)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->AddBorder(northPt,southPt);
}

StatusType  RemoveBorder(void* DS, int northPt, int southPt)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->RemoveBorder(northPt,southPt);
}

StatusType  AddNeighborhood(void* DS, Shore side, int location, int population)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->AddNeighborhood(side,location,population);
}

StatusType  AddManyNeighborhoods(void* DS, Shore side, int location, int size, const int* populations)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->AddManyNeighborhoods(side,location,size,populations);
}

StatusType  MonsterAttack(void* DS, Shore side, int location, int* population)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->MonsterAttack(side,location,population);
}


StatusType  ChangeMa(void* DS, int ma)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((RectangleLand*)DS)->ChangeMa(ma);
}

void        Quit(void** DS)
{
	delete (RectangleLand*)*DS;
	*DS = NULL;
}
