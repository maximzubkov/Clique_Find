#include <iostream>
#include <vector>
using namespace std; 

void vertexes (unsigned long long int num, int max){
	int i = 0;
	std::cout << "(";
	while (num > 0){
		if ((num & 1ULL) == 1ULL){
			std::cout << max - i - 1<< " ";
		}
		i++;
		num = num >> 1;
	}
	std::cout << ")";
	std::cout << "\n";
}

void binary (unsigned long long int num){
	int i = 0;
	std::vector<int> v;
	while (num > 0){
		if (num % 2 == 1){
			v.push_back(1);
		} else {
			v.push_back(0);
		}
		i++;
		num = num >> 1;
	}
	for (i = v.size() - 1; i >= 0; i--){
		std::cout << v[i];
	}
	std::cout << " " << v.size() << "\n";
}

void print(char set, int in_clique, unsigned long long int cli, unsigned long long int all, int max){
	std::cout << set<< ": " << cli << " in clique: " <<  in_clique << "; ";
	vertexes(cli, max);
	std::cout << "all: ";
	vertexes(all, max);

}