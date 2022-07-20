all:avl

avl:main.o avl.o
	gcc avl.o main.o -o avl

avl.o:avl.c
	gcc -c avl.c -o avl.o

main.o:main.c
	gcc -c main.c -o main.o

clean:
	rm -f avl *.o
