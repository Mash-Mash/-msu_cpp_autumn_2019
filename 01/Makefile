all: calculator

run: calculator
	./calculator

test: calculator
	python3 ./test.py

calculator: main.cpp calculator.cpp utils.cpp
	g++ -o calculator main.cpp calculator.cpp utils.cpp 
