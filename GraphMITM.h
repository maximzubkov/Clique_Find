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
    // Метод возвращает true, если в графе есть клика размера заданного размера size 
    bool HasClique(std::size_t size);
    // Метод возвращает размер максимальной клики для графа
    std::size_t GetMaxCliqueSize();
    // Метод возвращает вершины максимальной клики
    std::vector<int> GetMaxClique();
	void check(uint64_t mask, int size, int in_clique, 
			   uint64_t cli, char set, int current, 
			   uint64_t current_binary);
	uint64_t clique_find();
	std::vector< CliqueInfo > cliques_A;
	std::vector< CliqueInfo > cliques_B;
	uint64_t max_clique;
	int max_clique_size;
};

#endif
