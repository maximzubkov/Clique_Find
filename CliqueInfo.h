#pragma once

#include <cstdint>
#include <iostream>
using namespace std;
class CliqueInfo {
	// Структура, содержащая всю необходимую информацию о клике
	public:
		uint64_t clique; // Сама клика
		size_t size; // Ее размер
		uint64_t mask; // Маска клики
		// Допустим мы рассматривем CliqueInfo для клики X вершин из A, тогда all для этой клики - вершины Y достижимые из каждой вершины клики X
		// объединить с самой кликой X
		int max;
		uint64_t all;
		bool operator<(const CliqueInfo& a) const
	    {
	        return all < a.all;
	    }
	    CliqueInfo();
	    CliqueInfo(uint64_t clique, std::size_t size, uint64_t mask, size_t max, uint64_t all);
	    // CliqueInfo& operator=(const CliqueInfo) = default;
	    // CliqueInfo& operator=(CliqueInfo&&) noexcept = default;
	    friend std::ostream& operator << (std::ostream &ostr, const CliqueInfo &cli);
	    // friend CliqueInfo operator = (const CliqueInfo& cli);
};

