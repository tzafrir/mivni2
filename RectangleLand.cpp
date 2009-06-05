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
			Edge b(location,-1);
			Edge* ClosestBorder = Borders.findClosest(&b,Borders.Above);
			if (ClosestBorder == NULL || ClosestBorder->Location[index] != location)
			{
				//make sure we dont have a border in that location
				T =  new Town(location,maxNeighborhoods);
				if (Shores[index].insert(T) == Shores[index].Success)
					return SUCCESS;
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
	Town SnorthTown(northTown,-1);
	Town SsouthTown(southTown,-1);

	if (Shores[NORTH].find(&SnorthTown) != NULL && Shores[SOUTH].find(&SsouthTown) != NULL)
	{
		Edge* Road = NULL;
		try
		{
			Road = new Edge(northTown,southTown);
			//make sure there is no intersection with a border
			Edge* Border = Borders.findClosest(Road,Borders.Bellow);
			if (Border == NULL || Road->Location[SOUTH] > Border->Location[SOUTH])
			{
				Border = Borders.findClosest(Road,Borders.Above);
				if (Border == NULL || Road->Location[SOUTH] < Border->Location[SOUTH])
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
		NewBorder = new Edge(northPt,southPt);
		//make sure there is no intersection with a border
		Edge* Border = Borders.findClosest(NewBorder,Borders.Bellow);
		if (Border == NULL || NewBorder->Location[SOUTH] > Border->Location[SOUTH])
		{
			Border = Borders.findClosest(NewBorder,Borders.Above);
			if (Border == NULL || NewBorder->Location[SOUTH] < Border->Location[SOUTH])
			{
				int min,max;
				Edge* Road = Roads.findClosest(NewBorder,Roads.Bellow,min,max);
				if (Road == NULL || NewBorder->Location[SOUTH] > max)
				{
					Road = Roads.findClosest(NewBorder,Roads.Above,min,max);
					if (Road == NULL || NewBorder->Location[SOUTH] < min)
					{
						if (Borders.insert(NewBorder) == Borders.Success)
						{
							return SUCCESS;
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

void main()
{
	
	RectangleLand test(5);
	test.AddTown(NORTH,1,4);

	test.AddTown(NORTH,3,4);

	test.AddTown(SOUTH,2,4);

	test.AddRoad(3,2);

	test.AddRoad(4,8);
	test.AddBorder(1,4);
	test.AddBorder(2,1);

}