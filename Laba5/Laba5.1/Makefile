Laba5 : Laba5.o libmath_operations.a
	gcc Laba5.o -L. -lmath_operations -lm -o Laba5
	rm Laba5.o libmath_operations.a
Laba5.o : Laba5.c
	gcc -c Laba5.c
	
libmath_operations.a : square.o root.o
	ar rc libmath_operations.a square.o root.o
	ranlib libmath_operations.a
	rm square.o root.o
square.o root.o : square.c root.c
	gcc -c square.c root.c

