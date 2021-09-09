atdate: atdate.o utils.o
	gcc -o atdate atdate.o utils.o
utils.o: utils.c
	gcc -g -c utils.c

atdate.o: atdate.c utils.o
	gcc -g -c atdate.c

