 wordle_clone: main.o
	g++ main.o -o wordle_clone

main.o:
	g++ -c main.cpp

db:
	g++ -g main.cpp -o wordle_clone

clean:
	rm *.o wordle_clone

cleanwin:
	del *.o generate_dictioanry.exe
