build: main.o THash.o TLG.o
	gcc -Wall -g -o tema1 main.o THash.o TLG.o

main.o: main.c THash.h
	gcc -Wall -c main.c

THash.o: THash.c THash.h
	gcc -Wall -c THash.c

TLG.o: TLG.c TLG.h
	gcc -Wall -c TLG.c

run: build
	./tema1

clean:
	rm -f tema1 *.o
