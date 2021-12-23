playfair: main.o playfair.o
	g++ -Wall -g main.o playfair.o -o playfair

playfair.o: playfair.cpp playfair.h
	g++ -Wall -g -c playfair.cpp

main.o: main.cpp
	g++ -Wall -g -c main.cpp

clean:
	rm -rf *.o playfair