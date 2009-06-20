#ifndef _SELECT_H
#define _SELECT_H

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

	static void select(int* A,int Size, int index) 
	{
		index--; //if we work with indexes 0-size-1 the index'th item in in positon 
		//index -1
		int last=Size-1, first=0;

		while (true)
		{	
			int pivot;
			if (Size < 15) //median of medians isnt useful if we have 
				//less then 3 groups of five...
			{
				if (Size <= 1)
				{
					return;
				}
				pivot = last;
			}
			else
			{
				//use median of medians to select good pivot
				int medians= first;
				for (int i = medians; i <= last- 4;	medians++, i+=5)
				{
					select(&A[i],5,3);
					swap(A[i+2],A[medians]);
				}

				pivot = (medians - first) /2;

				select(&A[first],medians - first ,pivot);
				pivot = first + pivot -1;
			}
			
			pivot = partition(A,first,last,pivot);


			if (index < pivot)
			{
				last = pivot-1;
			}
			else
			{
				if (index == pivot) 
				{
					return;
				}

				first = pivot+1;
			}
			Size = last - first + 1;
			
		}
	}
		
};
#endif // _SELECT_H
