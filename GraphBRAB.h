

#ifndef __GRAPHMITM_H__
#define __GRAPHMITM_H__

#include <iostream>
#include <vector>
using namespace std;
#include "Graph.h"

class GraphBRAB : public Graph 
{
public:
	GraphBRAB(std::size_t n_vertex);
private:
	std::vector<int> clique_find();
	std::vector<int> clique;
};

#endif
