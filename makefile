 wordle_clone: main.o functions.o
	g++ -std=c++17 main.o functions.o -o wordle_clone

main.o:
	g++ -c -std=c++17 main.cpp

functions.o:
	g++ -c -std=c++17 functions.cpp

db:
	g++ -g -std=c++17 main.cpp functions.cpp -o wordle_clone

open:
	open main.cpp
	open functions.h
	open functions.cpp

openwin:
	main.cpp
	functions.h
	functions.cpp

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
