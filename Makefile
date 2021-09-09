atdate: atdate.o utils.o
	gcc -o atdate atdate.o utils.o
	sudo cp "./atdate" "/bin"
utils.o: utils.c
	gcc -g -c utils.c

atdate.o: atdate.c utils.o
	gcc -g -c atdate.c

