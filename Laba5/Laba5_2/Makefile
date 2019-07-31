Laba5 : Laba5.o libmath_operations.so
	gcc -o Laba5 Laba5.o -L. -lmath_operations -lm -Wl,-rpath,. 
	rm Laba5.o square.o root.o
Laba5.o : Laba5.c
	gcc -c Laba5.c
libmath_operations.so : square.o root.o
	gcc -shared -o libmath_operations.so square.o root.o
square.o root.o : square.c root.c
	gcc -fPIC -c square.c root.c
