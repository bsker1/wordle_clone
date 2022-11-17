 wordle_clone: main.o functions.o
	g++ -std=c++17 main.o functions.o -o wordle_clone

main.o:
	g++ -c -std=c++17 source/main.cpp

functions.o:
	g++ -c -std=c++17 source/functions.cpp

db:
	g++ -g -std=c++17 source/main.cpp source/functions.cpp -o wordle_clone

open:
	open source/main.cpp
	open source/functions.h
	open source/functions.cpp

openwin:
	source\main.cpp
	source\functions.h
	source\functions.cpp

run:
	clear
	./wordle_clone

runwin:
	cls
	wordle_clone.exe

clean:
	rm *.o wordle_clone

cleanwin:
	del *.o wordle_clone.exe
