# general commands
all: StrList

clean:
	rm -f *.o StrList
	
# .o files
Main.o: Main.c
	gcc -Wall -c Main.c

StrList.o: StrList.c
	gcc -Wall -c StrList.c

# executables
StrList: Main.o StrList.o
	gcc -Wall Main.o StrList.o -o StrList