
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "GraphBRAB.h"
#include "BeautifulPrint.h"
// using namespace Logger;
#include "Graph.h"

GraphBRAB::GraphBRAB(std::size_t n_vertex, std::vector< std::vector<int> >& matrix):
	Graph::Graph(n_vertex, matrix) 
{
	std::cout << "GraphBRAB \n" << endl;
	max_clique_size = 0;
	compsub = 0ULL;
	max_clique = 0ULL;
	clique_find((1ULL << this->size()) - 1ULL, 0ULL);
	std::cout << "ans: ";
	Logger::vertexes(std::cout, max_clique, this->size());
	std::cout << "size: " << max_clique_size << "\n";

}

bool GraphBRAB::HasClique(std::size_t size){
	if(max_clique_size >= size){
		return true;
	} else {
		return false;
	}
}
// Метод возвращает размер максимальной клики для графа
std::size_t GraphBRAB::GetMaxCliqueSize(){
	return (std::size_t)max_clique_size;
}
// Метод возвращает вершины максимальной клики
std::vector<int> GraphBRAB::GetMaxClique(){
	std::vector <int> v;
	int i = 0;
	uint64_t tmp = max_clique;
	while(tmp > 0){
		v.insert(v.begin(),(tmp & 1ULL));
		i++;
		tmp = tmp >> 1ULL;
	}
	v.insert(v.begin(),(tmp & 1ULL));
	return v;

}

bool GraphBRAB::check(uint64_t candidates, uint64_t forbidden){
	// Проверяет, содержит ли forbidden вершины, соединенные со всеми вершиными candidates
	std::vector<uint64_t> bit_code = this->getBiteCodes();
	for (int i = 0; i < this->size(); i++){
		if ((1ULL & (forbidden >> i)) == 1ULL){
			// Если нашлась такая вершина, которая соединена со всеми из candidates, то их побитовое 
			// "и" даст как раз таки ровно candidates, при поитовое "и" обладает таким свойством, что 
			// оно ограничено сверху candidates
			if ((candidates & bit_code[i]) == candidates){
				return true;
			}
		}
	}
	return false;
}

int GraphBRAB::number_of_vertexes(uint64_t v){
	int i = 0;
	uint64_t tmp = 1ULL;
	int num = 0;
	while(i < this->size()){
		if ((v & tmp) != 0ULL){
			num++;
		}
		i++;
		tmp = tmp << 1ULL;
	}
	return num;
}

// void GraphBRAB::pr(uint64_t candidates, uint64_t forbidden){
// 	std::cout << "candi: \n";
// 	vertexes(candidates, this->size());
// 	std::cout << "forb: \n";
// 	vertexes(forbidden, this->size());
// 	std::cout << "compsub: \n";
// 	vertexes(compsub, this->size());
// 	std::cout << "\n";
// }
void GraphBRAB::clique_find(uint64_t candidates, uint64_t forbidden){
	uint64_t v = (1ULL << (this->size() - 1));
	std::vector<uint64_t> bit_code = this->getBiteCodes();
	int i = 0;
	uint64_t new_candidates;
	uint64_t new_forbidden;
	while (candidates != 0ULL && (check(candidates, forbidden) == false)){
		while(i < this->size()){
			if ((v & candidates) != 0ULL){
				break;
			}
			v = v >> 1ULL;
			i++;
		}
		compsub = compsub ^ v;
		new_candidates = candidates & bit_code[i];
		new_forbidden = forbidden & bit_code[i];
		if (new_candidates == 0ULL && new_forbidden == 0ULL){
			if (number_of_vertexes(max_clique) < number_of_vertexes(compsub)){
				max_clique = compsub;
				max_clique_size = number_of_vertexes(compsub);
			}
		} else {
			clique_find(new_candidates, new_forbidden);
		}
		candidates = candidates ^ v;
		compsub = compsub ^ v;
		forbidden = forbidden | v;
		i = 0;
		v = (1ULL << (this->size() - 1));
	}
	return ;
}

