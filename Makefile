CXX = g++ -g

fabrik: main.o vector_3d.o point_3d.o
	$(CXX) main.o vector_3d.o point_3d.o -o fabrik

main.o: main.cpp
	$(CXX) -c main.cpp 

vector_3d.o: vector_3d.cpp
	$(CXX) -c vector_3d.cpp

point_3d.o: point_3d.cpp
	$(CXX) -c point_3d.cpp

clean: 
	rm *.o fabrik

# <target>: <dependencies>
#	 <recipe>