__start__: dining_philosophers
	./dining_philosophers

dining_philosophers: obj obj/main.o obj/fork.o obj/philosopher.o obj/table.o
	g++ -Wall -pedantic -std=c++11 -o dining_philosophers obj/main.o obj/fork.o obj/philosopher.o obj/table.o

obj:
	mkdir obj

obj/main.o:
	g++ -c -Wall -pedantic -std=c++11 -o obj/main.o src/main.cpp

obj/fork.o:
	g++ -c -Wall -pedantic -std=c++11 -o obj/fork.o src/fork.cpp

obj/philosopher.o:
	g++ -c -Wall -pedantic -std=c++11 -o obj/philosopher.o src/philosopher.cpp

obj/table.o:
	g++ -c -Wall -pedantic -std=c++11 -o obj/table.o src/table.cpp

clean:
	rm -f obj/*.o dining_philosophers
