#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

Graph::Graph(size_t n_vertex, std::vector< std::vector<int> >& matrix) : graph_size_(n_vertex), graph_matrix_(matrix) {
    // Конструктор класса, преобразующй
    std::cout << "Graph object being created with max nodes size:" << n_vertex << "\n\n";
    int i = 0, j = 0; /// В цикл
    uint64_t num = 0;
    for(i = 0; i < graph_size_; i++){
        num = 0; /// Не информативное название переменной
        for(j = 0; j < graph_size_; j++){
            num += (static_cast<uint64_t>(graph_matrix_[i][j]) << (graph_size_ - j - 1));
            /// В плюсах преобразование типов через static_cast<uint64_t>(graphMatrix[i][j]), (...)graphMatrix - наследие си
        }
        graph_bit_code_.push_back(num);
    }
}


void Graph::printMatrix(void) const{
    // Выводит матрицу инцедентности

    /// Если явно не работаешь с индексами, используй итерацию по элементам
    for (const auto& graph_row : graph_matrix_) {
        for (const auto& matrix_element : graph_row) {
            std::cout  << matrix_element << " ";
        }
        std::cout  << std::endl;
    }
}



void Graph::printNodeList(void) const{
    // Выводит все ребра графа в формате (u, v)
    for(int i = 0; i < graph_size_; i++){
        for(int j = 0; j < graph_size_; j++){
            if (graph_matrix_[i][j] == 1){
                std::cout << "(" << i << "," << j << ")";
            }
        }
    }
}

void Graph::addVertex(uint64_t v){
    graph_size_++;
    graph_bit_code_.push_back(v);
    for (int i = 0; i < this->size(); i++){
       graph_bit_code_[i] = (graph_bit_code_[i] << 1ULL) + (v & (1ULL << i)); 
    }
}


void Graph::removeVertex(const size_t vert){
    graph_bit_code_.erase(graph_bit_code_.begin() + vert);
    graph_size_--;
    uint64_t tmp = (1ULL << (this->size() - vert + 1)) - 1ULL;
    for (int i = 0; i < graph_size_; i++){
        graph_bit_code_[i] = ((graph_bit_code_[i] >> (this->size() - vert + 1)) << (this->size() - vert)) + (graph_bit_code_[i] & tmp);
    }
}


size_t Graph::size() const {
    return graph_size_;
}


std::vector < std::vector <int> > Graph::getMatrix() const{
    return graph_matrix_;
}


std::vector <uint64_t> Graph::getBiteCodes() const {
    return graph_bit_code_;
}