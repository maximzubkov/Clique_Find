#include <iostream>
#include <vector>
using namespace std;
#include "GraphMITM.h"
#include "Graph.h"

GraphMITM::GraphMITM(std::size_t n_vertex,  std::vector< std::vector<int> >& matrix): 
	Graph::Graph(n_vertex, matrix) 
{
	std::cout << "GraphMITM \n" << endl;
	clique_size = 0;
	clique = clique_find();
	Graph::printMatrix();

}

void GraphMITM::check(int mask, int size, int in_clique, std::vector<int> cli){
	int i = 1, j = 0;
	if (mask == 0){
		if (in_clique > clique_size){
			clique_size = in_clique;
			clique = cli;
			for (i = 0; i < cli.size(); i++){
				std::cout << cli[i]<<" ";
			}
			std::cout << "\n";
		}
		return;
	}
	while(1){
		if (i >= (1 << size)){
			break;
		}
		if ((i & mask) != 0){
			cli.push_back(j);
			check(mask & graphBitCode[j], size, in_clique + 1, cli);
			cli.pop_back();
		}
		j++;
		i = i << 1;
	}
	return;
}

std::vector<int> GraphMITM::clique_find(){
	std::vector<int> res;

	// Разобъем множество вершин на два множества A и B равной
	// (или почти равной в случае нечетного числа вершин)
	// мощности

	std::vector< std::vector <int> > A;
	std::vector< std::vector <int> > B;
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
	int mask_B = (1 << graphSize - med) - 1
	std::vector <int> cli;
	check(mask_A, med, 0, cli);
	check(mask_B, graphSize - med, 0, cli);
	
	// Теперь надо узнать для каждой клики графа A количество клик графа B, таких, 
	// что их объединение также является кликой. Для одной клики K графа A может быть 
	// несколько подходящих клик в B. Для этого отсортируем массив клик clique_B
	// и для каждой клики из clique_A бинарным поиском будем искать такую клику из clique_B,
	// что в сумме они дадут больше, чем ранее найденная пара клик. 

	return res;
}




/*

for (i = 0; i < graphMatrix.size(); i++){
	std::cout << mask[i];
}

*/
