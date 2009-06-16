#ifndef _SELECT_H
#define _SELECT_H

#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;

class Select {
	//A must have more then two element
	static int partition(int* A, int first, int last, int index) 
	{
		swap(A[first],A[index]);
		int* Smaller=A+first;
		int* Larger=A+last+1;

		while (true)
		{
			while (*(--Larger) > A[first] && Larger > Smaller);
		
			while (*(++Smaller) < A[first] && Larger > Smaller);

			if (Larger > Smaller)
			{
				swap(*Larger,*Smaller);
			}
			else
			{
				break;
			}
		} 

		swap(A[first],*Larger);
		return Larger-A;
	}

	static inline void swap(int& a, int& b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	public:
	static void select(int* A, int first, int last, int index) 
	{
		int pivot = last;
		if (last -first <= 5)
		{
			if (first == last)
			{
				return;
			}
		}
		else
		{
			int medians= first;
			for (int i = medians; i <= last- 4;	medians++, i+=5)
			{
				select(A,i,i+4,3);
				swap(A[i+2],A[medians++]);
			}
			pivot = (medians - first) /2;

			select(A,first,medians-1,pivot);
		}
		
		pivot = partition(A,first,last,pivot);

		if (index-1 < pivot)
		{
			select(A,first,pivot-1,index);
			
		}
		else
		{
			select(A,pivot,last,index);	
		}
		/*
		std::cout << std::endl << index - first << std::endl;
		for (int i = first; i <= last; i++)
		{
			std::cout << A[i] << ',' ;
		}
		std::cout << std::endl << pivot << std::endl;
		*/
	}
		
};
#endif // _SELECT_H
