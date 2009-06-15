#!/bin/sh
cd SanityTests
../main2 < testA1.txt > myA1.txt
diff myA1.txt outA1.txt
../main2 < testA2.txt > myA2.txt
diff myA2.txt outA2.txt
../main2 < testA3.txt > myA3.txt
diff myA3.txt outA3.txt
../main2 < testB1.txt > myB1.txt
diff myB1.txt outB1.txt
../main2 < testB2.txt > myB2.txt
diff myB2.txt outB2.txt
../main2 < testAB.txt > myAB.txt
diff myAB.txt outAB.txt
