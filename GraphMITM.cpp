#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "GraphMITM.h"
#include "Graph.h"
#include "CliqueInfo.h"
#include "BeautifulPrint.h"
#include <ctime>



GraphMITM::GraphMITM(std::size_t n_vertex,  std::vector< std::vector<int> >& matrix): 
	Graph::Graph(n_vertex, matrix) 
{
	std::cout << "GraphMITM \n" << endl;
	max_clique_size = 0;
	max_clique = clique_find();
	std::cout << "ans: ";
	vertexes(max_clique, graphSize);
	std::cout << "size: "<<max_clique_size << "\n";

}

// Метод возвращает true, если в графе действительно есть клика размера заданного размера size
bool GraphMITM::HasClique(std::size_t size){
	if(max_clique_size >= size){
		return true;
	} else {
		return false;
	}
}
// Метод возвращает размер максимальной клики для графа
std::size_t GraphMITM::GetMaxCliqueSize(){
	return (std::size_t)max_clique_size;
}
// Метод возвращает вершины максимальной клики
std::vector<int> GraphMITM::GetMaxClique(){
	std::vector <int> v;
	int i = 0;
	unsigned long long int tmp = max_clique;
	while(tmp > 0){
		v.insert(v.begin(),(tmp & 1ULL));
		i++;
		tmp = tmp >> 1ULL;
	}
	v.insert(v.begin(),(tmp & 1ULL));
	return v;

}

void GraphMITM::check(unsigned long long int mask, int size, int in_clique, unsigned long long int cli, char set, int current, unsigned long long int current_binary){
	// Перебирает рекурсивно все подмножества X вершин множества A (B) и доавляет в массив clique_A (clique_B) только такие X,
	// все вершины в которого соединины между собой
	if (set == 'A' && (in_clique >= 1ULL)){
		CliqueInfo tmp = {cli, in_clique, mask, (mask & ((1ULL << (size)) - 1ULL)) + cli};
		cliques_A.push_back(tmp);
		//print('A', in_clique, tmp.clique, tmp.all, graphSize);
		if ((mask & (((1 << size) - 1ULL) << (size))) == 0ULL){
			return;
		}
	} 
	if (set == 'B' && (in_clique >= 1ULL)){
		CliqueInfo tmp = {cli, in_clique, mask, ((mask >> (size)) << (size)) + cli};
		cliques_B.push_back(tmp);
		//print('B', in_clique, tmp.clique, tmp.all, graphSize);
		if ((mask & ((1ULL << size) - 1ULL)) == 0ULL){
			return;
		}
	}
	// maximum - ограничене, которое не позволяет брать биты, не входящее во множество A (или B)
	// на каждом шаге рассматриваем j-тый бит, то i = 2^j 
	unsigned long long int i = current_binary;
	int maximum;
	int j = current;
	if (set == 'A'){
		maximum = size;
	}
	if (set == 'B'){
		maximum = graphSize;
	}
	while(1){
		if (j >= maximum){
			break;
		}
		if ((i & mask) != 0ULL){
			check(mask & graphBitCode[j], size, in_clique + 1, cli + i, set, j + 1, i >> 1);
		}
		j++;
		i = i >> 1;
	}
	return;
}

unsigned long long int GraphMITM::clique_find(){
	unsigned long long int res;

	// Разобъем множество вершин посередине на два множества A и B равной мощности (в случае нечетного числа вершин 
	// просто добавим нулевую строку и нулевой столбец в матрицу инцедентности)

	int i;
	int size = graphSize;
	if (graphSize % 2 != 0){
		graphSize++;
		size = graphSize;
		for (i = 0; i < graphBitCode.size(); i++){
			graphBitCode[i] = graphBitCode[i] << 1ULL;
		}
		graphBitCode.push_back(0ULL);
	}
	int med = size >> 1;



	// Затем для каждого из множеств найдем все клики. 
	// Для этого воспользуемся маской. Маска - это graphSize-битовое число, которое показывает,
	// какие вершины еще можно добавить, таким образом для множества вершин X маской будет 
	// побитовое "и" строчек матрицы инцедентности, соответсвющих номерам вершин множества.
	// Легко понять, что на самом первом шаге можно добавить любую вершину, поэтому изначально маска заполнена только единицами. 
	// Когда мы добавляем некоторую вершину с номером V, число вершин, которые после добавления еще можно добавить либо уменьшится,
	// либо останется тем же, ведь вершины, не соединенные с добавленной не могут находиться с ней в одной клике, 
	// поэтому сделаем побитовое "и" исходной маски и V-той строчки из матрицы смежности.
	// Допустим мы ищем все клики множества A (для B аналогично, разве что с немного другими цифрами), маска помогает в двух вещах: 
	// 	  * Во-первых, стоит остановить рекурсивный перебор, когда часть маски, соотвествующая номерам вершин из A 
	// 		(для множества А это первые med битов маски) станет вся нулевой, тогда из рекурсивного перебора можно возвращаться
	// 	  * Во-вторых, если мы нашли некоторые клики в множества А и В, битовая запись которых cli_A и cli_B, а маски mask_A и mask_B
	//		при этом множеству А отвечают первые med битов маски, а множеству B оставшиеся graphSize - med битов. Тогда если 
	// 		cli_A и cli_B вместе также образуют клики, тогда верна формула: 
	//						(последние graphSize - med битов mask_A) + cli_A = (первые med битов mask_B) + cli_B
	// Таким образом будет удобно ввести еще одну характеристику клики, назовем ее all, для множества A: all_A = 
	// (последние graphSize - med битов mask_A) + cli_A; а для множества B: all_B = (первые med битов mask_B) + cli_B.
	// Стоить заметить, что для каждой клики значение параметра all уникальное

	unsigned long long int mask = (1ULL << size) - 1ULL; // Задаем маску из единичек
	// В каждом из множеств A и B должно быть пустое множество в качестве клики
	CliqueInfo empty_A = {0, 0, (1ULL << (size)) - 1ULL, ((1ULL << (med)) - 1ULL) };
	CliqueInfo empty_B = {0, 0, (1ULL << (size)) - 1ULL, ((1ULL << med) - 1ULL) << (graphSize - med)};
	cliques_A.push_back(empty_A);
	check(mask, med, 0, 0ULL, 'A', 0, 1ULL << (size - 1ULL));
	cliques_B.push_back(empty_B);
	check(mask, med, 0, 0ULL, 'B', med, 1ULL << (med - 1ULL));
	
	// Теперь надо узнать для каждой клики графа A такие клики графа B,  
	// что их объединение также является кликой. Для одной клики K графа A может быть 
	// несколько подходящих клик в B. Для начала отсортируем массив клик clique_B за O(2^{N/2}log(2^{N/2})) = O(N * 2^{N/2})
	// и для каждой клики сlique_A[i] бинарным поиском будем искать такую клику clique_B[j],
	// что сlique_A[i].all = clique_B[j].all. Это можно сделать бинарным поиском, так как для каждого значения 
	// сlique_A[i].all существует только одно значение clique_B[j].all равное ему, поэтому поиск отработает верно.

	std::sort(cliques_B.begin(), cliques_B.end());

	// Для начала пройдем по всем кликам из clique_A выберем среди них максимальную, выберем ее как начало для бинарного поиска

	/*
	for (i = 0; i < cliques_B.size(); i++){
		vertexes(cliques_B[i].all, size);
	}

	for (i = 0; i < cliques_A.size(); i++){
		vertexes(cliques_A[i].all, size);
	}
	*/

    for (i = 0; i < cliques_A.size(); i++){
    	if (cliques_A[i].size > max_clique_size){
    		max_clique_size = cliques_A[i].size;
            res = cliques_A[i].clique;
    	}
    }
    std::cout << "\n";
	// Бинарный поиск 

    int left = 0;
    int right = cliques_B.size();
   	int mid = 0;
    for (i = 0; i < cliques_A.size(); i++){
    	left = 0;
    	right = cliques_B.size();
   		mid = 0;
    	while (left < right){
        	mid = left + (right - left) / 2;
        	if (cliques_A[i].all == cliques_B[mid].all){
        		if (cliques_B[mid].size + cliques_A[i].size > max_clique_size){
            		max_clique_size = cliques_B[mid].size + cliques_A[i].size;
            		res = cliques_B[mid].clique | cliques_A[i].clique;
            		
            	}
        	}
        	if (cliques_A[i].all < cliques_B[mid].all)
            	right = mid;
        	else
            	left = mid + 1;
    	}
	}

	// Отменим временные изменения, которые пришлось сделать 

	if (graphSize % 2 != 0){
		for (i = 0; i < graphBitCode.size() - 1; i++){
			graphBitCode[i] = graphBitCode[i] >> 1;
		}
		graphBitCode.pop_back();
		graphSize--;
	}
    return res;
}
