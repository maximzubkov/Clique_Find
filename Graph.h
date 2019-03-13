#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
using namespace std;

class Graph{
    public:
        Graph(std::size_t n_vertex,  std::vector< std::vector<int> >& matrix);
        ~Graph();
        void printMatrix();
        // Метод возвращает true, если в графе действительно есть клика размера заданного размера
        bool HasClique(std::size_t clique_size);
        // Метод возвращает размер максимальной клики для графа
        std::size_t GetMaxCliqueSize();
        // Метод возвращает вершины максимальной клики
        std::vector<int> GetMaxClique();
        void addEdge(int from, int to);
        void printNodeList(void);
        std::size_t graphSize;
        std::vector < std::vector <int> > graphMatrix;
        std::vector <int> graphBitCode;
};

#endif