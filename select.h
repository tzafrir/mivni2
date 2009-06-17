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
	static void partition(int* A, int first, int Last, int index, int& p_Left,int& p_Right) 
	{
		
		int i = first, k = first, p = Last;
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

		//now (A+first)[0..k-1] smaller then pivot ,(A+first)[k..p-1] larger then pivot
		//(A+first)[p..Size-1] are all pivots


		i = Last;
		p_Left = k;
		
		for (; k < p; k++,i--)
		{
			swap(A[k],A[i]);
		}

		p_Right = i;
	}

	static void select(int* A,int Size, int index) 
	{
		index--; //its we work with indexes 0-size-1 the index'th item in in positon 
		//index -1
		int last=Size-1, first=0;
		int p_Left,p_Right;

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
			
			partition(A,first,last,pivot,p_Left,p_Right);


			if (index < p_Left)
			{
				last = p_Left-1;
			}
			else if (index > p_Right)
			{
				first = p_Right+1;
			}
			else
			{
				return; //one of the pivots of last partition is in the 
						//requested position
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
