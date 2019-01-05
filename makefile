defalt:
	make compile
	chmod a+x src/*

compile:
	g++ -o tolink main.cpp -Wall

install:
	./tolink --install
