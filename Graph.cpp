#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

Graph::Graph(size_t n_vertex, std::vector< std::vector<int> >& matrix) : graphSize(n_vertex), graphMatrix(matrix) {
    std::cout << "Graph object being created with max nodes size:" << n_vertex << "\n\n";
    int i = 0, j = 0;
    int num = 0;
    for(i = 0; i < graphSize; i++){
        num = 0;
        for(j = 0; j < graphSize; j++){
            num += (graphMatrix[i][graphSize - j - 1] << (graphSize - j - 1)); 
        }
        //std::cout<< num << " ";
        graphBitCode.push_back(num);
    }
}

Graph::~Graph(){
    std::cout << "Graph distroed" << "\n\n";
}	

void Graph::printMatrix(){
    int i, j;
    for(i = 0; i < graphSize; i++){
        for(j = 0; j < graphSize; j++){
            std::cout << graphMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Graph::printNodeList() {
    int i, j;
    for(i = 0; i < graphSize; i++){
        for(j = 0; j < graphSize; j++){
            if (graphMatrix[i][j] == 1){
                std::cout << "(" << i << "," << j << ")";
            }
        }
    }
}