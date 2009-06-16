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

	static void median_of_5(int* A)
	{
		for (int j=4;j >=2;j--) {
			int maxtmp = 0;
			for (int i=1; i<=j; i++) {
				if (A[i] > A[maxtmp]) {
					maxtmp = i;
				}
			}
			swap(A[j], A[maxtmp]); 
		}
	}

	
	public:
	static void select(int* A, int first, int last, int index) 
	{
		if (first == last)
		{
			return;
		}

		int* medians= A+ first;
		for (int* ptr = medians; ptr <= A + last- 4;
				medians++, ptr+=5)
		{
			median_of_5(ptr);
			swap(*(ptr+2),*medians);
		}

		int mediansNum = medians-(A+first);
		
		int pivot = last;
		if (mediansNum > 1)
		{
			pivot = (mediansNum - first) /2;
			select(A,first,mediansNum-1,pivot);
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
