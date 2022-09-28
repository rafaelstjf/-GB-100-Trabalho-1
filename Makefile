All:
	g++ -Wall -c main.cpp
	g++ -o main main.o

Debug:
	g++ -o main -Wall -ggdb main.cpp
