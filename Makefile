
algos: test.o
	g++ test.o -o algos

test.o : *.cpp *.hpp
	g++ -c *.cpp -o *.o

*.hpp : *.cpp
	g++ -c *.cpp -o *.o

clean:
	rm -f *.o