Laba5 : Laba5.o libmath_operations.so
	gcc -o Laba5 Laba5.o -L. -lmath_operations -ldl
	rm root.o square.o Laba5.o
Laba5.o : Laba5.c
	gcc -c Laba5.c

libmath_operations.so : root.o square.o
	gcc -shared root.o square.o -o libmath_operations.so -lm
square.o root.o : root.c square.c
	gcc -fPIC -c root.c square.c
