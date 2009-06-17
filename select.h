#ifndef _SELECT_H
#define _SELECT_H

#include <stdlib.h>
#include <iostream>
#include <cassert>

using std::cout;

class Select {
	//A must have more then two element
	static int partition(int* A, int Size, int index) 
	{
		int pivot = A[index];
		
		int* Smaller=A;

		while (*(Smaller) < pivot) Smaller++; //will stop at pivot in worst case
		swap(*Smaller,A[index]);

		index = Smaller - A;
		if (index == Size-1)
		{
			return index;
		}

		int* Larger=A+Size;

		while (true)
		{
			while (*(--Larger) > pivot); //we know the loop will stop in
									    //A[index] in the worsk case
		
			while (*(++Smaller) < pivot);  //we know the loop will stop in
									    //becuse we placed a >= item in A[index] in the
										//the begging
			if (Larger > Smaller)
			{
				swap(*Larger,*Smaller);
			}
			else
			{
				break;
			}
		} 

		swap(A[index],*Larger);
		return Larger-A;
	}

	static inline void swap(int& a, int& b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	public:

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
		
};
#endif // _SELECT_H
