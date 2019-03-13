#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "GraphMITM.h"
#include "Graph.h"
#include "CliqueInfo.h"

void binary (int num){
	int i = 0;
	std::cout << "(";
	while (num > 0){
		if (num % 2 == 1){
			std::cout << i << " ";
		}
		i++;
		num = num >> 1;
	}
	std::cout << ")";
	std::cout << "\n";
}

GraphMITM::GraphMITM(std::size_t n_vertex,  std::vector< std::vector<int> >& matrix): 
	Graph::Graph(n_vertex, matrix) 
{
	std::cout << "GraphMITM \n" << endl;
	max_clique_size = 0;
	max_clique = clique_find();
	std::cout << "\n\n\nans:";
	binary(max_clique);
	Graph::printMatrix();

}
/*
int bin_search(int key){

}
*/

void GraphMITM::check(int mask, int size, int in_clique, int cli, char set, int current, int current_binary){
	if (set == 'A' && (in_clique > 1)){
		CliqueInfo tmp = {cli, in_clique, mask};
		cliques_A.push_back(tmp);
		int i = 0;
		std::cout << "A: " << cli << " in clique: " <<  in_clique << "; ";
		binary(cli);
		std::cout << "mask: ";
		binary(mask);
		if ((mask & ((1 << size) - 1)) == 0){
			return;
		}
	} 
	if (set == 'B' && (in_clique > 1)){
		CliqueInfo tmp = {cli, in_clique, mask};
		cliques_B.push_back(tmp);
		int i = 0;
		std::cout << "B: " << cli << " in clique: " <<  in_clique << "; ";
		binary(cli);
		std::cout << "mask: ";
		binary(mask);
		if ((mask & ((1 << graphSize) - 1)) == 0){
			return;
		}
	}
	int i = current_binary, j = current, maximum;
	if (set == 'A'){
		maximum = (1 << size);
	}
	if (set == 'B'){
		maximum = (1 << (graphSize));
	}
	while(1){
		if (i >= maximum){
			break;
		}
		if ((i & mask) != 0){
			//cli.push_back(j);
			//std::cout << "   " << j; 
			check(mask & graphBitCode[j], size, in_clique + 1, cli + i, set, j + 1, i << 1);
			//std::cout << "\n"; 
			//cli.pop_back();
		}
		j++;
		i = i << 1;
	}
	return;
}

int GraphMITM::clique_find(){
	int res;

	// Разобъем множество вершин на два множества A и B равной
	// (или почти равной в случае нечетного числа вершин)
	// мощности

	std::vector< int > A;
	std::vector< int > B;
	int i, med = graphSize / 2;
	for (i = 0; i < graphSize; i++){
		if (i < med){
			A.push_back(graphBitCode[i]);
		} else {
			B.push_back(graphBitCode[i]);
		}
	}

	// Затем для каждого из множеств найдем клику наибольшего размера. 
	// Для этого воспользуемся маской (маска показывает какие вершины 
	// можно добавить, легко понять, что на самом первом шаге можно добавить любую, 
	// поэтому изначально маска заполнена только единицами). Добавив некоторую вершину с номером V,
	// необходимо уменьшить число доступных вершин, ведь вершины, не соединенные с добавленной
	// не могут находиться с ней в одной клике, поэтому сделаем побитовое "и" исходной маски 
	// и V-той строчки из матрицы смежности. Будем делать так до тех пор, пока маска не привратится
	// в нулевую, сравним найденную клику с максимальной полученной ранне и пойдем дальше проверять

	int mask_A = (1 << med) - 1; // Задаем маску из единичек
	int mask_B = ((1 << (graphSize - med)) - 1) << med;
	std::cout << "m_A " << mask_A << "m_B " << mask_B << "\n";
	// Вставим пустое мноежство
	CliqueInfo empty = {0, 0, (1 << (graphSize)) - 1};
	cliques_A.push_back(empty);
	cliques_B.push_back(empty);
	check(mask_A, med, 0, 0, 'A', 0, 1);
	check(mask_B, graphSize - med, 0, 0, 'B', med, 1 << (med));
	
	// Теперь надо узнать для каждой клики графа A такие клики графа B,  
	// что их объединение также является кликой. Для одной клики K графа A может быть 
	// несколько подходящих клик в B. Чтобы по некоторому заданному k выдать ответ, есть ли
	// в графе клика мощности k можно воспользоваться следующим алгоритмом:
	// для начала отсортируем массив клик clique_B за O(2^{N/2}log(2^{N/2})) = O(N * 2^{N/2})
	// и для каждой клики из clique_A бинарным поиском будем искать такую клику из clique_B, 
	// что в сумме вершин будет не менее k. Бинарный поиск отработает за O(log(2^{N/2})) = O(n), 
	// при этом бинарный поиск осуществляется для каждой клики из clique_A, то есть 
	// общая ассимптотика будет O(N * 2^{N/2}).
	// В случае поиска максимального элемента такой алгоритм не сработает, необходимо 
	// отсортировать оба массива и далее идти сверху вниз, считая при этом 
	// clique_A[i].clique & clique_B[j].another_subset_connected_vertexes

	std::sort(cliques_B.begin(), cliques_B.end());
	for (i = 0; i < cliques_B.size(); i++){
		binary(cliques_B[i].clique);
		std::cout << "mask: ";
		binary(cliques_B[i].mask);
	}
	
	std::cout << "\n\n";

	// Бинарный поиск 
	int empty_pos = cliques_B.size() - 1; 
    for (i = 0; i < cliques_A.size(); i++){
    	if (cliques_A[i].size + cliques_B[empty_pos].size > max_clique_size){
    		std::cout << "the legendary:";
        	binary(cliques_A[i].clique + cliques_B[empty_pos].clique);
    		max_clique_size = cliques_A[i].size + cliques_B[empty_pos].size;
            res = cliques_A[i].clique + cliques_B[empty_pos].clique;
    	}
    }
    int left = 0;
    int right = cliques_B.size();
   	int mid = 0;
    for (i = 0; i < cliques_A.size() - 1; i++){
    	std::cout << i;
    	binary(cliques_A[i].clique);
		std::cout << "mask: ";
		binary(cliques_A[i].mask);
    	while (left < right){
        	mid = left + (right - left) / 2;

        	if (cliques_B[mid].mask == cliques_A[i].clique){
        		std::cout << "the legendary:";
        		binary(cliques_B[mid].clique + cliques_A[i].clique);
        		if (cliques_B[mid].size + cliques_A[i].size > max_clique_size){
            		max_clique_size = cliques_B[mid].size + cliques_A[i].size;
            		res = cliques_B[mid].clique + cliques_A[i].clique;
            	}
        	}
        	if (cliques_B[mid].mask > cliques_A[i].clique)
            	right = mid;
        	else
            	left = mid + 1;
    	}
	}

    return res;
}

/*

for (i = 0; i < graphMatrix.size(); i++){
	std::cout << mask[i];
}

*/