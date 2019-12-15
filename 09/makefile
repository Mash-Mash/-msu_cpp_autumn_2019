var = FileSorter

all: $(var)

run: $(var)
	./$(var)

test: $(var)
	 ./$(var) -test

$(var): main.cpp
	g++ -pthread -o $(var) main.cpp
