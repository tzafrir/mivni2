#ifndef _SELECT_H
#define _SELECT_H

#include <stdlib.h>
#include <iostream>
#include <cassert>

using std::cout;

class Select {
public:
	//use 3-way partition, becuse we have similiar items, and we dont
	//wont to waste the good pivot chosne by median of medians
	static int partition(int* A, int Size, int index) 
	{
		
		int i = 0, k = 0, p = Size-1;
		swap(A[index],A[p]);
		int pivot = A[p];

		while (i < p)
		{
			if (A[i] < pivot)
			{
				swap(A[i++],A[k++]);
			}
			else if (A[i] == pivot)
			{
				swap (A[i],A[--p]);
			}
			else 
			{
				i++;
			}
		}

		//now A[0..k-1] smaller then pivot ,A[k..p-1] larger then pivot
		//A[p..Size-1] are all pivots


		i = Size;
		index = k + (Size - p) / 2; //(Size - p) is the number of medians
									//we divide by 2 and add the index
									//of the first pivot after partitioning
									//this way if we get a good pivot
									//we advance even if must of the items are pivots
		for (; k < p; k++)
		{
			swap(A[k],A[--i]);
		}
		return index;

	}

	static void select(int* A,int Size, int index) 
	{
		index--; //its we work with indexes 0-size-1 the index'th item in in positon 
		//index -1
		int last=Size-1, first=0;

		while (true)
		{
			assert(first <= last);
			
			int pivot;
			if (last - first < 15) //median of medians isnt useful if we have 
				//less then 3 groups of five...
			{
				if (first == last)
				{
					return;
				}
				pivot = last;
			}
			else
			{
				//use median of medians to select good pivot and
				//garuntee O(n)
				int medians= first;
				for (int i = medians; i <= last- 4;	medians++, i+=5)
				{
					select(&A[i],5,3);
					swap(A[i+2],A[medians++]);
				}

				pivot = (medians - first) /2;

				select(&A[first],medians,pivot);
			}
			
			pivot = partition(A,Size,pivot);


			if (index < pivot)
			{
				return;
				last = pivot-1;
			}
			else
			{
				if (index == pivot) 
				{
					return;
				}

				first = pivot+1;
				return;
			}
			
		}
	}

	static inline void swap(int& a, int& b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

		
};
#endif // _SELECT_H
