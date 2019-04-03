all:
	g++ -std=c++11 -lstdc++  main.cpp Graph.cpp GraphMITM.cpp GraphBRAB.cpp CliqueInfo.cpp -o graph
asan:
	g++ -fsanitize=address,leak,undefined main.cpp Graph.cpp GraphBRAB.cpp GraphMITM.cpp CliqueInfo.cpp -o graph
run:
	./graph.out
