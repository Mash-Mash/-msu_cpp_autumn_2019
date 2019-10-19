all: LinearAllocator

run: LinearAllocator
	./LinearAllocator

test: LinearAllocator
	python3 ./test.py

LinearAllocator: main.cpp LinearAllocator.cpp
	g++ -o LinearAllocator main.cpp LinearAllocator.cpp
