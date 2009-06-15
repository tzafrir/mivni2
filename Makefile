CPPFLAGS=-g -Wall --pedantic-errors
clean:
	rm *.o main2
heap.o: heap.h
Town.o: Town.h select.h
RectangleLand.o: RectangleLand.h 
library2.o: library2.h 
main2: main2.cpp library2.o RectangleLand.o Town.o heap.o
tests: main2
	./tests.sh
