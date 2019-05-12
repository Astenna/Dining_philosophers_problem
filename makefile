__start__: dining_philosophers
	./dining_philosophers

dining_philosophers: obj obj/main.o obj/fork_t.o obj/philosopher.o obj/table.o
	g++ -g -pthread -rdynamic -lncurses -Wall -pedantic -std=c++11 -o dining_philosophers obj/main.o obj/fork_t.o obj/philosopher.o obj/table.o

obj:
	mkdir obj

obj/main.o:
	g++ -g -c -pthread -Wall -pedantic -std=c++11 -o obj/main.o src/main.cpp

obj/table.o:
	g++ -g -c -pthread -Wall -pedantic -std=c++11 -o obj/table.o src/table.cpp

obj/philosopher.o:
	g++ -g -c -pthread -Wall -pedantic -std=c++11 -o obj/philosopher.o src/philosopher.cpp

obj/fork_t.o:
	g++ -g -c -pthread -Wall -pedantic -std=c++11 -o obj/fork_t.o src/fork_t.cpp

clean:
	rm -f obj/*.o dining_philosophers
