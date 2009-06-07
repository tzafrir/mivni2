#include "select.h"
#include <iostream>
using namespace std;

int main() {
	int A[15] = {12,13,5,6, 1,3,9,8,2, 4,7,11,14,15,10};
	int B[15] = {12,13,5,6, 1,3,9,8,2, 4,7,11,14,15,10};
	Select s;
	
	for (int i=1;i<=15;i++) {cout << s.select(A, 0, 14, i) << endl;}
	cout << endl;
	for (int i=1;i<=5;i++) {cout << s.select(B, 4, 8, i) << endl;}
	return 0;
}
