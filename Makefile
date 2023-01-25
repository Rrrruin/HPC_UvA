Game: main.o HPCGamelife.o
	g++ main.o HPCGamelife.o -o Game

main.o:main.cpp
	g++ main.cpp -c -o main.o
HPCGamelife.o:HPCGamelife.cpp
	g++ HPCGamelife.cpp -c -o HPCGamelife.o
