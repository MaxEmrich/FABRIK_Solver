CXX = g++ -g

my_program: main.o funcs.o 
	$(CXX) main.o funcs.o -o my_program

main.o: main.cpp
	$(CXX) -c main.cpp 

funcs.o: funcs.cpp
	$(CXX) -c funcs.cpp

clean: 
	rm *.o my_program

# <target>: <dependencies>
#	 <recipe>