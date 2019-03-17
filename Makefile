all:
	g++ -msse4 -mavx2 -Wshift-count-overflow main.cpp Graph.cpp GraphMITM.cpp BeautifulPrint.cpp -o graph
run:
	./graph.out
