CC=g++

run: prog1 prog2
	./prog1
	./prog2

prog1: sum_by_rows.o
	$(CC) -o prog1 sum_by_rows.o --std=c++11 -O2

sum_by_rows.o: sum_by_rows.cpp 
	$(CC) -c sum_by_rows.cpp --std=c++11 -O2

prog2: sum_by_columns.o
	$(CC) -o prog2 sum_by_columns.o --std=c++11 -O2

sum_by_columns.o: sum_by_columns.cpp
	$(CC) -c sum_by_columns.cpp --std=c++11 -O2

clean:
	rm -rf *.o my_prog
