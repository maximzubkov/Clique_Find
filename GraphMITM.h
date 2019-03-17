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
    // Метод возвращает true, если в графе действительно есть клика размера заданного размера
    bool HasClique();
    // Метод возвращает размер максимальной клики для графа
    std::size_t GetMaxCliqueSize();
    // Метод возвращает вершины максимальной клики
    std::vector<int> GetMaxClique();
	void check(unsigned long long int mask, int size, int in_clique, 
			   unsigned long long int cli, char set, int current, 
			   unsigned long long int current_binary);
	unsigned long long int clique_find();
	std::vector< CliqueInfo > cliques_A;
	std::vector< CliqueInfo > cliques_B;
	unsigned long long int max_clique;
	int max_clique_size;
};

#endif
