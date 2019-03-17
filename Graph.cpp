#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

Graph::Graph(size_t n_vertex, std::vector< std::vector<int> >& matrix) : graphSize(n_vertex), graphMatrix(matrix) {
    // Конструктор класса, преобразующй 
    std::cout << "Graph object being created with max nodes size:" << n_vertex << "\n\n";
    int i = 0, j = 0;
    unsigned long long int num = 0;
    for(i = 0; i < graphSize; i++){
        num = 0;
        for(j = 0; j < graphSize; j++){
            num += ((unsigned long long int)graphMatrix[i][j] << (graphSize - j - 1)); 
        }
        graphBitCode.push_back(num);
    }
}



Graph::~Graph(){
    //Диструктор
    std::cout << "Graph distroed" << "\n\n";
}	



void Graph::printMatrix(){
    // Выводит матрицу инцедентности 
    int i, j;
    for(i = 0; i < graphSize; i++){
        for(j = 0; j < graphSize; j++){
            std::cout << graphMatrix[i][j] << "";
        }
        std::cout << "\n";
    }
}



void Graph::printNodeList() {
    // Выводит все ребра графа в формате (u, v)
    int i, j;
    for(i = 0; i < graphSize; i++){
        for(j = 0; j < graphSize; j++){
            if (graphMatrix[i][j] == 1){
                std::cout << "(" << i << "," << j << ")";
            }
        }
    }
}