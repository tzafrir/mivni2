#include "RectangleLand.h"

/*
 *
 *	RectangleLand.cpp
 *
 */


StatusType  RectangleLand::AddTown(Shore side, int location, int maxNeighborhoods)
{
	unsigned int index = (unsigned int) side;
	if (location < 0 || maxNeighborhoods < 0)
		return INVALID_INPUT;

	if (index < 2)
	{
		Town* T = NULL;
		try
		{
			int min,max;
			//make sure we dont have a border in that location
			Edge b(location,-1);
			Edge* ClosestBorder = Borders[index].findClosest(&b,Borders[index].Above,min,max);
			if (ClosestBorder == NULL || ClosestBorder->Location[NORTH] != location) 
				//the location in the border is always north, no matter what the index is
			{
				
				T =  new Town(location,maxNeighborhoods,ma);
				if (Shores[index].insert(T) == Shores[index].Success) {
					AllowedBorders++;
					return SUCCESS;
				}
				delete T;
			}
		}
		catch (std::bad_alloc&)
		{
			delete(T);
		}
	}
	return FAILURE;
}


StatusType  RectangleLand::AddRoad(int northTown, int southTown)
{
	if (northTown < 0 || southTown < 0)
		return INVALID_INPUT;

	

	//first make sure both towns exist
	Town SnorthTown(northTown);
	Town SsouthTown(southTown);

	if (Shores[NORTH].find(&SnorthTown) != NULL && Shores[SOUTH].find(&SsouthTown) != NULL)
	{
		Edge* Road = NULL;
		try
		{
			Road = new Edge(northTown,southTown);
			int min,max;
			//make sure there is no intersection with a border
			Edge* Border = Borders[NORTH].findClosest(Road,Borders[NORTH].Bellow,min,max);
			if (Border == NULL || Road->Location[SOUTH] >= Border->Location[SOUTH])
			{
				Border = Borders[NORTH].findClosest(Road,Borders[NORTH].Above,min,max);
				if (Border == NULL || Road->Location[SOUTH] <= Border->Location[SOUTH])
				{
					if (Roads.insert(Road) == Roads.Success)
					{
						return SUCCESS;
					}
				}
			}
		}

		catch (std::bad_alloc&)
		{
		}
		delete(Road);
	}
	return FAILURE;
}

StatusType  RectangleLand::RemoveRoad(int northTown, int southTown)
{
	if (northTown < 0 || southTown < 0)
		return INVALID_INPUT;

	Edge SRoad(northTown,southTown);
	Edge* Road = Roads.remove(&SRoad);
	if (Road != NULL)
	{
		delete(Road);
		return SUCCESS;
	}
	//else
	return FAILURE;
}

StatusType RectangleLand::AddBorder(int northPt, int southPt)
{
	if (northPt < 0 || southPt < 0)
		return INVALID_INPUT;

	Edge* NewBorder = NULL;
	try
	{
		//make sure there isnt any tonw in those locations
		Town northTown(northPt);
		Town southTown(southPt);
		if (Shores[NORTH].find(&northTown) != NULL || Shores[SOUTH].find(&southTown) != NULL
			|| AllowedBorders == 0 )
		{
			return FAILURE;
		}
		NewBorder = new Edge(northPt,southPt);
		//make sure there is no intersection with a border
		int min,max;
		Edge* Border = Borders[NORTH].findClosest(NewBorder,Borders[NORTH].Bellow,min,max);
		if (Border == NULL || NewBorder->Location[SOUTH] >= Border->Location[SOUTH])
		{
			Border = Borders[NORTH].findClosest(NewBorder,Borders[NORTH].Above,min,max);
			if (Border == NULL || NewBorder->Location[SOUTH] <= Border->Location[SOUTH])
			{
				Edge* Road = Roads.findClosest(NewBorder,Roads.Bellow,min,max);
				if (Road == NULL || NewBorder->Location[SOUTH] >= max)
				{
					Road = Roads.findClosest(NewBorder,Roads.Above,min,max);
					if (Road == NULL || NewBorder->Location[SOUTH] <= min)
					{
						if (Borders[NORTH].insert(NewBorder) == Borders[NORTH].Success)
						{
							NewBorder = NULL; //dont free old border in case allocation fails...
							NewBorder = new Edge(southPt, northPt); //reverse order
							if (Borders[SOUTH].insert(NewBorder) == Borders[SOUTH].Success)
							{
								AllowedBorders--;
								return SUCCESS;
							}
						}
					}
				}
			}
		}
	}
	catch (std::bad_alloc&)
	{
	}

	delete(NewBorder);

	return FAILURE;
}

StatusType  RectangleLand::RemoveBorder(int northPt, int southPt)
{
	if (northPt < 0 || southPt < 0)
		return INVALID_INPUT;
	//else
	Edge SBorder(northPt,southPt);
	Edge* Border = Borders[NORTH].remove(&SBorder);
	if (Border != NULL)
	{
		delete(Border);
		SBorder.Location[NORTH] = southPt; //reverse order
		SBorder.Location[SOUTH] = northPt;
		Border = Borders[SOUTH].remove(&SBorder);
		delete(Border);
		AllowedBorders++;
		return SUCCESS;
	}
	//else
	return FAILURE;
}

StatusType RectangleLand::AddNeighborhood(Shore side, int location, int population){
	if ( (location < 0) || (population <= 0) ) {
		return INVALID_INPUT;
	}
	try{
		Town tmp(location);
		Town* T = Shores[side].find(&tmp);
		if (T == NULL) {
			return FAILURE;
		}
		if (T->AddNeighborhood(population) == T->TownSuccess) {
			return SUCCESS;
		}
	} catch (std::bad_alloc&)	{
	
		}
	return FAILURE;
}

StatusType RectangleLand::AddManyNeighborhoods(Shore side, int location, int size, const int* populations){
	if ( (size <= 0) || (location < 0) || (populations == NULL) ) {
		return INVALID_INPUT;
	}

	for (int i = 0; i < size; i++)
	{
		if (populations[i] <= 0)
		{
			return INVALID_INPUT;
		}

	}

	try {
		Town tmp(location);
		Town* T = Shores[side].find(&tmp);
		if (T == NULL) {
			return FAILURE;
		}
		if (T->AddManyNeighborhoods(size, populations) == T->TownFailure) {
			return FAILURE;
		}
		return SUCCESS;
	} catch (std::bad_alloc&)	{
	
	}
	return FAILURE;
}

StatusType RectangleLand::MonsterAttack(Shore side, int location, int* population) {
	if ( (location < 0) || (population == NULL) ) {
		return INVALID_INPUT;
	}
	try {
		Town tmp(location);
		Town* T = Shores[side].find(&tmp);
		if (T == NULL) {
			return FAILURE;
		}
		if (T->MonsterAttack(population) == T->TownFailure) {
			return FAILURE;
		}
		return SUCCESS;
	} catch (std::bad_alloc&)	{
	
	}
	return FAILURE;
}

StatusType RectangleLand::ChangeMa(int ma) {
	if (ma <= 0) {
		return INVALID_INPUT;
	}
	try {
		MaChanger M(ma);
		this->ma = ma;
		Shores[NORTH].inorder(&M);
		Shores[SOUTH].inorder(&M);
		return SUCCESS;
	} catch (std::bad_alloc&)	{
	
	}
	return FAILURE;
}

// Ma changer method for inorder
bool RectangleLand::MaChanger::DoWork(Town* T) {
	T->ChangeMa(ma);
	return false;
}
