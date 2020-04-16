CC = gcc
CFLAGS = -Wall -g

all: main

main: TTab.o TBrowser.o functiiStiva.o TLista.o main.o functiiCoada.o utils.o
	$(CC)  $(CFLAGS) $^ -o $@ 
main.o: main.c 
	$(CC) $(CFLAGS) -c $< -o $@
utils.o: utils.c
	$(CC) $(FLAGS) -c $< -o $@
functiiStiva.o: functiiStiva.c TStiva.h
	$(CC) $(FLAGS) -c $< -o $@
TTab.o: TTab.c
	$(CC) $(FLAGS) -c $< -o $@
TBrowser.o: TBrowser.c
	$(CC) $(FLAGS) -c $< -o $@
run:
	./main
clean:
	rm -f *.o main
checkMem:
	valgrind --leak-check=full --error-exitcode=1  --track-origins=yes ./main
