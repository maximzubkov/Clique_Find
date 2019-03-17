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
        void printNodeList(void);
        std::size_t graphSize;
        std::vector < std::vector <int> > graphMatrix;
        std::vector <unsigned long long int> graphBitCode;
};

#endif