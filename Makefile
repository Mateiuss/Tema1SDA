build: main.c THash.c TLG.c
	gcc -Wall -std=gnu99 -g -o tema1 main.c THash.c TLG.c

run: build
	./tema1

clean:
	rm -f tema1
