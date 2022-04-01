build:
	gcc -g -o out main.c THash.c TLG.c

run: build
	./out

clean:
	rm out