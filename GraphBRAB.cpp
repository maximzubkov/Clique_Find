#include <iostream>
#include <vector>
using namespace std;
#include "GraphBRAB.h"
#include "Graph.h"

GraphBRAB::GraphBRAB(std::size_t n_vertex) : Graph::Graph(n_vertex) 
{
	std::cout << "GraphBRAB \n" << endl;
	clique = clique_find();
}

std::vector<int> GraphBRAB::clique_find(){
	std::vector<int> res;
	std::cout << "BRAB \n";
	return res;
}