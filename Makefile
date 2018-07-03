trep: trep.o
	gcc -o trep trep.o

install:
	cp trep.exe /usr/local/bin

clean:
	rm -f *.exe *.o *~
