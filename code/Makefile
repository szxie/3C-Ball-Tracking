main: main.o Edge.o HSV.o Circle.o
	g++ `pkg-config --cflags opencv` -o main main.o Edge.o HSV.o Circle.o `pkg-config --libs opencv`
    
main.o: main.cpp
	g++ `pkg-config --cflags opencv` -c -o main.o main.cpp `pkg-config --libs opencv`
    
Edge.o: Edge.cpp
	g++ `pkg-config --cflags opencv` -c -o Edge.o Edge.cpp `pkg-config --libs opencv`
	
HSV.o: HSV.cpp
	g++ `pkg-config --cflags opencv` -c -o HSV.o HSV.cpp `pkg-config --libs opencv`
	
Circle.o: Circle.cpp
	g++ `pkg-config --cflags opencv` -c -o Circle.o Circle.cpp `pkg-config --libs opencv`
	
	


