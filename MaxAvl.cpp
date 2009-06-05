#include "Maxavl.h"
#include "Town.h"


class NM{
public:
	NM(int a,int b) : number(a), Max(b) {}
	int number;
	int Max;
	bool operator<= (const NM& x) const
	{
		return number <= x.number;
	}
};

void main()
{
	int m;
	NM b(5,8);
	NM* a;
	MAXAVL<NM> T;
	a = new  NM(1,3);
	T.insert(a);
	a = new  NM(2,2);	
	T.insert(a);
	a = new  NM(6,4);
	T.insert(a);


	a = new  NM(4,3);
	T.insert(a);

	a = new  NM(9,2);
	T.insert(a);

	a = new  NM(7,3);
	T.insert(a);


	T.findClosest(&b,T.Bellow,m);

}