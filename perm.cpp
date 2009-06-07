#include <iostream>

using namespace std;

int pow(int i) {
	int x=1;
	for (int j=0;j<i;j++) {
		x = (x * 2) % 65213;
	}
	return x;
}

int main(){
	cout << "{1,";
	for (int i=1;i<65212;i++) {
		if (i % 10 == 0) cout << endl;
		cout << pow(i) << ",";
	}
	cout << pow(65212) << "}";
}
