#include <iostream>
#define LARGE rand() % 80000
#define MEDIUM rand () % 40000
#define SMALL rand() % 25
#define SHORE rand() % 2
#define __ << " " <<
#define HOWMANY 1 + rand() % 50
#define LENGTH 1000

using namespace std;

void AddTown() {
	cout << "AddTown " << SHORE __ SMALL __ LARGE << endl;
}

void AddRoad() {
	cout << "AddRoad " <<  SMALL __ SMALL << endl;
}

void RemoveRoad() {
	cout << "RemoveRoad " << SMALL __ SMALL << endl;
}

void AddBorder() {
	cout << "AddBorder " << SMALL __ SMALL << endl;
}

void RemoveBorder() {
	cout << "RemoveBorder " << SMALL __ SMALL << endl;
}

void AddNei() {
	cout << "AddNeighborhood " << SHORE __ SMALL __ LARGE << endl;
}

void AddMany() {
	int size = HOWMANY;
	cout << "AddManyNeighborhoods " << SHORE __ SMALL __ size;
	for (int i=0; i < size; i++) {
		cout __ SMALL;
	}
	cout << endl;
}

void MonsterA() {
	cout << "MonsterAttack " << SHORE __ SMALL << endl;
}

void ChangeMa() {
	cout << "ChangeMa " << MEDIUM << endl;
}



int main() {

	srand(time(NULL));
	int length = LENGTH;
	cout << "Init " << MEDIUM << "\n";
	for (int i=0; i < length; i++) {
		switch (rand() % 9) {
			case 0 : AddTown(); break;
			case 1 : AddRoad(); break;
			case 2 : RemoveRoad(); break;
			case 3 : AddBorder(); break;
			case 4 : RemoveBorder(); break;
			case 5 : AddNei(); break;
			case 6 : AddMany(); break;
			case 7 : MonsterA(); break;
			case 8 : ChangeMa(); break;
		}
	}
	cout << "Quit" << "\n";
	return 0;
}
