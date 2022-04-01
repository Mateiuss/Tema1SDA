build:
	gcc -g -o tema1 main.c THash.c TLG.c

run: build
	./out

clean:
	rm out