#Name: 		 Owen Douglas
#Student ID: 1056143
#Email: 	 douglaso@uoguelph.ca


CC = gcc
CFLAGS = -Wall -pedantic -ansi -g

# Excecutable
a3 : binary.o common.o name.o principals.o title.o a3.o
	$(CC) binary.o common.o name.o principals.o title.o a3.o -o $@

# Object Files
principals.o : principals.c binary.h common.h
	$(CC) $(CFLAGS) -c principals.c -o $@

title.o : title.c binary.h common.h
	$(CC) $(CFLAGS) -c title.c -o $@

name.o : name.c binary.h common.h
	$(CC) $(CFLAGS) -c name.c -o $@

binary.o : binary.c common.h
	$(CC) $(CFLAGS) -c binary.c -o $@

common.o : common.c
	$(CC) $(CFLAGS) -c common.c -o $@

a3.o : a3.c binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) -c a3.c -o $@

# Run Stuff
run : a3
	./a3 /home/courses/cis2520

clean :
	rm *.o a3