#ifndef __GRAPHBRAB_H__
#define __GRAPHBRAB_H__

#include <iostream>
#include <vector>
using namespace std;
#include "Graph.h"
#include "CliqueInfo.h"

class GraphBRAB: public Graph::Graph
{
public:
	GraphBRAB(std::size_t n_vertex, std::vector< std::vector<int> >& matrix);
	// Метод возвращает true, если в графе есть клика размера заданного размера size 
    bool HasClique(std::size_t size);
    // Метод возвращает размер максимальной клики для графа
    std::size_t GetMaxCliqueSize();
    // Метод возвращает вершины максимальной клики
    std::vector<int> GetMaxClique();
private:
	bool check(uint64_t candidates, uint64_t forbidden);
	void clique_find(uint64_t candidates, uint64_t forbidden);
	int number_of_vertexes(uint64_t v);
	uint64_t compsub;
	uint64_t max_clique;
	int max_clique_size;
};

#endif
