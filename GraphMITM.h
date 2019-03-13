#ifndef __GRAPHMITM_H__
#define __GRAPHMITM_H__

#include <iostream>
#include <vector>
using namespace std;
#include "Graph.h"
#include "CliqueInfo.h"

class GraphMITM: public Graph::Graph
{
public:
	GraphMITM(std::size_t n_vertex, std::vector< std::vector<int> >& matrix);
	void check(int mask, int size, int in_clique, int cli, char set, int current, int current_binary);
	int clique_find();
	std::vector< CliqueInfo > cliques_A;
	std::vector< CliqueInfo > cliques_B;
	int max_clique;
	int max_clique_size;
};

#endif
