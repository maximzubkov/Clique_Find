all:
	g++ -msse4 -mavx2 main.cpp Graph.cpp GraphMITM.cpp -o graph
run:
	./graph.out
