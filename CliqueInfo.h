#ifndef __CLIQUEINFO_H__
#define __CLIQUEINFO_H__

struct CliqueInfo {
	// Структура, содержащая всю необходимую информацию о клике
	unsigned long long int clique; // Сама клика
	int size; // Ее размер
	unsigned long long int mask; // Маска клики
	// Допустим мы рассматривем CliqueInfo для клики X вершин из A, тогда all для этой клики - вершины Y достижимые из каждой вершины клики X
	// объединить с самой кликой X
	unsigned long long int all;  
	bool operator<(const CliqueInfo& a) const
    {
        return all < a.all;
    }
};

#endif
