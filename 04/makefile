var = BigInt

all: $(var)

run: $(var)
	./$(var)

test: $(var)
	 ./$(var) -test

$(var): main.cpp $(var).cpp
	g++ -o $(var) main.cpp $(var).cpp
