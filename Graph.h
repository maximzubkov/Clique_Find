#pragma once

/// Вместо ifndef ...., можно просто написать #pragma once, так и в конце #endif тоже не нужен

#include <vector>

/// вообще дизлайк, так делать не надо нигде, кроме маленьких учебных проектов, у тебя может оказаться 20 пространств
/// имен с одинаковыми функциями внутри

class Graph{
    public:
        Graph(std::size_t n_vertex, std::vector< std::vector<int> >& matrix);
        // Graph(std::size_t n_vertex);
        void addVertex(uint64_t v);
        void removeVertex(const size_t vert);
        void printMatrix(void) const;
        void printNodeList(void) const;
        size_t size() const;
        std::vector < std::vector <int> > getMatrix() const;
        std::vector <uint64_t> getBiteCodes() const;
    private:
        std::size_t graph_size_;
        std::vector < std::vector <int> > graph_matrix_;
        std::vector <uint64_t> graph_bit_code_;
};

/// Во первых, стоит использовать private: для некоторых полей,
/// во-вторых, один из принципов ООП - инкапсуляция, желательно проектировать объект так, чтобы никакими вызовами его методов
/// или обращения к полям было невозможно испортить его внутреннюю структуру
/// В твоем случае можно написать где-то в кода graph.graphSize = 100500, и потом где-то в цикле типа
/// for (int i = 0; < graph.graphSize; ++i) { graphMarix[i][0] = 1; } словить выход за границы массива


/// небольшой набросок
// class Graph {
// public:
//     Graph(std::size_t n_vertex, std::vector< std::vector<int> >&& matrix);

//     void printMatrix() const ;
//     void printNodeList() const;

//     bool HasEdge(size_t from, size_t to) const {
//         if (from > graph_size_ || to > graph_size_) {
//             return false;
//         }
//         return (graph_matrix_[from][to] == 1);
//     }

//     size_t size() const {
//         return graph_size_;
//     }


// private:
//     std::size_t graph_size_;
//     std::vector < std::vector <int> > graph_matrix_;
//     std::vector <uint64_t> graph_bit_code_;
// }
