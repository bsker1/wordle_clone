 wordle_clone: main.o functions.o
	g++ main.o functions.o -o wordle_clone

main.o:
	g++ -c main.cpp

functions.o:
	g++ -c functions.cpp

db:
	g++ -g main.cpp functions.cpp -o wordle_clone

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
	wordleclone.exe

clean:
	rm *.o wordle_clone

cleanwin:
	del *.o wordle_clone.exe
